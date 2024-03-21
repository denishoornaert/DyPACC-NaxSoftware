/**
 * @file common.c
 * @ingroup image-filters
 * @brief Collection of manipulations on BMP (read, copy, and write).
 * @author Denis Hoornaert <denis.hoornaert@tum.de>
 *
 * This allows the benchmark to be run periodically, by re-running only the
 * execution portion.
 *
 * @copyright (C) 2022 Denis Hoornaert <denis.hoornaert@tum.de>
 * SPDX-License-Identifier: MIT
 *
 */

#include "../image-filters/include/common_filters.h"

#define MAX_HEIGHT 132

extern u8 bmp_img1; // first byte of bmp_img1
extern u8 bmp_img2; // first byte of bmp_img2

struct bmp_t readBMP(const char *file)
{
    char *bmp = &bmp_img1;
    int cur = 0;

    struct bmp_t img;
    img.header = bmp;

    img.file_size = img.header[2] | (img.header[3] << 8) | (img.header[4] << 8) | (img.header[5] << 8);
    img.data_offset = img.header[10] | (img.header[11] << 8) | (img.header[12] << 8) | (img.header[13] << 8);
    img.width = img.header[18] | (img.header[19] << 8) | (img.header[20] << 8) | (img.header[21] << 8);
    img.height = img.header[22] | (img.header[23] << 8) | (img.header[24] << 8) | (img.header[25] << 8);
    img.depth = (img.header[28] | (img.header[29] << 8) | (img.header[30] << 8) | (img.header[31] << 8)) >> 3;

    cur = img.data_offset;

    // print img size
    sim_puts("BMP1: w=");
    sim_puthex(img.width);
    sim_puts(" h=");
    sim_puthex(img.height);
    sim_puts("\n");

    u32 read_width = 3 * img.width + img.width % 4;
    img.data = img.data_buffer_refs;
    for (u32 h = 0; h < img.height; h++)
    {
        // sim_puthex(h);
        // sim_puts(" of ");
        // sim_puthex(img.height);
        // sim_puts("\n");
        img.data_buffer_refs[h] = &bmp[cur + h * read_width];
    }

    // print img pixel
    sim_puts("BMP1: r");
    sim_puthex(img.data[32][3 * 32 + 2]);
    sim_puts(" g");
    sim_puthex(img.data[32][3 * 32 + 1]);
    sim_puts(" b");
    sim_puthex(img.data[32][3 * 32 + 0]);
    sim_puts("\n");

    return img;
}

void copyBMP(struct bmp_t *ignored, struct bmp_t *img)
{
    char *bmp = &bmp_img2;
    int cur = 0;

    img->header = bmp;

    img->file_size = img->header[2] | (img->header[3] << 8) | (img->header[4] << 8) | (img->header[5] << 8);
    img->data_offset = img->header[10] | (img->header[11] << 8) | (img->header[12] << 8) | (img->header[13] << 8);
    img->width = img->header[18] | (img->header[19] << 8) | (img->header[20] << 8) | (img->header[21] << 8);
    img->height = img->header[22] | (img->header[23] << 8) | (img->header[24] << 8) | (img->header[25] << 8);
    img->depth = (img->header[28] | (img->header[29] << 8) | (img->header[30] << 8) | (img->header[31] << 8)) >> 3;

    cur = img->data_offset;

    // print img size
    sim_puts("BMP2: w=");
    sim_puthex(img->width);
    sim_puts(" h=");
    sim_puthex(img->height);
    sim_puts("\n");

    u32 read_width = 3 * img->width + img->width % 4;
    img->data = img->data_buffer_refs;
    for (u32 h = 0; h < img->height; h++)
    {
        img->data_buffer_refs[h] = &bmp[cur + h * read_width];
    }

    // print img pixel
    sim_puts("BMP2: r");
    sim_puthex(img->data[32][3 * 32 + 2]);
    sim_puts(" g");
    sim_puthex(img->data[32][3 * 32 + 1]);
    sim_puts(" b");
    sim_puthex(img->data[32][3 * 32 + 0]);
    sim_puts("\n");
}

void writeBMP(const char *file, struct bmp_t img)
{
    // Ignored
}

void freeBMP(struct bmp_t *img)
{
    // Ignored
}