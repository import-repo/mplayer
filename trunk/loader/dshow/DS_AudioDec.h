/********************************************************

	DirectShow Audio decoder implementation
	Copyright 2000 Eugene Kuznetsov  (divx@euro.ru)
        Converted  C++ --> C  :) by A'rpi/ESP-team

*********************************************************/

#ifdef __cplusplus
extern "C" {
#endif /* defined(__cplusplus) */

void* DS_AudioDecoder_Open(char* dllname, GUID* guid, WAVEFORMATEX* wf);

void DS_AudioDecoder_Close(void* _handle);

int DS_AudioDecoder_GetSrcSize(void* _handle, int dest_size);

int DS_AudioDecoder_Convert(void* _handle,
	    unsigned char* in_data, unsigned in_size,
	    unsigned char* out_data, unsigned out_size,
	    unsigned* size_read, unsigned* size_written);

#ifdef __cplusplus
} /* extern "C" */
#endif /* defined(__cplusplus) */
