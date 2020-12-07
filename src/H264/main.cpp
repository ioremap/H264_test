#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "x264.h"
#include "x264_config.h"

#include <pthread.h>

#define PRINT_NONE        "\033[0m"
#define PRINT_RED         "\033[0;31m"
#define PRINT_GREEN       "\033[0;32m"

int main()
{
	FILE* fp_yuv = fopen("./resource/shinian.yuv", "rb");
	if(!fp_yuv)
	{
		printf(PRINT_RED "open resource/shinian.yuv faied!\n" PRINT_NONE);
		return -1;
	}

	FILE* fp_264 = fopen("./resource/shinian.h264", "wb");
	if (!fp_264)
	{
		printf(PRINT_RED "create resource/shinian.h264 failed!\n" PRINT_NONE);
	}

	x264_picture_t* ppic_in = (x264_picture_t*)malloc(sizeof(x264_picture_t));
	if(!ppic_in)
	{
		printf(PRINT_RED" malloc failed!\n" PRINT_NONE);
		return -1;
	}

	x264_picture_t* ppic_out = (x264_picture_t*)malloc(sizeof(x264_picture_t));
	if(!ppic_out)
	{
		printf(PRINT_RED "malloc failed!\n" PRINT_NONE);
		return -1;
	}

	int csp = X264_CSP_I420;
	int frame_num = 0;

	x264_param_t enc_param;
	x264_param_default(&enc_param);
	enc_param.i_width = 720;
	enc_param.i_height = 480;
	enc_param.i_csp = csp;

	x264_param_apply_profile(&enc_param, x264_profile_names[0]);

	x264_t* phandle = x264_encoder_open(&enc_param);
	if(!phandle)
	{
		printf(PRINT_RED "x264_encoder_open error!\n" PRINT_NONE);

		free(ppic_in);
		free(ppic_out);
		fclose(fp_yuv);
		fclose(fp_264);

		return -1;
	}
	else
	{
		printf(PRINT_GREEN "x264_encoder_open success!\n" PRINT_NONE);
	}

	x264_picture_init(ppic_out);
	x264_picture_alloc(ppic_in, csp, enc_param.i_width, enc_param.i_height);

	int size = enc_param.i_width * enc_param.i_height;

	if(0 == frame_num)
	{
		fseek(fp_yuv, 0, SEEK_END);
		switch(csp)
		{
			case X264_CSP_I420:
			{
				frame_num = ftell(fp_yuv) / (size*3/2);
			}
				break;
			case X264_CSP_I444:
			{
				frame_num = ftell(fp_yuv) / (size*3);
			}
				break;
			default:
				break;
		}

		fseek(fp_yuv, 0, SEEK_SET);

		printf(PRINT_GREEN "pic width:%d height:%d  frame_num:%d\n" PRINT_NONE, enc_param.i_width, enc_param.i_height, frame_num);
	}

	x264_nal_t* pnal = NULL;
	int nal_count = 0;
	
	for(int i = 0; i < frame_num; i++)
	{
		switch(csp)
		{
			case X264_CSP_I420:
			{
				fread(ppic_in->img.plane[0], size, 1, fp_yuv);
				fread(ppic_in->img.plane[1], size/4, 1, fp_yuv);
				fread(ppic_in->img.plane[2], size/4, 1, fp_yuv);
			}
				break;
			case X264_CSP_I444:
			{
				fread(ppic_in->img.plane[0], size, 1, fp_yuv);
				fread(ppic_in->img.plane[1], size, 1, fp_yuv);
				fread(ppic_in->img.plane[2], size, 1, fp_yuv);
			}
				break;
			default:
				break;
		}

		ppic_in->i_pts = i;

		int ret = x264_encoder_encode(phandle, &pnal, &nal_count, ppic_in, ppic_out);
		if(ret < 0)
		{
			printf(PRINT_RED "x264_encoder_encode error\n" PRINT_NONE);
			continue;
		}
		else
		{
			printf(PRINT_GREEN "x264_encoder_encode success, nal count:%d\n" PRINT_NONE, nal_count);
		}

		for(int j = 0; j < nal_count; j++)
		{
			fwrite(pnal[j].p_payload, 1, pnal[j].i_payload, fp_264);
		}

	}


	while(1)
	{
		int ret = x264_encoder_encode(phandle, &pnal, &nal_count, NULL, ppic_out);
		if(0 == ret)
			break;

		printf(PRINT_GREEN "flush nal count:%d\n" PRINT_NONE, nal_count);

		for(int j = 0; j < nal_count; j++)
		{
			fwrite(pnal[j].p_payload, 1, pnal[j].i_payload, fp_264);
		}
	}


	x264_picture_clean(ppic_in);

	x264_encoder_close(phandle);

	free(ppic_in);
	free(ppic_out);

	fclose(fp_yuv);
	fclose(fp_264);

	return 0;
}