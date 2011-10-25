/*
 * dct36_3dnow.c - 3DNow! optimized dct36()
 *
 * This code based 'dct36_3dnow.s' by Syuuhei Kashiyama
 * <squash@mb.kcom.ne.jp>, only two types of changes have been made:
 *
 * - removed PREFETCH instruction for speedup
 * - changed function name for support 3DNow! automatic detection
 *
 * You can find Kashiyama's original 3dnow! support patch
 * (for mpg123-0.59o) at
 * http://user.ecc.u-tokyo.ac.jp/~g810370/linux-simd/ (Japanese).
 *
 * by KIMURA Takuhiro <kim@hannah.ipc.miyakyo-u.ac.jp> - until 31.Mar.1999
 *                    <kim@comtec.co.jp>               - after  1.Apr.1999
 *
 * Modified for use with MPlayer, for details see the changelog at
 * http://svn.mplayerhq.hu/mplayer/trunk/
 * $Id$
 *
 * Original disclaimer:
 *  The author of this program disclaim whole expressed or implied
 *  warranties with regard to this program, and in no event shall the
 *  author of this program liable to whatever resulted from the use of
 *  this program. Use it at your own risk.
 *
 * 2003/06/21: Moved to GCC inline assembly - Alex Beregszaszi
 */

#define real float /* ugly - but only way */

#include "mangle.h"

#ifdef __DCT36_OPTIMIZE_FOR_K7
void dct36_3dnowex(real *inbuf, real *o1,
    real *o2, real *wintab, real *tsbuf)
#else
void dct36_3dnow(real *inbuf, real *o1,
    real *o2, real *wintab, real *tsbuf)
#endif
{
    __asm__ __volatile__(
	"movq (%%eax),%%mm0\n\t"
	"movq 4(%%eax),%%mm1\n\t"
	"pfadd %%mm1,%%mm0\n\t"
	"movq %%mm0,4(%%eax)\n\t"
	"psrlq $32,%%mm1\n\t"
	"movq 12(%%eax),%%mm2\n\t"
	"punpckldq %%mm2,%%mm1\n\t"
	"pfadd %%mm2,%%mm1\n\t"
	"movq %%mm1,12(%%eax)\n\t"
	"psrlq $32,%%mm2\n\t"
	"movq 20(%%eax),%%mm3\n\t"
	"punpckldq %%mm3,%%mm2\n\t"
	"pfadd %%mm3,%%mm2\n\t"
	"movq %%mm2,20(%%eax)\n\t"
	"psrlq $32,%%mm3\n\t"
	"movq 28(%%eax),%%mm4\n\t"
	"punpckldq %%mm4,%%mm3\n\t"
	"pfadd %%mm4,%%mm3\n\t"
	"movq %%mm3,28(%%eax)\n\t"
	"psrlq $32,%%mm4\n\t"
	"movq 36(%%eax),%%mm5\n\t"
	"punpckldq %%mm5,%%mm4\n\t"
	"pfadd %%mm5,%%mm4\n\t"
	"movq %%mm4,36(%%eax)\n\t"
	"psrlq $32,%%mm5\n\t"
	"movq 44(%%eax),%%mm6\n\t"
	"punpckldq %%mm6,%%mm5\n\t"
	"pfadd %%mm6,%%mm5\n\t"
	"movq %%mm5,44(%%eax)\n\t"
	"psrlq $32,%%mm6\n\t"
	"movq 52(%%eax),%%mm7\n\t"
	"punpckldq %%mm7,%%mm6\n\t"
	"pfadd %%mm7,%%mm6\n\t"
	"movq %%mm6,52(%%eax)\n\t"
	"psrlq $32,%%mm7\n\t"
	"movq 60(%%eax),%%mm0\n\t"
	"punpckldq %%mm0,%%mm7\n\t"
	"pfadd %%mm0,%%mm7\n\t"
	"movq %%mm7,60(%%eax)\n\t"
	"psrlq $32,%%mm0\n\t"
	"movd 68(%%eax),%%mm1\n\t"
	"pfadd %%mm1,%%mm0\n\t"
	"movd %%mm0,68(%%eax)\n\t"
	"movd 4(%%eax),%%mm0\n\t"
	"movd 12(%%eax),%%mm1\n\t"
	"punpckldq %%mm1,%%mm0\n\t"
	"punpckldq 20(%%eax),%%mm1\n\t"
	"pfadd %%mm1,%%mm0\n\t"
	"movd %%mm0,12(%%eax)\n\t"
	"psrlq $32,%%mm0\n\t"
	"movd %%mm0,20(%%eax)\n\t"
	"psrlq $32,%%mm1\n\t"
	"movd 28(%%eax),%%mm2\n\t"
	"punpckldq %%mm2,%%mm1\n\t"
	"punpckldq 36(%%eax),%%mm2\n\t"
	"pfadd %%mm2,%%mm1\n\t"
	"movd %%mm1,28(%%eax)\n\t"
	"psrlq $32,%%mm1\n\t"
	"movd %%mm1,36(%%eax)\n\t"
	"psrlq $32,%%mm2\n\t"
	"movd 44(%%eax),%%mm3\n\t"
	"punpckldq %%mm3,%%mm2\n\t"
	"punpckldq 52(%%eax),%%mm3\n\t"
	"pfadd %%mm3,%%mm2\n\t"
	"movd %%mm2,44(%%eax)\n\t"
	"psrlq $32,%%mm2\n\t"
	"movd %%mm2,52(%%eax)\n\t"
	"psrlq $32,%%mm3\n\t"
	"movd 60(%%eax),%%mm4\n\t"
	"punpckldq %%mm4,%%mm3\n\t"
	"punpckldq 68(%%eax),%%mm4\n\t"
	"pfadd %%mm4,%%mm3\n\t"
	"movd %%mm3,60(%%eax)\n\t"
	"psrlq $32,%%mm3\n\t"
	"movd %%mm3,68(%%eax)\n\t"

	"movq 24(%%eax),%%mm0\n\t"
	"movq 48(%%eax),%%mm1\n\t"
	"movd "MANGLE(COS9)"+12,%%mm2\n\t"
	"punpckldq %%mm2,%%mm2\n\t"
	"movd "MANGLE(COS9)"+24,%%mm3\n\t"
	"punpckldq %%mm3,%%mm3\n\t"
	"pfmul %%mm2,%%mm0\n\t"
	"pfmul %%mm3,%%mm1\n\t"
	"pushl %%eax\n\t"
	"movl $1,%%eax\n\t"
	"movd %%eax,%%mm7\n\t"
	"pi2fd %%mm7,%%mm7\n\t"
	"popl %%eax\n\t"
	"movq 8(%%eax),%%mm2\n\t"
	"movd "MANGLE(COS9)"+4,%%mm3\n\t"
	"punpckldq %%mm3,%%mm3\n\t"
	"pfmul %%mm3,%%mm2\n\t"
	"pfadd %%mm0,%%mm2\n\t"
	"movq 40(%%eax),%%mm3\n\t"
	"movd "MANGLE(COS9)"+20,%%mm4\n\t"
	"punpckldq %%mm4,%%mm4\n\t"
	"pfmul %%mm4,%%mm3\n\t"
	"pfadd %%mm3,%%mm2\n\t"
	"movq 56(%%eax),%%mm3\n\t"
	"movd "MANGLE(COS9)"+28,%%mm4\n\t"
	"punpckldq %%mm4,%%mm4\n\t"
	"pfmul %%mm4,%%mm3\n\t"
	"pfadd %%mm3,%%mm2\n\t"
	"movq (%%eax),%%mm3\n\t"
	"movq 16(%%eax),%%mm4\n\t"
	"movd "MANGLE(COS9)"+8,%%mm5\n\t"
	"punpckldq %%mm5,%%mm5\n\t"
	"pfmul %%mm5,%%mm4\n\t"
	"pfadd %%mm4,%%mm3\n\t"
	"movq 32(%%eax),%%mm4\n\t"
	"movd "MANGLE(COS9)"+16,%%mm5\n\t"
	"punpckldq %%mm5,%%mm5\n\t"
	"pfmul %%mm5,%%mm4\n\t"
	"pfadd %%mm4,%%mm3\n\t"
	"pfadd %%mm1,%%mm3\n\t"
	"movq 64(%%eax),%%mm4\n\t"
	"movd "MANGLE(COS9)"+32,%%mm5\n\t"
	"punpckldq %%mm5,%%mm5\n\t"
	"pfmul %%mm5,%%mm4\n\t"
	"pfadd %%mm4,%%mm3\n\t"
	"movq %%mm2,%%mm4\n\t"
	"pfadd %%mm3,%%mm4\n\t"
	"movq %%mm7,%%mm5\n\t"
	"punpckldq "MANGLE(tfcos36)"+0,%%mm5\n\t"
	"pfmul %%mm5,%%mm4\n\t"
	"movq %%mm4,%%mm5\n\t"
	"pfacc %%mm5,%%mm5\n\t"
	"movd 108(%%edx),%%mm6\n\t"
	"punpckldq 104(%%edx),%%mm6\n\t"
	"pfmul %%mm6,%%mm5\n\t"
#ifdef __DCT36_OPTIMIZE_FOR_K7
	"pswapd %%mm5,%%mm5\n\t"
	"movq %%mm5,32(%%ecx)\n\t"
#else
	"movd %%mm5,36(%%ecx)\n\t"
	"psrlq $32,%%mm5\n\t"
	"movd %%mm5,32(%%ecx)\n\t"
#endif
	"movq %%mm4,%%mm6\n\t"
	"punpckldq %%mm6,%%mm5\n\t"
	"pfsub %%mm6,%%mm5\n\t"
	"punpckhdq %%mm5,%%mm5\n\t"
	"movd 32(%%edx),%%mm6\n\t"
	"punpckldq 36(%%edx),%%mm6\n\t"
	"pfmul %%mm6,%%mm5\n\t"
	"movd 32(%%esi),%%mm6\n\t"
	"punpckldq 36(%%esi),%%mm6\n\t"
	"pfadd %%mm6,%%mm5\n\t"
	"movd %%mm5,1024(%%ebx)\n\t"
	"psrlq $32,%%mm5\n\t"
	"movd %%mm5,1152(%%ebx)\n\t"
	"movq %%mm3,%%mm4\n\t"
	"pfsub %%mm2,%%mm4\n\t"
	"movq %%mm7,%%mm5\n\t"
	"punpckldq "MANGLE(tfcos36)"+32,%%mm5\n\t"
	"pfmul %%mm5,%%mm4\n\t"
	"movq %%mm4,%%mm5\n\t"
	"pfacc %%mm5,%%mm5\n\t"
	"movd 140(%%edx),%%mm6\n\t"
	"punpckldq 72(%%edx),%%mm6\n\t"
	"pfmul %%mm6,%%mm5\n\t"
	"movd %%mm5,68(%%ecx)\n\t"
	"psrlq $32,%%mm5\n\t"
	"movd %%mm5,0(%%ecx)\n\t"
	"movq %%mm4,%%mm6\n\t"
	"punpckldq %%mm6,%%mm5\n\t"
	"pfsub %%mm6,%%mm5\n\t"
	"punpckhdq %%mm5,%%mm5\n\t"
	"movd 0(%%edx),%%mm6\n\t"
	"punpckldq 68(%%edx),%%mm6\n\t"
	"pfmul %%mm6,%%mm5\n\t"
	"movd 0(%%esi),%%mm6\n\t"
	"punpckldq 68(%%esi),%%mm6\n\t"
	"pfadd %%mm6,%%mm5\n\t"
	"movd %%mm5,0(%%ebx)\n\t"
	"psrlq $32,%%mm5\n\t"
	"movd %%mm5,2176(%%ebx)\n\t"
	"movq 8(%%eax),%%mm2\n\t"
	"movq 40(%%eax),%%mm3\n\t"
	"pfsub %%mm3,%%mm2\n\t"
	"movq 56(%%eax),%%mm3\n\t"
	"pfsub %%mm3,%%mm2\n\t"
	"movd "MANGLE(COS9)"+12,%%mm3\n\t"
	"punpckldq %%mm3,%%mm3\n\t"
	"pfmul %%mm3,%%mm2\n\t"
	"movq 16(%%eax),%%mm3\n\t"
	"movq 32(%%eax),%%mm4\n\t"
	"pfsub %%mm4,%%mm3\n\t"
	"movq 64(%%eax),%%mm4\n\t"
	"pfsub %%mm4,%%mm3\n\t"
	"movd "MANGLE(COS9)"+24,%%mm4\n\t"
	"punpckldq %%mm4,%%mm4\n\t"
	"pfmul %%mm4,%%mm3\n\t"
	"movq 48(%%eax),%%mm4\n\t"
	"pfsub %%mm4,%%mm3\n\t"
	"movq (%%eax),%%mm4\n\t"
	"pfadd %%mm4,%%mm3\n\t"
	"movq %%mm2,%%mm4\n\t"
	"pfadd %%mm3,%%mm4\n\t"
	"movq %%mm7,%%mm5\n\t"
	"punpckldq "MANGLE(tfcos36)"+4,%%mm5\n\t"
	"pfmul %%mm5,%%mm4\n\t"
	"movq %%mm4,%%mm5\n\t"
	"pfacc %%mm5,%%mm5\n\t"
	"movd 112(%%edx),%%mm6\n\t"
	"punpckldq 100(%%edx),%%mm6\n\t"
	"pfmul %%mm6,%%mm5\n\t"
	"movd %%mm5,40(%%ecx)\n\t"
	"psrlq $32,%%mm5\n\t"
	"movd %%mm5,28(%%ecx)\n\t"
	"movq %%mm4,%%mm6\n\t"
	"punpckldq %%mm6,%%mm5\n\t"
	"pfsub %%mm6,%%mm5\n\t"
	"punpckhdq %%mm5,%%mm5\n\t"
	"movd 28(%%edx),%%mm6\n\t"
	"punpckldq 40(%%edx),%%mm6\n\t"
	"pfmul %%mm6,%%mm5\n\t"
	"movd 28(%%esi),%%mm6\n\t"
	"punpckldq 40(%%esi),%%mm6\n\t"
	"pfadd %%mm6,%%mm5\n\t"
	"movd %%mm5,896(%%ebx)\n\t"
	"psrlq $32,%%mm5\n\t"
	"movd %%mm5,1280(%%ebx)\n\t"
	"movq %%mm3,%%mm4\n\t"
	"pfsub %%mm2,%%mm4\n\t"
	"movq %%mm7,%%mm5\n\t"
	"punpckldq "MANGLE(tfcos36)"+28,%%mm5\n\t"
	"pfmul %%mm5,%%mm4\n\t"
	"movq %%mm4,%%mm5\n\t"
	"pfacc %%mm5,%%mm5\n\t"
	"movd 136(%%edx),%%mm6\n\t"
	"punpckldq 76(%%edx),%%mm6\n\t"
	"pfmul %%mm6,%%mm5\n\t"
	"movd %%mm5,64(%%ecx)\n\t"
	"psrlq $32,%%mm5\n\t"
	"movd %%mm5,4(%%ecx)\n\t"
	"movq %%mm4,%%mm6\n\t"
	"punpckldq %%mm6,%%mm5\n\t"
	"pfsub %%mm6,%%mm5\n\t"
	"punpckhdq %%mm5,%%mm5\n\t"
	"movd 4(%%edx),%%mm6\n\t"
	"punpckldq 64(%%edx),%%mm6\n\t"
	"pfmul %%mm6,%%mm5\n\t"
	"movd 4(%%esi),%%mm6\n\t"
	"punpckldq 64(%%esi),%%mm6\n\t"
	"pfadd %%mm6,%%mm5\n\t"
	"movd %%mm5,128(%%ebx)\n\t"
	"psrlq $32,%%mm5\n\t"
	"movd %%mm5,2048(%%ebx)\n\t"

	"movq 8(%%eax),%%mm2\n\t"
	"movd "MANGLE(COS9)"+20,%%mm3\n\t"
	"punpckldq %%mm3,%%mm3\n\t"
	"pfmul %%mm3,%%mm2\n\t"
	"pfsub %%mm0,%%mm2\n\t"
	"movq 40(%%eax),%%mm3\n\t"
	"movd "MANGLE(COS9)"+28,%%mm4\n\t"
	"punpckldq %%mm4,%%mm4\n\t"
	"pfmul %%mm4,%%mm3\n\t"
	"pfsub %%mm3,%%mm2\n\t"
	"movq 56(%%eax),%%mm3\n\t"
	"movd "MANGLE(COS9)"+4,%%mm4\n\t"
	"punpckldq %%mm4,%%mm4\n\t"
	"pfmul %%mm4,%%mm3\n\t"
	"pfadd %%mm3,%%mm2\n\t"
	"movq (%%eax),%%mm3\n\t"
	"movq 16(%%eax),%%mm4\n\t"
	"movd "MANGLE(COS9)"+32,%%mm5\n\t"
	"punpckldq %%mm5,%%mm5\n\t"
	"pfmul %%mm5,%%mm4\n\t"
	"pfsub %%mm4,%%mm3\n\t"
	"movq 32(%%eax),%%mm4\n\t"
	"movd "MANGLE(COS9)"+8,%%mm5\n\t"
	"punpckldq %%mm5,%%mm5\n\t"
	"pfmul %%mm5,%%mm4\n\t"
	"pfsub %%mm4,%%mm3\n\t"
	"pfadd %%mm1,%%mm3\n\t"
	"movq 64(%%eax),%%mm4\n\t"
	"movd "MANGLE(COS9)"+16,%%mm5\n\t"
	"punpckldq %%mm5,%%mm5\n\t"
	"pfmul %%mm5,%%mm4\n\t"
	"pfadd %%mm4,%%mm3\n\t"
	"movq %%mm2,%%mm4\n\t"
	"pfadd %%mm3,%%mm4\n\t"
	"movq %%mm7,%%mm5\n\t"
	"punpckldq "MANGLE(tfcos36)"+8,%%mm5\n\t"
	"pfmul %%mm5,%%mm4\n\t"
	"movq %%mm4,%%mm5\n\t"
	"pfacc %%mm5,%%mm5\n\t"
	"movd 116(%%edx),%%mm6\n\t"
	"punpckldq 96(%%edx),%%mm6\n\t"
	"pfmul %%mm6,%%mm5\n\t"
	"movd %%mm5,44(%%ecx)\n\t"
	"psrlq $32,%%mm5\n\t"
	"movd %%mm5,24(%%ecx)\n\t"
	"movq %%mm4,%%mm6\n\t"
	"punpckldq %%mm6,%%mm5\n\t"
	"pfsub %%mm6,%%mm5\n\t"
	"punpckhdq %%mm5,%%mm5\n\t"
	"movd 24(%%edx),%%mm6\n\t"
	"punpckldq 44(%%edx),%%mm6\n\t"
	"pfmul %%mm6,%%mm5\n\t"
	"movd 24(%%esi),%%mm6\n\t"
	"punpckldq 44(%%esi),%%mm6\n\t"
	"pfadd %%mm6,%%mm5\n\t"
	"movd %%mm5,768(%%ebx)\n\t"
	"psrlq $32,%%mm5\n\t"
	"movd %%mm5,1408(%%ebx)\n\t"
	"movq %%mm3,%%mm4\n\t"
	"pfsub %%mm2,%%mm4\n\t"
	"movq %%mm7,%%mm5\n\t"
	"punpckldq "MANGLE(tfcos36)"+24,%%mm5\n\t"
	"pfmul %%mm5,%%mm4\n\t"
	"movq %%mm4,%%mm5\n\t"
	"pfacc %%mm5,%%mm5\n\t"
	"movd 132(%%edx),%%mm6\n\t"
	"punpckldq 80(%%edx),%%mm6\n\t"
	"pfmul %%mm6,%%mm5\n\t"
	"movd %%mm5,60(%%ecx)\n\t"
	"psrlq $32,%%mm5\n\t"
	"movd %%mm5,8(%%ecx)\n\t"
	"movq %%mm4,%%mm6\n\t"
	"punpckldq %%mm6,%%mm5\n\t"
	"pfsub %%mm6,%%mm5\n\t"
	"punpckhdq %%mm5,%%mm5\n\t"
	"movd 8(%%edx),%%mm6\n\t"
	"punpckldq 60(%%edx),%%mm6\n\t"
	"pfmul %%mm6,%%mm5\n\t"
	"movd 8(%%esi),%%mm6\n\t"
	"punpckldq 60(%%esi),%%mm6\n\t"
	"pfadd %%mm6,%%mm5\n\t"
	"movd %%mm5,256(%%ebx)\n\t"
	"psrlq $32,%%mm5\n\t"
	"movd %%mm5,1920(%%ebx)\n\t"
	"movq 8(%%eax),%%mm2\n\t"
	"movd "MANGLE(COS9)"+28,%%mm3\n\t"
	"punpckldq %%mm3,%%mm3\n\t"
	"pfmul %%mm3,%%mm2\n\t"
	"pfsub %%mm0,%%mm2\n\t"
	"movq 40(%%eax),%%mm3\n\t"
	"movd "MANGLE(COS9)"+4,%%mm4\n\t"
	"punpckldq %%mm4,%%mm4\n\t"
	"pfmul %%mm4,%%mm3\n\t"
	"pfadd %%mm3,%%mm2\n\t"
	"movq 56(%%eax),%%mm3\n\t"
	"movd "MANGLE(COS9)"+20,%%mm4\n\t"
	"punpckldq %%mm4,%%mm4\n\t"
	"pfmul %%mm4,%%mm3\n\t"
	"pfsub %%mm3,%%mm2\n\t"
	"movq (%%eax),%%mm3\n\t"
	"movq 16(%%eax),%%mm4\n\t"
	"movd "MANGLE(COS9)"+16,%%mm5\n\t"
	"punpckldq %%mm5,%%mm5\n\t"
	"pfmul %%mm5,%%mm4\n\t"
	"pfsub %%mm4,%%mm3\n\t"
	"movq 32(%%eax),%%mm4\n\t"
	"movd "MANGLE(COS9)"+32,%%mm5\n\t"
	"punpckldq %%mm5,%%mm5\n\t"
	"pfmul %%mm5,%%mm4\n\t"
	"pfadd %%mm4,%%mm3\n\t"
	"pfadd %%mm1,%%mm3\n\t"
	"movq 64(%%eax),%%mm4\n\t"
	"movd "MANGLE(COS9)"+8,%%mm5\n\t"
	"punpckldq %%mm5,%%mm5\n\t"
	"pfmul %%mm5,%%mm4\n\t"
	"pfsub %%mm4,%%mm3\n\t"
	"movq %%mm2,%%mm4\n\t"
	"pfadd %%mm3,%%mm4\n\t"
	"movq %%mm7,%%mm5\n\t"
	"punpckldq "MANGLE(tfcos36)"+12,%%mm5\n\t"
	"pfmul %%mm5,%%mm4\n\t"
	"movq %%mm4,%%mm5\n\t"
	"pfacc %%mm5,%%mm5\n\t"
	"movd 120(%%edx),%%mm6\n\t"
	"punpckldq 92(%%edx),%%mm6\n\t"
	"pfmul %%mm6,%%mm5\n\t"
	"movd %%mm5,48(%%ecx)\n\t"
	"psrlq $32,%%mm5\n\t"
	"movd %%mm5,20(%%ecx)\n\t"
	"movq %%mm4,%%mm6\n\t"
	"punpckldq %%mm6,%%mm5\n\t"
	"pfsub %%mm6,%%mm5\n\t"
	"punpckhdq %%mm5,%%mm5\n\t"
	"movd 20(%%edx),%%mm6\n\t"
	"punpckldq 48(%%edx),%%mm6\n\t"
	"pfmul %%mm6,%%mm5\n\t"
	"movd 20(%%esi),%%mm6\n\t"
	"punpckldq 48(%%esi),%%mm6\n\t"
	"pfadd %%mm6,%%mm5\n\t"
	"movd %%mm5,640(%%ebx)\n\t"
	"psrlq $32,%%mm5\n\t"
	"movd %%mm5,1536(%%ebx)\n\t"
	"movq %%mm3,%%mm4\n\t"
	"pfsub %%mm2,%%mm4\n\t"
	"movq %%mm7,%%mm5\n\t"
	"punpckldq "MANGLE(tfcos36)"+20,%%mm5\n\t"
	"pfmul %%mm5,%%mm4\n\t"
	"movq %%mm4,%%mm5\n\t"
	"pfacc %%mm5,%%mm5\n\t"
	"movd 128(%%edx),%%mm6\n\t"
	"punpckldq 84(%%edx),%%mm6\n\t"
	"pfmul %%mm6,%%mm5\n\t"
	"movd %%mm5,56(%%ecx)\n\t"
	"psrlq $32,%%mm5\n\t"
	"movd %%mm5,12(%%ecx)\n\t"
	"movq %%mm4,%%mm6\n\t"
	"punpckldq %%mm6,%%mm5\n\t"
	"pfsub %%mm6,%%mm5\n\t"
	"punpckhdq %%mm5,%%mm5\n\t"
	"movd 12(%%edx),%%mm6\n\t"
	"punpckldq 56(%%edx),%%mm6\n\t"
	"pfmul %%mm6,%%mm5\n\t"
	"movd 12(%%esi),%%mm6\n\t"
	"punpckldq 56(%%esi),%%mm6\n\t"
	"pfadd %%mm6,%%mm5\n\t"
	"movd %%mm5,384(%%ebx)\n\t"
	"psrlq $32,%%mm5\n\t"
	"movd %%mm5,1792(%%ebx)\n\t"

	"movq (%%eax),%%mm4\n\t"
	"movq 16(%%eax),%%mm3\n\t"
	"pfsub %%mm3,%%mm4\n\t"
	"movq 32(%%eax),%%mm3\n\t"
	"pfadd %%mm3,%%mm4\n\t"
	"movq 48(%%eax),%%mm3\n\t"
	"pfsub %%mm3,%%mm4\n\t"
	"movq 64(%%eax),%%mm3\n\t"
	"pfadd %%mm3,%%mm4\n\t"
	"movq %%mm7,%%mm5\n\t"
	"punpckldq "MANGLE(tfcos36)"+16,%%mm5\n\t"
	"pfmul %%mm5,%%mm4\n\t"
	"movq %%mm4,%%mm5\n\t"
	"pfacc %%mm5,%%mm5\n\t"
	"movd 124(%%edx),%%mm6\n\t"
	"punpckldq 88(%%edx),%%mm6\n\t"
	"pfmul %%mm6,%%mm5\n\t"
	"movd %%mm5,52(%%ecx)\n\t"
	"psrlq $32,%%mm5\n\t"
	"movd %%mm5,16(%%ecx)\n\t"
	"movq %%mm4,%%mm6\n\t"
	"punpckldq %%mm6,%%mm5\n\t"
	"pfsub %%mm6,%%mm5\n\t"
	"punpckhdq %%mm5,%%mm5\n\t"
	"movd 16(%%edx),%%mm6\n\t"
	"punpckldq 52(%%edx),%%mm6\n\t"
	"pfmul %%mm6,%%mm5\n\t"
	"movd 16(%%esi),%%mm6\n\t"
	"punpckldq 52(%%esi),%%mm6\n\t"
	"pfadd %%mm6,%%mm5\n\t"
	"movd %%mm5,512(%%ebx)\n\t"
	"psrlq $32,%%mm5\n\t"
	"movd %%mm5,1664(%%ebx)\n\t"

	"femms\n\t"
	:
	: "a" (inbuf), "S" (o1), "c" (o2), "d" (wintab), "b" (tsbuf)
	: "memory");
}