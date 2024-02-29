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

#include "../image-filters/include/common.h"

struct bmp_t readBMP(const char *file)
{
    struct bmp_t img;
    // TODO: Implement
    return img;
}

void copyBMP(struct bmp_t *img, struct bmp_t *out)
{
    // TODO: Implement
}

void writeBMP(const char *file, struct bmp_t img)
{
    // TODO: Implement
}

void freeBMP(struct bmp_t *img)
{
    // TODO: Implement
}