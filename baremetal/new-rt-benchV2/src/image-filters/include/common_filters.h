/**
 * @file common.h
 * @ingroup image-filters
 * @brief All BMP-related manipulation functions and struct.
 * @author Denis Hoornaert <denis.hoornaert@tum.de>
 *
 * @copyright (C) 2022 Denis Hoornaert <denis.hoornaert@tum.de>
 * SPDX-License-Identifier: MIT
 */

// #include <stdio.h>
// #include <math.h>
// #include <stdlib.h>
// #include <stdint.h>
#include <type.h>
#include "../../common.h"

#ifndef COMMON_FILTERS_H
#define COMMON_FILTERS_H

/** @brief Struct representing the useful data to represent a BMP image in memory.
 * @details
 * Is used to store relevant data (e.g., height, width) and other raw type of data
 * to be used down the line by the filters and BMP manipulations.
 */
struct bmp_t
{
	u32 file_size;	 ///< The size of the BMP file read in bytes
	u32 data_offset; ///< The offset in bytes of where the data start in the file @todo: useful?
	u32 width;		 ///< The width in pixels of the image
	u32 height;		 ///, The height in pixels of the image
	u16 depth;		 ///< The size in bytes of each pixel
	u8 *header;		 ///< Raw BMP header (fixed in format definition)
	u8 *header_ext;	 ///< RAW BMP header extension (dynamic, input dependent)
	u8 **data;		 ///< Payload storing the image's pixels
#define MAX_HEIGHT 150
	u8 *data_buffer_refs[MAX_HEIGHT];
	u32 magic;
};

void readBMP(struct bmp_t *img);

/** @brief Function copying the content of one `bmp_t` struct in another.
 * @param[in] img The source image to copy from.
 * @param[out] out The destination struct to copy to.
 */
void copyBMP(struct bmp_t *img, struct bmp_t *out);

/** @brief Function writing the content of a `bmp_t` struct into a BMP image file.
 * @param[in] file The file name (path included) to the BMP image to write.
 * @param[in] img The source image content to write in the file.
 */
void writeBMP(const char *file, struct bmp_t img);

/** @brief Function freeing the dynamically allocated memory used by the `bmp_t` struct.
 * @param[in] img The `bmp_t` struct to free memory from.
 */
void freeBMP(struct bmp_t *img);

#endif /* COMMON_FILTERS_H */
