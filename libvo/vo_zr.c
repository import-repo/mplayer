/* 
 * vo_zr.c - playback on zoran cards 
 * Copyright (C) Rik Snel 2001,2002, License GNU GPL v2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/videodev.h>
#include "zoran.h"

#include "config.h"

#include "video_out.h"
#include "video_out_internal.h"
#include "../mp_msg.h"
#include "../cfgparser.h"
#include "fastmemcpy.h"

LIBVO_EXTERN (zr)

static vo_info_t vo_info = 
{
	"Zoran ZR360[56]7/ZR36060 Driver (DC10(+)/buz/lml33/MatroxRR)",
	"zr",
	"Rik Snel <snel@phys.uu.nl>",
	""
};

/* General variables */

static int image_width;
static int image_height;
static int off_y, off_c, stride; /* for use by 'draw slice/frame' */
static int framenum;
static int fields = 1; /* currently no interlacing */
static int zrfd = 0;
static int bw = 0; /* if bw == 1, then display in black&white */
static int vdec = 1;
static int hdec = 1;
static int size;
static int quality = 1;

typedef struct {
	int width;
	int height;
	int xoff;
	int yoff;
	int set;
} geo;
geo g = {0, 0, 0, 0, 0};

static uint8_t *image=NULL;
static uint8_t *buf=NULL;


/* Variables needed for Zoran */

int vdes;  /* the file descriptor of the video device */
int frame = 0, synco = 0, queue = 0; /* buffer management */
struct zoran_params zp;
struct zoran_requestbuffers zrq;
struct zoran_sync zs;
struct video_capability vc;
#define MJPEG_NBUFFERS	2
#define MJPEG_SIZE	1024*256

//should be command line options
int norm = VIDEO_MODE_AUTO;
#ifndef VO_ZR_DEFAULT_DEVICE
#define VO_ZR_DEFAULT_DEVICE "/dev/video"
#endif
char *device = NULL;


extern int mjpeg_encode_frame(char *bufr, int field);
extern void mjpeg_encoder_init(int w, int h, unsigned char *y,
		int y_psize, int y_rsize, unsigned char *u,
		int u_psize, int u_rsize, unsigned char *v,
		int v_psize, int v_rsize, int f, int cu, int q, int b);

int zoran_getcap() {
	char* dev = device ? device : VO_ZR_DEFAULT_DEVICE;
	vdes = open(dev, O_RDWR);
	/* before we can ask for the maximum resolution, we must set 
	 * the correct tv norm */

	if (ioctl(vdes, BUZIOC_G_PARAMS, &zp) < 0) {
		mp_msg(MSGT_VO, MSGL_ERR, "device at %s is probably not a DC10(+)/buz/lml33\n", dev);
		return 1;
	}
	
	if (zp.norm != norm && norm != VIDEO_MODE_AUTO) {
		/* attempt to set requested norm */
		zp.norm = norm;
		if (ioctl(vdes, BUZIOC_S_PARAMS, &zp) < 0) {
			mp_msg(MSGT_VO, MSGL_ERR,
				"unable to change video norm, use another program to change it (XawTV)\n");
			return 1;
		}
		ioctl(vdes, BUZIOC_G_PARAMS, &zp);
		if (norm != zp.norm) {
			mp_msg(MSGT_VO, MSGL_ERR,
				"unable to change video norm, use another program to change it (XawTV)\n");
			return 1;
		}
	}
	
	if (vdes < 0) {
		mp_msg(MSGT_VO, MSGL_ERR, "error opening %s\n", 
				dev);
		return 1;
	}


	if (ioctl(vdes, VIDIOCGCAP, &vc) < 0) {
		mp_msg(MSGT_VO, MSGL_ERR, "error getting video capabilities from %s\n");
		return 1;
	}
	mp_msg(MSGT_VO, MSGL_V, "zr: MJPEG card reports maxwidth=%d, maxheight=%d\n", vc.maxwidth, vc.maxheight);
	
	return 0;
}
	
int init_zoran(int zrhdec, int zrvdec) {
	/* center the image, and stretch it as far as possible (try to keep
	 * aspect) and check if it fits */
	if (image_width > vc.maxwidth) {
		mp_msg(MSGT_VO, MSGL_ERR, "zr: movie to be played is too wide, max width currenty %d\n", vc.maxwidth);
		return 1;
	}

	if (image_height > vc.maxheight) {
		mp_msg(MSGT_VO, MSGL_ERR, "movie to be played is too high, max height currenty %d\n", vc.maxheight);
		return 1;
	}

	zp.decimation = 0;
	zp.HorDcm = zrhdec; 
	zp.VerDcm = zrvdec;
	zp.TmpDcm = 1;
	zp.field_per_buff = fields;
	zp.img_x = (vc.maxwidth - zp.HorDcm*(int)image_width/hdec)/2;
	zp.img_y = (vc.maxheight - zp.VerDcm*(3-fields)*(int)image_height)/4;
	zp.img_width = zp.HorDcm*image_width/hdec;
	zp.img_height = zp.VerDcm*image_height/fields;
	mp_msg(MSGT_VO, MSGL_V, "zr: geometry (after 'scaling'): %dx%d+%d+%d fields=%d, w=%d, h=%d\n", zp.img_width, (3-fields)*zp.img_height, zp.img_x, zp.img_y, fields, image_width/hdec, image_height);

	if (ioctl(vdes, BUZIOC_S_PARAMS, &zp) < 0) {
		mp_msg(MSGT_VO, MSGL_ERR, "error setting display parameters\n");
		return 1;
	}

	zrq.count = MJPEG_NBUFFERS;
	zrq.size = MJPEG_SIZE;

	if (ioctl(vdes, BUZIOC_REQBUFS, &zrq)) {
		mp_msg(MSGT_VO, MSGL_ERR, "error requesting %d buffers of size %d\n", zrq.count, zrq.size);
		return 1;
	}

	buf = (char*)mmap(0, zrq.count*zrq.size, PROT_READ|PROT_WRITE,
			MAP_SHARED, vdes, 0);

	if (buf == MAP_FAILED) {
		mp_msg(MSGT_VO, MSGL_ERR, "error requesting %d buffers of size %d\n", zrq.count, zrq.size);
		return 1;
	}
	return 0;
}

void uninit_zoran(void) {
	if (image) {
		free(image);
		image=NULL;
	}
	while (queue > synco + 1) {
		if (ioctl(vdes, BUZIOC_SYNC, &zs) < 0) 
			mp_msg(MSGT_VO, MSGL_ERR, "error waiting for buffers to become free"); 
		synco++;
	}
	/* stop streaming */
	frame = -1;
	if (ioctl(vdes, BUZIOC_QBUF_PLAY, &frame) < 0) 
		mp_msg(MSGT_VO, MSGL_ERR, "error stopping playback of last frame");
	close(vdes);
}

static uint32_t init(uint32_t width, uint32_t height, uint32_t d_width, 
	uint32_t d_height, uint32_t fullscreen, char *title, uint32_t format)
{
	int j, stretchx, stretchy;
	/* this allows to crop parts from incoming picture,
	 * for easy 512x240 -> 352x240 */
	/* These values must be multples of 2 */
	if (format != IMGFMT_YV12 && format != IMGFMT_YUY2) {
		printf("vo_zr called with wrong format");
		exit(1);
	}
	stride = 2*width;
	if (g.set) {
		if (g.width%2 != 0 || g.height%2 != 0 ||
				g.xoff%2 != 0 || g.yoff%2 != 0) {
			mp_msg(MSGT_VO, MSGL_ERR, "arguments in -zrcrop must be multiples of 2\n");
			return 1;
		}
		if (g.width <= 0 || g.height <= 0 ||
				g.xoff < 0 || g.yoff < 0) {
			mp_msg(MSGT_VO, MSGL_ERR, "width and height must be positive and offset nonnegative\n");
			return 1;
		}
		if (g.width + g.xoff > width) {
			mp_msg(MSGT_VO, MSGL_ERR, "width+xoffset (%d+%d>%d) is too big\n", g.width, g.xoff, width);
			return 1;
		}
		if (g.height + g.yoff > height) {
			mp_msg(MSGT_VO, MSGL_ERR, "height+yoffset (%d+%d>%d) is too big\n", g.height, g.yoff, height);
			return 1;
		}
	} else {
		g.width = width;
		g.height = height;
		g.xoff = 0;
		g.yoff = 0;
		g.set = 1;
	}
	/* we must know the maximum resolution of the device
	 * it differs for DC10+ and buz for example */
	zoran_getcap(); /*must be called before init_zoran */
	/* make the scaling decision
	 * we are capable of stretching the image in the horizontal
	 * direction by factors 1, 2 and 4
	 * we can stretch the image in the vertical direction by a factor
	 * of 1 and 2 AND we must decide about interlacing */
	if (g.width > vc.maxwidth/2 || g.height > vc.maxheight/2) {
		stretchx = 1;
		stretchy = 1;
		fields = 2;
		if (vdec == 2) {
			fields = 1;
		} else if (vdec == 4) {
			fields = 1;
			stretchy = 2;
		}
		stretchx = hdec;
	} else if (g.width > vc.maxwidth/4 || g.height > vc.maxheight/4) {
		stretchx = 2;
		stretchy = 1;
		fields = 1;
		if (vdec == 2) {
			stretchy = 2;
		} else if (vdec == 4) {
			if (!zrfd) {
				mp_msg(MSGT_VO, MSGL_WARN, "vo_zr: vertical decimation too high, changing to 2 (use -zrfd to keep vdec=4)\n");
				vdec = 2;
			}
			stretchy = 2;
		}
		if (hdec == 2) {
			stretchx = 4;
		} else if (hdec == 4){
			if (!zrfd) {
				mp_msg(MSGT_VO, MSGL_WARN, "vo_zr: horizontal decimation too high, changing to 2 (use -zrfd to keep hdec=4)\n");
				hdec = 2;
			}
			stretchx = 4;
		}
	} else {
		/* output image is maximally stretched */
		stretchx = 4;
		stretchy = 2;
		fields = 1;
		if (vdec != 1 && !zrfd) {
			mp_msg(MSGT_VO, MSGL_WARN, "vo_zr: vertical decimation too high, changing to 1 (use -zrfd to keep vdec=%d)\n", vdec);
			vdec = 1;
		}

		if (hdec != 1 && !zrfd) {
			mp_msg(MSGT_VO, MSGL_WARN, "vo_zr: vertical decimation too high, changing to 1 (use -zrfd to keep hdec=%d)\n", hdec);
			hdec = 1;
		}
	}
	/* It can be that the original frame was too big for display,
	 * or that the width of the decimated image (for example) after
	 * padding up to a multiple of 16 has become too big. (orig
	 * width 720 (exactly right for the Buz) after decimation 360,
	 * after padding up to a multiple of 16 368, display 736 -> too
	 * large). In these situations we auto(re)crop. */
	j = 16*((g.width - 1)/(hdec*16) + 1);
	if (stretchx*j > vc.maxwidth) {
		g.xoff += 2*((g.width - hdec*(j-16))/4);
		/* g.off must be a multiple of 2 */
		g.width = hdec*(j - 16);
		g.set = 0; /* we abuse this field to report that g has changed*/
	}
	j = 8*fields*((g.height - 1)/(vdec*fields*8) + 1);
	if (stretchy*j > vc.maxheight) {
		g.yoff += 2*((g.height - vdec*(j - 8*fields))/4);
		g.height = vdec*(j - 8*fields);
		g.set = 0;
	}
	if (!g.set) 
		mp_msg(MSGT_VO, MSGL_V, "zr: auto(re)cropping %dx%d+%d+%d to make the image fit on the screen\n", g.width, g.height, g.xoff, g.yoff);

	/* the height must be a multiple of fields*8 and the width
	 * must be a multiple of 16 */
	/* add some black borders to make it so, and center the image*/
	image_height = fields*8*((g.height/vdec - 1)/(fields*8) + 1);
	image_width = (hdec*16)*((g.width - 1)/(hdec*16) + 1);
	off_y = (image_height - g.height/vdec)/2;
	if (off_y%2 != 0) off_y++;
	off_y *= image_width;
	off_c = off_y/4;
	off_y += (image_width - g.width)/2;
	if (off_y%2 != 0) off_y--;
	off_c += (image_width - g.width)/4;
	framenum = 0;
	size = image_width*image_height;
	mp_msg(MSGT_VO, MSGL_V, "input: %dx%d, cropped: %dx%d, output: %dx%d, off_y=%d, off_c=%d\n", width, height, g.width, g.height, image_width, image_height, off_y, off_c);
	
	image = malloc(2*size); /* this buffer allows for YUV422 data,
				 * so it is a bit too big for YUV420 */
	if (!image) {
		mp_msg(MSGT_VO, MSGL_ERR, "Memory exhausted\n");
		return 1;
	}
	/* and make sure that the borders are _really_ black */
	switch (format) {
		case IMGFMT_YV12:
			memset(image, 0, image_width*image_height);
			memset(image + size, 0x80, image_width*image_height/4);
			memset(image + 3*size/2, 0x80, image_width*image_height/4);
			mjpeg_encoder_init(image_width/hdec, image_height,
					image, hdec, image_width,
					image + image_width*image_height, 
					hdec, image_width/2,
					image + 3*image_width*image_height/2, 
					hdec, image_width/2, fields, 1, 
					quality, bw);
			break;
		case IMGFMT_YUY2:
			for (j = 0; j < 2*size; j+=4) {
				image[j] = 0;
				image[j+1] = 0x80;
				image[j+2] = 0;
				image[j+3] = 0x80;
			}
			mjpeg_encoder_init(image_width/hdec, image_height,
					image, hdec*2, image_width*2,
					image + 1, hdec*4, image_width*2,
					image + 3, hdec*4, image_width*2,
					fields, 0, quality, bw);
			break;
		default:
			mp_msg(MSGT_VO, MSGL_FATAL, "internal inconsistency in vo_zr\n");
	}


	if (init_zoran(stretchx, stretchy)) {
		return 1;
	}

	return 0;
}

static const vo_info_t* get_info(void) {
	return &vo_info;
}

static void draw_osd(void) {
}

static void flip_page (void) {
	int i, j, k;
	/*FILE *fp;
	char filename[100];*/
	/* do we have a free buffer? */
	if (queue-synco < zrq.count) {
		frame = queue;
	} else {
		if (ioctl(vdes, BUZIOC_SYNC, &zs) < 0) 
			mp_msg(MSGT_VO, MSGL_ERR, "error waiting for buffers to become free"); 
		frame = zs.frame;
		synco++;
	}
	k=0;
	for (i = 0; i < fields; i++) 
		k+=mjpeg_encode_frame(buf+frame*zrq.size+k, i);
	/* Warning, Quantization and Huffman tables are only
	 * written in the first frame by default (to preserver bandwidth) */
	/*sprintf(filename, "test%04d.jpg", framenum);
	fp = fopen(filename, "w");
	if (!fp) exit(1);
	fwrite(buf+frame*zrq.size, 1, k, fp);
	fclose(fp);*/
	/*fp = fopen("test1.jpg", "r");
	fread(buf+frame*zrq.size, 1, 2126, fp);
	fclose(fp);*/
	
	if (ioctl(vdes, BUZIOC_QBUF_PLAY, &frame) < 0) 
		mp_msg(MSGT_VO, MSGL_ERR,
				"error queueing buffer for playback");
	queue++;

	framenum++;
	return;
}

static uint32_t draw_frame(uint8_t * src[]) {
	int i;
	char *source, *dest;
	//printf("draw frame called\n");
	source = src[0] + 2*g.yoff*image_width + 2*g.xoff;
	dest = image + 2*off_y;
	for (i = 0; i < g.height/vdec; i++) {
		memcpy(dest, source, image_width*2);
		dest += 2*image_width;
		source += vdec*stride;
	}
	return 0;
}

static uint32_t query_format(uint32_t format) {
	if(format==IMGFMT_YV12) return 1;
	if(format==IMGFMT_YUY2) return 1;
	return 0;
}

static void uninit(void) {
	uninit_zoran();
}

static void check_events(void) {
}


static uint32_t draw_slice(uint8_t *srcimg[], int stride[],
		int w, int h, int x, int y) {
	int i;
	/* Apply 'geometry', crop unwanted parts */
	uint8_t *dst;
	uint8_t *src;
	//printf("before: w=%d, h=%d, x=%d, y=%d, src0=%p, src1=%p, src2=%p\n", w, h, x, y, srcimg[0], srcimg[1], srcimg[2]);
	if (x < g.xoff) {
		srcimg[0] += g.xoff - x;
		srcimg[1] += (g.xoff - x)/2;
		srcimg[2] += (g.xoff - x)/2;
		w -= g.xoff - x;
		if (w < 0) return 0;
		x = 0 /*g.xoff*/;
	} else {
		x -= g.xoff;
	}
	if (x + w > g.width) {
		w = g.width - x;
		if (w < 0) return 0;
	}
	if (y < g.yoff) {
		srcimg[0] += (g.yoff - y)*stride[0];
		srcimg[1] += ((g.yoff - y)/2)*stride[1];
		srcimg[2] += ((g.yoff - y)/2)*stride[2];
		h -= g.yoff - y;
		if (h < 0) return 0;
		y = 0;
	} else {
		y -= g.yoff;
	}
	if (y + h > g.height) {
		h = g.height - y;
		if (h < 0) return 0;
	}
	//printf("after: w=%d, h=%d, x=%d, y=%d, src0=%p, src1=%p, src2=%p\n", w, h, x, y, srcimg[0], srcimg[1], srcimg[2]);
	dst=image + off_y + image_width*(y/vdec)+x;
	src=srcimg[0];
	// copy Y:
	for (i = 0; i < h; i++) {
		if ((i + x)%vdec == 0) {
			memcpy(dst,src,w);
			dst+=image_width;
		}
		src+=stride[0];

	}
	if (!bw) {
    		// copy U+V:
		uint8_t *src1=srcimg[1];
		uint8_t *src2=srcimg[2];
		uint8_t *dst1=image + size + off_c+ (y/(vdec*2))*image_width/2+(x/2);
		uint8_t *dst2=image + 3*size/2 + off_c + 
			(y/(vdec*2))*image_width/2+(x/2);
		for (i = 0; i< h/2; i++) {
			if ((i+x/2)%vdec == 0) {
				memcpy(dst1,src1,w/2);
				memcpy(dst2,src2,w/2);
				dst1+=image_width/2;
				dst2+=image_width/2;
			}
			src1+=stride[1];
			src2+=stride[2];
		}
    	}
 	return 0;
}


/* copied and adapted from vo_aa_parseoption */
int
vo_zr_parseoption(struct config * conf, char *opt, char *param){
    /* got an option starting with zr */
    char *x, *help;
    int i;
    /* do WE need it ?, always */
    if (!strcasecmp(opt, "zrdev")) {
	if (param == NULL) return ERR_MISSING_PARAM;
	//if ((i=getcolor(param))==-1) return ERR_OUT_OF_RANGE;
	//aaopt_osdcolor=i;
	device = malloc(strlen(param)+1);
	strcpy(device, param);
	mp_msg(MSGT_VO, MSGL_V, "zr: using device %s\n", device);
	return 1;
    } else if (!strcasecmp(opt, "zrbw")) {
	    if (param != NULL) {
		    return ERR_OUT_OF_RANGE;
	    }
	    bw = 1;
	    return 1;
    } else if (!strcasecmp(opt, "zrfd")) {
	    if (param != NULL) {
		    return ERR_OUT_OF_RANGE;
	    }
	    zrfd = 1;
	    return 1;
    } else if (!strcasecmp(opt, "zrcrop")){
	if (param == NULL) return ERR_MISSING_PARAM;
	if (sscanf(param, "%dx%d+%d+%d", &g.width, &g.height, 
				&g.xoff, &g.yoff) != 4) {
		g.xoff = 0; g.yoff = 0;
		if (sscanf(param, "%dx%d", &g.width, &g.height) != 2) {
			mp_msg(MSGT_VO, MSGL_ERR, "argument to -zrcrop must be of the form 352x288+16+0\n");
			return ERR_OUT_OF_RANGE;
		}
	}
	g.set = 1;
	mp_msg(MSGT_VO, MSGL_V, "zr: cropping %s\n", param);
	return 1;
    }else if (!strcasecmp(opt, "zrhdec")) {
        i = atoi(param);
	if (i != 1 && i != 2 && i != 4) return ERR_OUT_OF_RANGE;
	hdec = i;
	return 1;
    }else if (!strcasecmp(opt, "zrvdec")) {
        i = atoi(param);
	if (i != 1 && i != 2 && i != 4) return ERR_OUT_OF_RANGE;
	vdec = i;
	return 1;
    }else if (!strcasecmp(opt, "zrquality")) {
        i = atoi(param);
	if (i < 1 || i > 20) return ERR_OUT_OF_RANGE;
	quality = i;
	return 1;
    }else if (!strcasecmp(opt, "zrnorm")) {
	if (param == NULL) return ERR_MISSING_PARAM;
	if (!strcasecmp(param, "NTSC")) {
            mp_msg(MSGT_VO, MSGL_V, "zr: Norm set to NTSC\n");
            norm = VIDEO_MODE_NTSC;
	    return 1;
	} else if (!strcasecmp(param, "PAL")) {
	    mp_msg(MSGT_VO, MSGL_V, "zr: Norm set to PAL\n");
            norm = VIDEO_MODE_PAL;
	    return 1;
	} else {
           return ERR_OUT_OF_RANGE;
        }
    }else if (!strcasecmp(opt, "zrhelp")){
	printf("Help for -vo zr: Zoran ZR360[56]7/ZR36060 based MJPEG capture/playback cards\n");
	printf("\n");
	printf("Here are the zr options:\n");
	printf(
		    "\n"
		    "  -zrcrop     specify part of the input image that\n"
		    "              you want to see as an x-style geometry string\n"
		    "              example: -zrcrop 352x288+16+0\n"
		    "  -zrvdec     vertical decimation 1, 2 or 4\n"
		    "  -zrhdec     horizontal decimation 1, 2 or 4\n"
		    "  -zrfd       decimation is only done if the primitive\n"
		    "              hardware upscaler can correct for the decimation,\n"
		    "              this switch allows you to see the effects\n"
		    "              of too much decimation\n"
		    "  -zrbw       display in black&white (speed increase)\n"
		    "  -zrquality  jpeg compression quality [BEST] 1 - 20 [VERY BAD]\n"
		    "  -zrdev      playback device (example -zrdev /dev/video1\n"
		    "  -zrnorm     specify norm PAL/NTSC [dev: leave at current setting]\n"
		    "\n"
	      );
	exit(0);
		
    }
    return ERR_NOT_AN_OPTION;
}

void vo_zr_revertoption(config_t* opt,char* param) {

  if (!strcasecmp(param, "zrdev")) {
    if(device)
      free(device);
    device=NULL;
  } else if (!strcasecmp(param, "zrbw"))
    bw=0;
  else if (!strcasecmp(param, "zrfd"))
    zrfd=0;
  else if (!strcasecmp(param, "zrcrop"))
    g.set = g.xoff = g.yoff = 0;
  else if (!strcasecmp(param, "zrhdec"))
    hdec = 1;
  else if (!strcasecmp(param, "zrvdec"))
    vdec = 1;
  else if (!strcasecmp(param, "zrquality"))
    quality = 1;
  else if (!strcasecmp(param, "zrnorm"))
    norm = VIDEO_MODE_AUTO;

}

static uint32_t preinit(const char *arg)
{
  return 0;
}

static void query_vaa(vo_vaa_t *vaa)
{
  memset(vaa,0,sizeof(vo_vaa_t));
}
