// MPlayer Turkish Translation
// Translated by: "heart_of_the_ocean" Murat ALKAN

// ========================= MPlayer help ===========================

#ifdef HELP_MP_DEFINE_STATIC
static char help_text[]=
"Kullan�m:   mplayer [options] [adres|yer/]dosyaismi\n"
"\n"
"Genel se�enekler: (T�m se�enekleri g�rmek i�in man sayfalar�na bak�n)\n"
" -vo <drv[:ayg�t]> video ��k�� s�r�c�s�n� & ayg�t�n� se�in ('-vo help' ile listeyi g�rebilirsiniz)\n"
" -ao <drv[:ayg�t]> ses ��k�� s�r�c�s�n� & ayg�t�n� se�in ('-ao help' ile listeyi g�rebilirsiniz)\n"
#ifdef HAVE_VCD
" vcd://<trackno>  vcd yi �almaya ba�lar. (Video CD) VCD track numaras�n� girebilirsiniz\n"
#endif
#ifdef USE_DVDREAD
" dvd://<ba�l�kno>  DVD ba�l��� �al. Ba�l�k numaras�n� gireblirsiniz.\n"
" -alang/-slang    DVD dublaj/altyaz� dili se�in (2-char country codu taraf�ndan)\n"
#endif
" -ss <zamanpoz>    Verilmi� pozisyonu ara (saniye yada hh:mm:ss)\n"
" -nosound          Sesleri �almaz\n"
" -fs -vm -zoom     Tam ekran �al��t�rma se�enekleri (fullscr,vidmode chg,softw.scale)\n"
" -x <x> -y <y>     Ekran ��z�n�rl�l���n� ayarlar (-vm veya -zoom kullan�m� i�in)\n"
" -sub <dosya>      Kullanmak i�in bir altyazi se�er (-subfps, -subdelay ada bak�n)\n"
" -playlist <dosya> Playlist dosyas� se�\n"
" -vid x -aid y     Video se�mek i�in se�enekler (x) ve ses se�mek i�in se�enkler (y)\n"
" -fps x -srate y   Video de�i�tirmek i�in se�enekler (x fps) ve ses (y Hz) oran�\n"
" -pp <kalite>      postprocessing filtresini aktifle�tirir (detaylar i�in man sayfalar�na bak�n)\n"
" -framedrop        frame dropping i aktifle�tirir (yava� bilgisayarlar i�in)\n"
"\n"
"Ba�l�ca Tu�lar: (t�m liste i�in man sayfalar�na bak�n, input.conf'u kontrol edin)\n"
" <-  veya  ->       geri sar/ileri sar (10 saniye)\n"
" yukar� veya asa��  geri sar/ileri sar  (1 dakika)\n"
" pgup veya pgdown   geri sar/ileri sar (10 dakika)\n"
" < veya >           Playlist te ileri/geri sar\n"
" p veya BO�LUK      �almay� duraklat (devam ettirmek i�in bir tu�a bas�n)\n"
" q veya ESC         �almay� durdur ve ��k\n"
" + veya -           Ses gecikmesini uygun hale getir  +/- 0.1 saniye\n"
" o                  OSD moduna ge�:  none / seekbar / seekbar+timer\n"
" * veya /           Sesi y�kselt yada al�at\n"
" z veya x           Altyaz� gecikmesini uygun hale getir  +/- 0.1 saniye\n"
" r veya t           Altyazi pozisyonunu uygun hale getir ,-vf expand 'ada bak�n\n"
"\n"
" * * * DETAYLAR ���N MAN SAYFALARINA BAKIN, GEL��M�� TU�LARI VE SE�ENEKLER� BULAB�L�RS�N�Z * * *\n"
"\n";
#endif

// ========================= MPlayer messages ===========================

// mplayer.c:

#define MSGTR_Exiting "\n��k�l�yor...\n"
#define MSGTR_ExitingHow "\n��k�l�yor... (%s)\n"
#define MSGTR_Exit_quit "��k��"
#define MSGTR_Exit_eof "Dosyan�n Sonu"
#define MSGTR_Exit_error "�l�mc�l Hata"
#define MSGTR_IntBySignal "\nMPlayer %s mod�l�ndeki %d hatas� ile kapand�\n"
#define MSGTR_NoHomeDir "ANAD�Z�N bulunumad�\n"
#define MSGTR_GetpathProblem "get_path(\"config\") problemi\n"
#define MSGTR_CreatingCfgFile "Ayar dosyas� olu�turuluyor: %s\n"
#define MSGTR_InvalidAOdriver "Yanl�� Ses ��k�� s�r�c�s� ad�: %s\n'-ao help' Komutunu kullanarak kullan�labilir ses ��k�� s�r�c�leri g�rebilirsiniz.\n"
#define MSGTR_CopyCodecsConf "(etc/codecs.conf'u (MPlayer kaynak a�ac�ndan) ~/.mplayer/codecs.conf a kopyalay�n/ba� yap�n)\n"
#define MSGTR_BuiltinCodecsConf "G�m�l� codecs.conf dosyas� kullan�l�yor\n"
#define MSGTR_CantLoadFont "Yaz�tipi a��lamad�: %s\n"
#define MSGTR_CantLoadSub "Altyaz� a��lamad�: %s\n"
#define MSGTR_DumpSelectedStreamMissing "bo�alt�m: �L�MC�L: se�ili format hatal�!\n"
#define MSGTR_CantOpenDumpfile "dump(bo�alt�m) dosyas� a��lamad�!!!\n"
#define MSGTR_CoreDumped "Program kapand� :)\n"
#define MSGTR_FPSnotspecified "Ba�l�ktaki FPS se�ili de�il (veya hatal�)! -fps komutunu kullan�n!\n"
#define MSGTR_TryForceAudioFmtStr "Ses codecleri s�r�c� ailesi �al��maya zorlan�yor %s...\n"
#define MSGTR_CantFindAudioCodec "0x%X! Ses format� i�in codec bulunamad�\n"
#define MSGTR_TryForceVideoFmtStr "Video codec s�r�c�s� zorlanmaya �al���l�yor %s...\n"
#define MSGTR_CantFindVideoCodec "Se�ilmi� -vo s�r�c�s� ve video format� 0x%X i�in Codec bulunamad�!\n"
#define MSGTR_VOincompCodec "�zg�n�z, se�ili video_��k�� s�r�c�s� bu codec ile �ak���yor.\n"
#define MSGTR_CannotInitVO "�L�MC�L: Video s�r�c�s� y�klenemedi!\n"
#define MSGTR_CannotInitAO " Ses s�r�c�s� a��lamad�/�ali�mad� -> ses yok\n"
#define MSGTR_StartPlaying "�almaya ba�lan�yor...\n"

#define MSGTR_SystemTooSlow "\n\n"\
"         ************************************************\n"\
"         ****      Sisteminiz bunu �almak i�in �ok YAVA�!     ****\n"\
"         ************************************************\n"\
"!!!  Muhtemel nedenler, problemler,��z�mleri: \n"\
"- En genel: bozuk/hatal� _ses_ kart�. ��z�m: -ao sdl veya ba�ka bir�ey deneyin\n"\
"  ALSA 0.9 i�in ALSA 0.5 veya OSS em�lasyonu. DOCS/HTML/en/devices.html#audio-dev dosyas�na g�zat�n!\n"\
"  -autosync 30 veya ba�ka de�erlerle denemeler yapabilirsiniz.\n"\
"- Yava� Video ��k���.  -vo komutu ile ba�ka s�r�c� se�in(liste i�in: -vo help) veya\n"\
"  -framedrop ile deneyin!  DOCS/HTML/en/devices.html#video-dev dosyas�na video h�zland�rma i�in g�zat�n.\n"\
"- Yava� CPU. B�y�k bir DVD/divx i yava� bir CPU ile �al��t�rmay�n! -hardframedrop u\n"\
"kullan�n. -Bozuk Dosya. �e�itli se�enekler deneyin: -nobps  -ni  -mc 0  -forceidx gibi.\n"\
"- Yava� s�r�c�den �alacaksan�z (nfs/smb aglar�, dvd, vcd v.b.) -cache 8192  i deneyin.\n"\
"-  -cache ile bo�lukland�r�lmami� AVI dosyas�m� a��yorsunuz? -nocache ile kullanin.\n"\
"Bunlari yapt���n�zda bir�ey de�i�miyorsa, DOCS/HTML/en/bugreports.html dosyas�na g�zat�n!\n\n"

#define MSGTR_NoGui "MPlayer GRAF�K ARAB�R�MS�Z se�ene�iyle olu�turulmu�!\n"
#define MSGTR_GuiNeedsX "MPlayer GRAF�K ARAB�R�M� X11 i gerektirir!\n"
#define MSGTR_Playing "%s �al�n�yor\n"
#define MSGTR_NoSound "Ses: ses yok!!!\n"
#define MSGTR_FPSforced "FPS  %5.3f  olmak zorunda(ftime: %5.3f)\n"
#define MSGTR_CompiledWithRuntimeDetection "MPlayer RUNTIME CPU Detection ile olu�turulmu�. - dikkat, bu h�zl� de�ildir! En iyi performans� alabilmek i�in, MPlayer � -disable-runtime-cpudetection se�ene�i ile tekrar compile edin.\n"
#define MSGTR_CompiledWithCPUExtensions "x86 CPU i�in eklerle olu�turulmu�:"
#define MSGTR_AvailableVideoOutputDrivers "Video  ��k��  s�r�c�leri kullan�labilir:\n"
#define MSGTR_AvailableAudioOutputDrivers "Ses  ��k�� s�r�c�leri kullan�labilir:\n"
#define MSGTR_AvailableAudioCodecs "Ses codecleri kullan�labilir:\n"
#define MSGTR_AvailableVideoCodecs "Video Codecleri kullan�labilir:\n"
#define MSGTR_AvailableAudioFm "\nSes codec aileleri/s�r�c�leri (g�m�l�) kullan�labilir:\n"
#define MSGTR_AvailableVideoFm "\nVideo codec aileleri/s�r�c�leri (g�m�l�) kullan�labilir:\n"
#define MSGTR_UsingRTCTiming "Linux s�r�c� RTC zamanlamas� kullan�l�yor(%ldHz)\n"
#define MSGTR_CannotReadVideoProperties "Video: �zellikler okunamad�\n"
#define MSGTR_NoStreamFound "Bi�im bulunamad�\n"
#define MSGTR_ErrorInitializingVODevice "Video ��k�� (-vo) s�r�c�s�n� a�arken/y�klerken hata!\n"
#define MSGTR_ForcedVideoCodec "Video codecine zorland�: %s\n"
#define MSGTR_ForcedAudioCodec "Ses codecine zorland�: %s\n"
#define MSGTR_AODescription_AOAuthor "AO: A��klama: %s\nAO: Yapan: %s\n"
#define MSGTR_AOComment "AO: Yorum: %s\n"
#define MSGTR_Video_NoVideo "Video: video yok!!!\n"
#define MSGTR_NotInitializeVOPorVO "\n�L�MC�L: Video Filtreleri (-vf) veya video ��k��� (-vo) y�klenemedi!\n"
#define MSGTR_Paused "\n------ DURAKLADI -------\r"
#define MSGTR_PlaylistLoadUnable "\nPlaylist y�klenemedi %s\n"

// mencoder.c:

#define MSGTR_UsingPass3ControllFile "pass3 kontrol dosyas� kullan�l�yor: %s\n"
#define MSGTR_MissingFilename "\nHatal� dosyaad�!\n\n"
#define MSGTR_CannotOpenFile_Device "dosya/ayg�t a��lamad�\n"
#define MSGTR_CannotOpenDemuxer "Ayr��t�r�c� a��lamad�\n"
#define MSGTR_NoAudioEncoderSelected "\nSes �eviricisi (-oac) se�ilmemi�!  Birtane se�in yada -nosound u kullan�n. Yard�m i�in: -oac help \n"
#define MSGTR_NoVideoEncoderSelected "\nVideo �eviricisi (-ovc) se�ilmemi�! Birtane se�in, Yard�m i�in: -ovc help yaz�n\n"
#define MSGTR_CannotOpenOutputFile "��k�� dosyas� a��lamad� '%s'\n"
#define MSGTR_EncoderOpenFailed "�evirici a��lamad�\n"
#define MSGTR_ForcingOutputFourcc "��k�� fourcc den zorlan�yor: %x [%.4s]'a\n"
#define MSGTR_WritingAVIHeader "AVI Ba�l��� yaz�l�yor...\n"
#define MSGTR_DuplicateFrames "\n�ift %d �er�evesi/leri!!!    \n"
#define MSGTR_SkipFrame "\n�er�eve atla!!!    \n"
#define MSGTR_ErrorWritingFile "%s: dosya yazarken hata.\n"
#define MSGTR_WritingAVIIndex "\nAVI i�eri�i yaz�l�yor...\n"
#define MSGTR_FixupAVIHeader "AVI Ba�l��� d�zeltiliyor...\n"
#define MSGTR_RecommendedVideoBitrate "%s CD si i�in tavsiye edilen video bitrate: %d\n"
#define MSGTR_VideoStreamResult "\nVideo bi�imi: %8.3f kbit/s  (%d bps)  boyut: %d byte  %5.3f saniye  %d �er�eve\n"
#define MSGTR_AudioStreamResult "\nSes bi�imi: %8.3f kbit/s  (%d bps)  boyut: %d byte    %5.3f saniye\n"

// open.c, stream.c:
#define MSGTR_CdDevNotfound "CD-ROM S�r�c�s� '%s' bulunamad�!\n"
#define MSGTR_ErrTrackSelect "VCD Track i se�ilirken hata!"
#define MSGTR_ReadSTDIN "stdin'den okunuyor...\n"
#define MSGTR_UnableOpenURL "URL a��lamad�: %s\n"
#define MSGTR_ConnToServer "Sunucuya ba�lan�ld�: %s\n"
#define MSGTR_FileNotFound "Dosya bulunamad�: '%s'\n"

#define MSGTR_SMBInitError "libsmbclient k�t�phanesi �al��t�r�lamad�: %d\n"
#define MSGTR_SMBFileNotFound "A�dan a��lamad�: '%s'\n"
#define MSGTR_SMBNotCompiled "MPlayer SMB okuma deste�i ile olu�turulmam��.\n"

#define MSGTR_CantOpenDVD "DVD s�r�c�s� a��lamad�: %s\n"
#define MSGTR_DVDwait "Disk yap�s� okunuyor, l�tfen bekleyin...\n"
#define MSGTR_DVDnumTitles "Bu DVD de %d ba�l�klar� var.\n"
#define MSGTR_DVDinvalidTitle "Yanl�� DVD ba�l�k numaras�: %d\n"
#define MSGTR_DVDnumChapters "Bu DVD Ba�l���nda de %d b�l�mleri var.\n"
#define MSGTR_DVDinvalidChapter "Yanl�� DVD b�l�m numaras�: %d\n"
#define MSGTR_DVDnumAngles "Bu DVD ba�l���nda %d angles lar� var.\n"
#define MSGTR_DVDinvalidAngle "Yanl�� DVD angle numaras�: %d\n"
#define MSGTR_DVDnoIFO "DVD Ba�l��� i�in IFO dosyas� a��lam�yor %d.\n"
#define MSGTR_DVDnoVOBs " VOBS Ba�l��� a��lmad� (VTS_%02d_1.VOB).\n"
#define MSGTR_DVDopenOk "DVD ba�ar�yla a��ld�!\n"

// demuxer.c, demux_*.c:
#define MSGTR_AudioStreamRedefined "Dikkat! Ses bi�im ba�l��� %d tekrar atand�!\n"
#define MSGTR_VideoStreamRedefined "Dikkat! Video bi�im ba�l��� %d tekrar atand�!\n"
#define MSGTR_TooManyAudioInBuffer "\nDEMUXER: Buffer da bir�ok (%d in %d bytes) ses paketi var!\n"
#define MSGTR_TooManyVideoInBuffer "\nDEMUXER: Buffer da bir�ok  (%d in %d bytes) video packeti var!\n"
#define MSGTR_MaybeNI "Belki bo�luksuz bi�im/dosya �al�yor olabilirsiniz veya codec hatal�?\n" \
		      "-ni opsiyonuyla .AVI dosyalar� i�in, bo�luksuz �almay� modunu zorlay�n.\n"
#define MSGTR_SwitchToNi "\nK�t� bo�lukland�r�lm�� .AVI bulundu - -ni moduna ge�iliyor!\n"
#define MSGTR_Detected_XXX_FileFormat "%s Dosya format� bulundu!\n"
#define MSGTR_DetectedAudiofile "Ses dosyas� bulundu!\n"
#define MSGTR_NotSystemStream "MPEG Sistemi Bi�imi de�il... (belki Transport Bi�imi?)\n"
#define MSGTR_InvalidMPEGES "Yanl�� MPEG-ES bi�imi?? programc�larla bildirin, bu bir hata olabilir :(\n"
#define MSGTR_FormatNotRecognized "============ �zg�n�m, bu dosya bi�imi desteklenmiyor =============\n"\
				  "=== E�er bu dosya bir AVI, ASF veta MPEG bi�imi ise, program yazarlar�yla ba�lant� kurun! ===\n"
#define MSGTR_MissingVideoStream "Video bi�imi bulunamad�!\n"
#define MSGTR_MissingAudioStream "Ses bi�imi bulunamad�...  ->  ses yok\n"
#define MSGTR_MissingVideoStreamBug "Hatal� video bi�imi!? Programc�larla bildirin, bu bir hata olabilir :(\n"

#define MSGTR_DoesntContainSelectedStream "demux: Dosya se�ili video/ses i i�ermiyor.\n"

#define MSGTR_NI_Forced "Zorland�"
#define MSGTR_NI_Detected "Bulundu"
#define MSGTR_NI_Message "%s BO�LUKSUZ dosya-bi�imi!\n"

#define MSGTR_UsingNINI "BO�LUKSUZ Bozulma AVI dosya-bi�imi kullan�l�yor!\n"
#define MSGTR_CouldntDetFNo "Frame numaralar� bulunamad� (sade seek i�in)  \n"
#define MSGTR_CantSeekRawAVI "AVI Bi�imleri Raw da aranamad�! (Index zorunlu, -idx  komutuyla deneyin!)  \n"
#define MSGTR_CantSeekFile "Bu dosyada aranamaz!  \n"

#define MSGTR_MOVcomprhdr "MOV: ��k��t�r�lm�� bi�imler (�imdilik) deskteklenmiyor!\n"
#define MSGTR_MOVvariableFourCC "MOV: Dikkat! FOURCC bulundu!?\n"
#define MSGTR_MOVtooManyTrk "MOV: Dikkat! �ok fazla track!"
#define MSGTR_FoundAudioStream "==> Bulunan Ses Bi�imi: %d\n"
#define MSGTR_FoundVideoStream "==> Bulunan Video Bi�imi: %d\n"
#define MSGTR_DetectedTV "TV Bulundu! ;-)\n"
#define MSGTR_ErrorOpeningOGGDemuxer "ogg ayr��t�r�c�s� a��lamad�\n"
#define MSGTR_ASFSearchingForAudioStream "ASF: Ses bi�imi aran�yor (id:%d)\n"
#define MSGTR_CannotOpenAudioStream "Ses Bi�imi a��lamad�: %s\n"
#define MSGTR_CannotOpenSubtitlesStream "Altyaz� Bi�imi A��lamad�: %s\n"
#define MSGTR_OpeningAudioDemuxerFailed "Ses ayr��t�r�c�s� a��l�rken hata olu�tu: %s\n"
#define MSGTR_OpeningSubtitlesDemuxerFailed "Altyaz� Ayr��t�r�c�s� a��l�rken hata olu�tu: %s\n"
#define MSGTR_TVInputNotSeekable "TV ��k��� aranabilir de�il! (Muhtemelen arama kanal de�i�tirmek i�in olacak ;)\n"
#define MSGTR_DemuxerInfoAlreadyPresent "Ayr��t�r�c� bilgisi %s �nceden a��lm��!\n"
#define MSGTR_ClipInfo "Klip bilgisi: \n"

// dec_video.c & dec_audio.c:
#define MSGTR_CantOpenCodec "codec a��lamad�\n"
#define MSGTR_CantCloseCodec "codec kapat�lamad�\n"

#define MSGTR_MissingDLLcodec "HATA: Gerekli olan DirectShow codeci a��lamad�: %s\n"
#define MSGTR_ACMiniterror "Win32/ACM AUDIO codecleri y�klenemedi (DLL dosyas� eksik mi?)\n"
#define MSGTR_MissingLAVCcodec " '%s' codec i libavcodec de bulunamad�...\n"

#define MSGTR_MpegNoSequHdr "MPEG: �L�MC�L: S�ra ba�l��� i�in aran�rken EOF \n"
#define MSGTR_CannotReadMpegSequHdr "�L�MC�L: S�ra ba�l��� okunamad�!\n"
#define MSGTR_CannotReadMpegSequHdrEx "�L�MC�L: S�ra Ba�l��� eki okunamad�!\n"
#define MSGTR_BadMpegSequHdr "MPEG: Hatal� s�ra ba�l���!\n"
#define MSGTR_BadMpegSequHdrEx "MPEG: Hatal� s�ra ba�l��� eki!\n"

#define MSGTR_ShMemAllocFail "Payla��lm�� haf�za yerle�tirilemedi\n"
#define MSGTR_CantAllocAudioBuf "Ses ��k��� buffer� yerle�tirilemedi\n"

#define MSGTR_UnknownAudio "Bilinmeyen/hatal� ses bi�imi -> ses yok\n"

#define MSGTR_UsingExternalPP "[PP] Harici postprocessing filtresi kullan�l�yor, max q = %d\n"
#define MSGTR_UsingCodecPP "[PP] Codeclerin postprocessing i kullan�l�yor, max q = %d\n"
#define MSGTR_VideoAttributeNotSupportedByVO_VD "Video Bi�imi '%s' se�ili vo & vd taraf�ndan desteklenm�yor! \n"
#define MSGTR_VideoCodecFamilyNotAvailableStr "�stenilen video codec ailesi [%s] (vfm=%s) kullan�labilir de�il (compile ederken a��n!)\n"
#define MSGTR_AudioCodecFamilyNotAvailableStr "�stenilen ses codec ailesi [%s] (afm=%s) kullan�labilir de�il. (compile ederken a��n!)\n"
#define MSGTR_OpeningVideoDecoder "Video decoderi a��l�yor: [%s] %s\n"
#define MSGTR_OpeningAudioDecoder "Ses decoderi a��l�yor: [%s] %s\n"
#define MSGTR_UninitVideoStr "kapanan video: %s  \n"
#define MSGTR_UninitAudioStr "kapanan ses: %s  \n"
#define MSGTR_VDecoderInitFailed "VDecoder a��l��� ba�ar�s�z :(\n"
#define MSGTR_ADecoderInitFailed "ADecoder a��l��� ba�ar�s�z :(\n"
#define MSGTR_ADecoderPreinitFailed "ADecoder �na��l�� ba�ar�s�z :(\n"
#define MSGTR_AllocatingBytesForInputBuffer "dec_audio: Tayin ediliyor: %d byte(giri� i�in)\n"
#define MSGTR_AllocatingBytesForOutputBuffer "dec_audio: Tayin ediliyor %d + %d = %d byte  (��k�� buffer i i�in)\n"

// LIRC:
#define MSGTR_SettingUpLIRC "lirc deste�i ayarlan�yor...\n"
#define MSGTR_LIRCdisabled "Uzaktan kontrol sistemini kullanamayacaks�n�z\n"
#define MSGTR_LIRCopenfailed "lirc deste�i a��lamad�!\n"
#define MSGTR_LIRCcfgerr "LIRC ayar dosyas� okunamad� %s!\n"

// vf.c
#define MSGTR_CouldNotFindVideoFilter "Video filtresi bulunamad� '%s'\n"
#define MSGTR_CouldNotOpenVideoFilter "Video filtresi a��lamad� '%s'\n"
#define MSGTR_OpeningVideoFilter "Video filtresi a��l�yor: "
#define MSGTR_CannotFindColorspace "Genel renk se�imi bulunamad�, d�zeltmek i�in 'scale' ekleniyor :(\n"

// vd.c
#define MSGTR_CodecDidNotSet "VDec: codec ayarlanamad�: sh->disp_w ve sh->disp_h, ��z�lmeye �al���l�yor!\n"
#define MSGTR_VoConfigRequest "VDec: vo ayar iste�i - %d x %d (preferred csp: %s)\n"
#define MSGTR_CouldNotFindColorspace "Uyan renkler bulunamad� - -vf cetveli ile deneniyor...\n"
#define MSGTR_MovieAspectIsSet "Movie-G�r�n�m�: %.2f:1 - do�ru movie g�r�n�m i�in �nderecelendirme.\n"
#define MSGTR_MovieAspectUndefined "Movie-G�r�n�m� atanmam�� - �nderecelerndirme uygulanmad�.\n"

// ====================== GUI messages/buttons ========================

#ifdef HAVE_NEW_GUI

// --- labels ---
#define MSGTR_About "Hakk�nda"
#define MSGTR_FileSelect "Dosya Se�..."
#define MSGTR_SubtitleSelect "Altyaz� Se�..."
#define MSGTR_OtherSelect "Se�..."
#define MSGTR_AudioFileSelect "Ek ses kanal� se�..."
#define MSGTR_FontSelect "Yaz�tipi Se�..."
#define MSGTR_PlayList "PlayList"
#define MSGTR_Equalizer "Equalizer"
#define MSGTR_SkinBrowser "Skin Taray�c�"
#define MSGTR_Network "A� bi�imleri..."
#define MSGTR_Preferences "Se�enekler"
#define MSGTR_NoMediaOpened "Medya a��lmad�"
#define MSGTR_VCDTrack "VCD track %d"
#define MSGTR_NoChapter "b�l�m yok"
#define MSGTR_Chapter "b�l�m %d"
#define MSGTR_NoFileLoaded "dosya y�klenmedi"

// --- buttons ---
#define MSGTR_Ok "Tamam"
#define MSGTR_Cancel "�ptal"
#define MSGTR_Add "Ekle"
#define MSGTR_Remove "Sil"
#define MSGTR_Clear "Temizle"
#define MSGTR_Config "Ayarla"
#define MSGTR_ConfigDriver "S�r�c�y� Ayarla"
#define MSGTR_Browse "G�zat"

// --- error messages ---
#define MSGTR_NEMDB "�zg�n�m, buffer i�in yeterli haf�za yok."
#define MSGTR_NEMFMR "�zg�n�m, menu i�lemesi i�in yeterli haf�za yok."
#define MSGTR_IDFGCVD "�zg�n�m, GUI ile uyumlu video ��k�� s�r�c�s� bulunamad�."
#define MSGTR_NEEDLAVCFAME "�zg�n�m, MPEG olmayan dosyalar� DXR3/H+  ayg�t�n�zla �alamazs�n�z. \nL�tfen DXR3/H+ ayarlardaki lavc veya fame i etkinle�tirin."

// --- skin loader error messages
#define MSGTR_SKIN_ERRORMESSAGE "[skin] Hata : skin ayar dosyas� %d sat�r�: %s"
#define MSGTR_SKIN_WARNING1 "[skin] Dikkat: skin ayar dosyas�  %d sat�r�: widget bulundu ama \"section\" bulunamad� (%s)"
#define MSGTR_SKIN_WARNING2 "[skin] Dikkat: skin ayar dosyas�  %d sat�r�: widget bulundu ama \"subsection\" bulunamad� (%s)"
#define MSGTR_SKIN_BITMAP_16bit  "16 bit veya daha az resim desteklenmiyor (%s).\n"
#define MSGTR_SKIN_BITMAP_FileNotFound  "dosya bulunamad� (%s)\n"
#define MSGTR_SKIN_BITMAP_BMPReadError "BMP okuma hatas� (%s)\n"
#define MSGTR_SKIN_BITMAP_TGAReadError "TGA okuma hatas� (%s)\n"
#define MSGTR_SKIN_BITMAP_PNGReadError "PNG okuma hatas� (%s)\n"
#define MSGTR_SKIN_BITMAP_RLENotSupported "RLE paket TGA desteklenmiyor (%s)\n"
#define MSGTR_SKIN_BITMAP_UnknownFileType "bilinmeyen dosya tipi (%s)\n"
#define MSGTR_SKIN_BITMAP_ConvertError "24 bit den 32 bit e �evirme hatas� (%s)\n"
#define MSGTR_SKIN_BITMAP_UnknownMessage "Bilinmeyen mesaj: %s\n"
#define MSGTR_SKIN_FONT_NotEnoughtMemory "yetersiz haf�za\n"
#define MSGTR_SKIN_FONT_TooManyFontsDeclared "�ok fazla yaz�tipi tan�t�ld�\n"
#define MSGTR_SKIN_FONT_FontFileNotFound "yaz�tipi dosyas� bulunamad�\n"
#define MSGTR_SKIN_FONT_FontImageNotFound "yaz�tipi image dosyas� bulunamad�\n"
#define MSGTR_SKIN_FONT_NonExistentFontID "Varolmayan yaz�tipi tan�t�c�s� (%s)\n"
#define MSGTR_SKIN_UnknownParameter "bilinmeyen parametre (%s)\n"
#define MSGTR_SKIN_SKINCFG_SkinNotFound "Skin bulunamad� (%s).\n"
#define MSGTR_SKIN_SKINCFG_SkinCfgReadError "Skin ayar dosyas� okuma hatas� (%s).\n"
#define MSGTR_SKIN_LABEL "Skinler:"

// --- gtk menus
#define MSGTR_MENU_AboutMPlayer "MPlayer Hakk�nda"
#define MSGTR_MENU_Open "A�..."
#define MSGTR_MENU_PlayFile "Dosya �al..."
#define MSGTR_MENU_PlayVCD "VCD  �al..."
#define MSGTR_MENU_PlayDVD "DVD �al..."
#define MSGTR_MENU_PlayURL "URL �al..."
#define MSGTR_MENU_LoadSubtitle "Altyaz� y�kle..."
#define MSGTR_MENU_DropSubtitle "Altyaz� b�rak..."
#define MSGTR_MENU_LoadExternAudioFile "Ek ses dosyas� y�kle..."
#define MSGTR_MENU_Playing "�al�n�yor"
#define MSGTR_MENU_Play "�al"
#define MSGTR_MENU_Pause "Duraklat"
#define MSGTR_MENU_Stop "Dur"
#define MSGTR_MENU_NextStream "Sonraki bi�im"
#define MSGTR_MENU_PrevStream "�nceki bi�im"
#define MSGTR_MENU_Size "Boyut"
#define MSGTR_MENU_NormalSize "Normal boyut"
#define MSGTR_MENU_DoubleSize "B�y�k boyut"
#define MSGTR_MENU_FullScreen "Tam Ekran"
#define MSGTR_MENU_DVD "DVD"
#define MSGTR_MENU_VCD "VCD"
#define MSGTR_MENU_PlayDisc "�al..."
#define MSGTR_MENU_ShowDVDMenu "DVD men�s�n� g�ster"
#define MSGTR_MENU_Titles "Ba�l�klar"
#define MSGTR_MENU_Title "Ba�l�k %2d"
#define MSGTR_MENU_None "(yok)"
#define MSGTR_MENU_Chapters "B�l�mler"
#define MSGTR_MENU_Chapter "B�l�m %2d"
#define MSGTR_MENU_AudioLanguages "Ses Dilleri"
#define MSGTR_MENU_SubtitleLanguages "Altyaz� Dilleri"
#define MSGTR_MENU_PlayList "Playlist"
#define MSGTR_MENU_SkinBrowser "Skin se�ici"
#define MSGTR_MENU_Preferences "Se�enekler"
#define MSGTR_MENU_Exit "��k��..."
#define MSGTR_MENU_Mute "Sesi K�s"
#define MSGTR_MENU_Original "Orjinal"
#define MSGTR_MENU_AspectRatio "G�r�n�� Oran�"
#define MSGTR_MENU_AudioTrack "Ses track"
#define MSGTR_MENU_Track "Track %d"
#define MSGTR_MENU_VideoTrack "Video track"

// --- equalizer
#define MSGTR_EQU_Audio "Ses"
#define MSGTR_EQU_Video "Video"
#define MSGTR_EQU_Contrast "Kontrast: "
#define MSGTR_EQU_Brightness "A��kl�k: "
#define MSGTR_EQU_Hue "Hue: "
#define MSGTR_EQU_Saturation "Saturation: "
#define MSGTR_EQU_Front_Left "�n Sol"
#define MSGTR_EQU_Front_Right "�n Sa�"
#define MSGTR_EQU_Back_Left "Arka Sol"
#define MSGTR_EQU_Back_Right "Arka Sa�"
#define MSGTR_EQU_Center "Merkez"
#define MSGTR_EQU_Bass "Bass"
#define MSGTR_EQU_All "Hepsi"

// --- playlist
#define MSGTR_PLAYLIST_Path "Yer"
#define MSGTR_PLAYLIST_Selected "Se�ili dosyalar"
#define MSGTR_PLAYLIST_Files "Dosyalar"
#define MSGTR_PLAYLIST_DirectoryTree "Dizin A�ac�"

// --- preferences
#define MSGTR_PREFERENCES_Audio "Ses"
#define MSGTR_PREFERENCES_Video "Video"
#define MSGTR_PREFERENCES_SubtitleOSD "Altyaz� & OSD"
#define MSGTR_PREFERENCES_Misc "�e�itli"

#define MSGTR_PREFERENCES_None "Yok"
#define MSGTR_PREFERENCES_AvailableDrivers "Kullan�labilir s�r�c�ler:"
#define MSGTR_PREFERENCES_DoNotPlaySound "Sesleri �alma"
#define MSGTR_PREFERENCES_NormalizeSound "Sesi normalle"
#define MSGTR_PREFERENCES_EnEqualizer "Equalizer� A�"
#define MSGTR_PREFERENCES_ExtraStereo "Extra stereoyu a�"
#define MSGTR_PREFERENCES_Coefficient "Katsay�:"
#define MSGTR_PREFERENCES_AudioDelay "Ses Gecikmesi"
#define MSGTR_PREFERENCES_DoubleBuffer "�ifte bufferingi a�"
#define MSGTR_PREFERENCES_DirectRender "Direkt i�lemeyi a�"
#define MSGTR_PREFERENCES_FrameDrop "frame b�rakmas�n� a�"
#define MSGTR_PREFERENCES_HFrameDrop "HARD frame b�rakmas�n� a� (tehlikeli)"
#define MSGTR_PREFERENCES_Flip "Resmi �staraftan a�a�� yolla"
#define MSGTR_PREFERENCES_Panscan "Panscan: "
#define MSGTR_PREFERENCES_OSDTimer "Zamanlay�c�lar ve G�stergeler"
#define MSGTR_PREFERENCES_OSDProgress "Sadece Progressbarlar"
#define MSGTR_PREFERENCES_Subtitle "Altyaz�:"
#define MSGTR_PREFERENCES_SUB_Delay "Gecikme: "
#define MSGTR_PREFERENCES_SUB_FPS "FPS:"
#define MSGTR_PREFERENCES_SUB_POS "Posizyon: "
#define MSGTR_PREFERENCES_SUB_AutoLoad "Altyaz� otomatik y�klemesini kapat"
#define MSGTR_PREFERENCES_SUB_Unicode "Unicode altyaz�"
#define MSGTR_PREFERENCES_SUB_MPSUB "Mevcut altyaz�y� MPlayer'�n altyaz� bi�imine �evir"
#define MSGTR_PREFERENCES_SUB_SRT "Mevcut altyaz�y� zaman tabanl� SubViewer (SRT) bi�imine �evir"
#define MSGTR_PREFERENCES_Font "Yaz�tipi:"
#define MSGTR_PREFERENCES_FontFactor "Yaz�tipi Fakt�r�:"
#define MSGTR_PREFERENCES_PostProcess "postprocessingi a�"
#define MSGTR_PREFERENCES_AutoQuality "Otomatik Kalite: "
#define MSGTR_PREFERENCES_NI "Bo�luksuz AVIyi kullan"
#define MSGTR_PREFERENCES_IDX "Gerekli ise index-tablosunu yeniden olu�tur"
#define MSGTR_PREFERENCES_VideoCodecFamily "Video codec ailesi:"
#define MSGTR_PREFERENCES_AudioCodecFamily "Ses codec ailesi:"
#define MSGTR_PREFERENCES_FRAME_OSD_Level "OSD seviyesi"
#define MSGTR_PREFERENCES_FRAME_Subtitle "Altyaz�"
#define MSGTR_PREFERENCES_FRAME_Font "Yaz�tipi"
#define MSGTR_PREFERENCES_FRAME_PostProcess "Postprocessing"
#define MSGTR_PREFERENCES_FRAME_CodecDemuxer "Codec & ayr��t�r�c�"
#define MSGTR_PREFERENCES_FRAME_Cache "Tampon"
#define MSGTR_PREFERENCES_FRAME_Misc "Di�er"
#define MSGTR_PREFERENCES_Message "Yapt���n�z de�i�ikliklerin �al��abilmesi i�in l�tfen MPlayer� yeniden ba�lat�n!"
#define MSGTR_PREFERENCES_DXR3_VENC "Video �eviricisi:"
#define MSGTR_PREFERENCES_DXR3_LAVC "LAVC kullan(FFmpeg)"
#define MSGTR_PREFERENCES_DXR3_FAME "FAME kullan"
#define MSGTR_PREFERENCES_FontEncoding1 "Unicode"
#define MSGTR_PREFERENCES_FontEncoding2 "Bat� Avrupa Dilleri (ISO-8859-1)"
#define MSGTR_PREFERENCES_FontEncoding3 "Euro ile  Bat� Avrupa  dilleri(ISO-8859-15)"
#define MSGTR_PREFERENCES_FontEncoding4 "Slavca/Orta avrupa dilleri (ISO-8859-2)"
#define MSGTR_PREFERENCES_FontEncoding5 "Esperanto, Galician, Maltese, T�rk�e (ISO-8859-3)"
#define MSGTR_PREFERENCES_FontEncoding6 "Eski Baltik karakterseti (ISO-8859-4)"
#define MSGTR_PREFERENCES_FontEncoding7 "Cyrillic (ISO-8859-5)"
#define MSGTR_PREFERENCES_FontEncoding8 "Arap�a (ISO-8859-6)"
#define MSGTR_PREFERENCES_FontEncoding9 "Modern Yunanca (ISO-8859-7)"
#define MSGTR_PREFERENCES_FontEncoding10 "T�rk�e (ISO-8859-9)"
#define MSGTR_PREFERENCES_FontEncoding11 "Balt�k (ISO-8859-13)"
#define MSGTR_PREFERENCES_FontEncoding12 "Celtik (ISO-8859-14)"
#define MSGTR_PREFERENCES_FontEncoding13 "Hebrew karaktersetleri (ISO-8859-8)"
#define MSGTR_PREFERENCES_FontEncoding14 "Rus�a (KOI8-R)"
#define MSGTR_PREFERENCES_FontEncoding15 "Ukraynaca, Belarus�a (KOI8-U/RU)"
#define MSGTR_PREFERENCES_FontEncoding16 "Sade �ince karakterseti(CP936)"
#define MSGTR_PREFERENCES_FontEncoding17 "Geleneksel �ince karakterseti (BIG5)"
#define MSGTR_PREFERENCES_FontEncoding18 "Japonca karaktersetleri (SHIFT-JIS)"
#define MSGTR_PREFERENCES_FontEncoding19 "Korece karakter seti (CP949)"
#define MSGTR_PREFERENCES_FontEncoding20 "Thaice karakter seti (CP874)"
#define MSGTR_PREFERENCES_FontEncoding21 "Cyrillic Windows (CP1251)"
#define MSGTR_PREFERENCES_FontEncoding22 "Slavca/Orta avrupa Windows (CP1250)"
#define MSGTR_PREFERENCES_FontNoAutoScale "Otomatik Dereceleme Yapma"
#define MSGTR_PREFERENCES_FontPropWidth "Geni�li�i orant�la"
#define MSGTR_PREFERENCES_FontPropHeight "Y�ksekligi orant�la"
#define MSGTR_PREFERENCES_FontPropDiagonal "K��egeni orant�la"
#define MSGTR_PREFERENCES_FontEncoding "�evirme:"
#define MSGTR_PREFERENCES_FontBlur "Blur:"
#define MSGTR_PREFERENCES_FontOutLine "Alt��izili:"
#define MSGTR_PREFERENCES_FontTextScale "Yaz� derecesi:"
#define MSGTR_PREFERENCES_FontOSDScale "OSD derecesi:"
#define MSGTR_PREFERENCES_Cache "Tampon a��k/kapal�"
#define MSGTR_PREFERENCES_LoadFullscreen "Tam Ekran olarak ba�lat"
#define MSGTR_PREFERENCES_CacheSize "Tampon boyutu: "
#define MSGTR_PREFERENCES_XSCREENSAVER "XekranKoruyucusunu Durdur"
#define MSGTR_PREFERENCES_AutoSync "AutoSync a��k/kapal�"
#define MSGTR_PREFERENCES_AutoSyncValue "Autosync: "

// --- messagebox
#define MSGTR_MSGBOX_LABEL_FatalError "�l�mc�l hata!"
#define MSGTR_MSGBOX_LABEL_Error "Hata!"
#define MSGTR_MSGBOX_LABEL_Warning "Dikkat!"

#endif





