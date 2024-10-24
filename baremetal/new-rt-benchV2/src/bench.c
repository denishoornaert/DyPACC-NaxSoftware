#include "bench.h"

#if BENCH == BENCH_THRESHOLD || BENCH == BENCH_GRAYSCALE || BENCH == BENCH_SEPIA || BENCH == BENCH_SOBEL || BENCH == BENCH_GAUSSIAN_NOISE
#include "image-filters/include/common_filters.h"
#include "image-filters/include/filters.h"

struct bmp_t source;
struct bmp_t target;

#else
extern int benchmark_init(int parameters_num, void **parameters);
extern void benchmark_execution(int parameters_num, void **parameters);
#endif

static void *params[4] = {0, 0, 0, 0};

void bench_main()
{
        /* Wait initial delay */
        put_str("Waiting initial delay of ");
        put_num(INIT_DELAY);
        put_str(" cycles.\n");

        u32 delay_c = get_time();
        while (get_time() - delay_c < INIT_DELAY)
                ;
        put_str("   [done]\n");

        put_str("Setting priorities...\n");
        set_prios(MAIN_PRIO, MAIN_PRIO, MAIN_PRIO);
        put_str("    [done]\nStarting runs...\n");

        put_str("BufferSize=");
        put_num(BUFFER_SIZE);
        put_str("\n");

        put_str("Runs=");
        put_num(N_RUNS);
        put_str("\n");

        /* Run the Benchmarks */
        for (int run_id = 0; run_id < N_RUNS; run_id++)
        {

                put_str("Starting Per-Run Initialization...\n");
#if BENCH == BENCH_THRESHOLD || BENCH == BENCH_GRAYSCALE || BENCH == BENCH_SEPIA || BENCH == BENCH_SOBEL || BENCH == BENCH_GAUSSIAN_NOISE
                readBMP(&source);
                copyBMP(&source, &target);
#else
                benchmark_init(4, (void **)&params);
#endif
                put_str("    [done]\nStarting run...\n");

                u64 start_t = get_time();
#if BENCH == BENCH_THRESHOLD
                threshold(&source);
#elif BENCH == BENCH_GRAYSCALE
                grayscale(&source, &target);
#elif BENCH == BENCH_SEPIA
                sepia(&source, &target);
#elif BENCH == BENCH_SOBEL
                int kh[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
                int kv[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
                sobel(&source, &target, 3, kh, kv);
#elif BENCH == BENCH_GAUSSIAN_NOISE
                float conv[3][3] = {{0.05854983f, 0.09653235f, 0.05854983f}, {0.09653235f, 0.15915494f, 0.09653235f}, {0.05854983f, 0.09653235f, 0.05854983f}};
                gaussian_noise(&source, &target, 3, conv);
#else
                benchmark_execution(4, (void **)&params);
#endif
                u64 end_t = get_time();

                put_str("RunResult{ \"run_id\":");
                put_num(run_id);
                put_str(", \"time\":");
                put_num(end_t - start_t);
                put_str(" }\n");
        }
}