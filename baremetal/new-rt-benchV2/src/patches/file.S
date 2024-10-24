
.global bmp_img1
bmp_img1:
#ifdef INCLUDE_SQCIF
.incbin "src/image-filters/inputs/sqcif.bmp"
#endif
#ifdef INCLUDE_CIF
.incbin "src/image-filters/inputs/cif.bmp"
#endif
#ifdef INCLUDE_VGA
.incbin "src/image-filters/inputs/vga.bmp"
#endif
#ifdef INCLUDE_FULLHD
.incbin "src/image-filters/inputs/fullhd.bmp"
#endif
#ifdef INCLUDE_4K
.incbin "src/image-filters/inputs/4k.bmp"
#endif


.global bmp_img1_end
bmp_img1_end:
.byte 0
.global bmp_img2
bmp_img2:
#ifdef INCLUDE_SQCIF
.incbin "src/image-filters/inputs/sqcif.bmp"
#endif
#ifdef INCLUDE_CIF
.incbin "src/image-filters/inputs/cif.bmp"
#endif
#ifdef INCLUDE_VGA
.incbin "src/image-filters/inputs/vga.bmp"
#endif
#ifdef INCLUDE_FULLHD
.incbin "src/image-filters/inputs/fullhd.bmp"
#endif
#ifdef INCLUDE_4K
.incbin "src/image-filters/inputs/4k.bmp"
#endif

.global bmp_img2_end
bmp_img2_end:
.byte 0

