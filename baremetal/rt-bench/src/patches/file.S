

.global bmp_img1
bmp_img1:
#if defined(BENCH_THRESHOLD) || defined(BENCH_GRAYSCALE) || defined(BENCH_SEPIA) || defined(BENCH_SOBEL) || defined(BENCH_GAUSSIAN_NOISE)
.incbin "src/image-filters/inputs/qcif.bmp"
#endif

.global bmp_img1_end
bmp_img1_end:
.byte 0
.global bmp_img2
bmp_img2:
#if defined(BENCH_THRESHOLD) || defined(BENCH_GRAYSCALE) || defined(BENCH_SEPIA) || defined(BENCH_SOBEL) || defined(BENCH_GAUSSIAN_NOISE)
.incbin "src/image-filters/inputs/qcif.bmp"
#endif

.global bmp_img2_end
bmp_img2_end:
.byte 0
