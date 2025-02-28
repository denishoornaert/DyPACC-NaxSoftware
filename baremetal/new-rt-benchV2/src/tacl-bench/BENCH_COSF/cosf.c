/**
 * @file cosf.c
 * @defgroup cosf Cosf
 * @ingroup rt-tacle-bench
 * @brief RT-Bench compatible cosf benchmark from TACle Bench.
 * @details
 * The original script has been broken down in three components:
 * - init: benchmark_init();
 * - execution: benchmark_execution();
 * - teardown: benchmark_teardown();
 *
 * Code is courtesy of TACle Bench project (see https://github.com/tacle/tacle-bench)
 * This header was generated automatically, please consult the code at bench/kernel/cosf/cosf.c for the exact license(s).
 *

  This program is part of the TACLeBench benchmark suite.
  Version V 1.9

  Name: cosf

  @author Dustin Green

  Function: cosf performs calculations of the cosinus function

  Source:

  Original name:

  Changes:

  @copyright this code is FREE with no restrictions

*/

// Libraries used by rt-bench

#include "wcclibm.h"

/*
  Declaration of global variables
*/

float cosf_solutions;

/*
  Initialization function
*/

int benchmark_init(int parameters_num, void **parameters)
{
  cosf_solutions = 0.0f;
  return 0;
}

/*
  Return function
*/

int cosf_return(void)
{
  int temp = cosf_solutions;

  if (temp == -4)
    return 0;
  else
    return -1;
}

/*
  Main functions
*/

void benchmark_execution(int parameters_num, void **parameters)
{
  float i;
  _Pragma("loopbound min 100 max 32768") for (i = 0.0f; i < 32768; i += 0.1f)
      cosf_solutions += basicmath___cosf(i);
}

void benchmark_teardown(int parameters_num, void **parameters)
{
}
