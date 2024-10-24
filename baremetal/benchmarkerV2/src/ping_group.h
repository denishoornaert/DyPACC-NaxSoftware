#ifndef PING_GROUP_H
#define PING_GROUP_H

#include "common.h"

#if BENCH == BENCH_C2C_CAS && USE_PING_GROUP == TRUE

void endless_ping(u32 hart_id);

#endif
#endif