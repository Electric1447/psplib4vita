/* psplib/image.h
   Image manipulation/saving/loading

   Copyright (C) 2007-2008 Akop Karapetyan

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

   Author contact information: pspdev@akop.org
*/

#ifndef _PSP_IMAGE_H
#define _PSP_IMAGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <psp2/gxm.h>
#include <psp2/io/fcntl.h>
#include <vita2d.h>

#define PSP_IMAGE_INDEXED 8
#define PSP_IMAGE_16BPP   16

#define GU_PSM_T8 SCE_GXM_TEXTURE_FORMAT_P8_1BGR
#define GU_PSM_5551 SCE_GXM_TEXTURE_FORMAT_U1U5U5U5_ABGR
#define GU_PSM_4444 SCE_GXM_TEXTURE_FORMAT_U4U4U4U4_ABGR

typedef struct
{
  int X;
  int Y;
  int Width;
  int Height;
} PspViewport;

typedef struct
{
  int Width;
  int Height;
  void *Pixels;
	vita2d_texture *Texture;
  PspViewport Viewport;
  char FreeBuffer;
  char BytesPerPixel;
  char Depth;
  char PowerOfTwo;
  unsigned int TextureFormat;
  /* TODO: don't allocate if not necessary */
  void *Palette;
  unsigned short PalSize;
} PspImage;

/* Create/destroy */
PspImage* pspImageCreate(int width, int height, int bits_per_pixel);
PspImage* pspImageCreateVram(int width, int height, int bits_per_pixel);
PspImage* pspImageCreateOptimized(int width, int height, int bpp);
void      pspImageDestroy(PspImage *image);

PspImage* pspImageRotate(const PspImage *orig, int angle_cw);
PspImage* pspImageCreateThumbnail(const PspImage *image);
PspImage* pspImageCreateCopy(const PspImage *image);
void      pspImageClear(PspImage *image, unsigned int color);

PspImage* pspImageLoadPng(const char *path);
PspImage* pspImageLoadPng2D(const char *path);

int       pspImageSavePng(const char *path, const PspImage* image);
PspImage* pspImageLoadPngSCE(SceUID fp);
PspImage* pspImageLoadPngFd(FILE *fp);
int       pspImageSavePngFd(FILE *fp, const PspImage* image);

int pspImageBlur(const PspImage *original, PspImage *blurred);
int pspImageDiscardColors(const PspImage *original);

#ifdef __cplusplus
}
#endif

#endif  // _PSP_IMAGE_H
