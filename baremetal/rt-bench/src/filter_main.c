#include <sim.h>
#include <type.h>
#include <riscv.h>
#include "putnum.h"
#include "image-filters/include/common_filters.h"
#include "image-filters/include/filters.h"

static void *params[4] = {0, 0, 0, 0};

void filter_main()
{

    sim_puts("Running RT-BENCH: \n");
    sim_puts("   RT-BENCH init: \n");

    struct bmp_t source = readBMP(params[0]);
    struct bmp_t target;
    copyBMP(&source, &target);

    u32 start_t = sim_time();
    u32 start_c = sim_time();

#ifdef BENCH_THRESHOLD
    threshold(&source);
#endif
#ifdef BENCH_GRAYSCALE
    grayscale(&source, &target);
#endif
#ifdef BENCH_SEPIA
    sepia(&source, &target);
#endif
#ifdef BENCH_SOBEL
    int kh[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    int kv[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    sobel(&source, &target, 3, kh, kv);
#endif
#ifdef BENCH_GAUSSIAN_NOISE
    float conv[3][3] = {{0.05854983f, 0.09653235f, 0.05854983f}, {0.09653235f, 0.15915494f, 0.09653235f}, {0.05854983f, 0.09653235f, 0.05854983f}};
    gaussian_noise(&source, &target, 3, conv);
#endif

    u32 end_c = sim_time();
    u32 end_t = sim_time();

    sim_puts("Bench:");
    for (u32 h = 0; h < source.height; h++)
    {
        sim_puthex(source.data[h][source.width]);
        sim_puthex(target.data[h][source.width]);
    }
    sim_puts("\n");
    sim_puts("Cycles: 0x");
    sim_puthex(end_c - start_c);
    sim_puts(" = ");
    sim_put_num(end_c - start_c);
    sim_puts("\n");
    sim_puts("Time: 0x");
    sim_puthex(end_t - start_t);
    sim_puts(" = ");
    sim_put_num(end_t - start_t);
    sim_puts("\n");

    // Wait for output to stabalize before finishing
    while (csr_read(mcycle) - end_c < 1000)
        ;
}