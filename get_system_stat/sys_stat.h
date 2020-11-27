#ifndef GET_SYS_STAT
#define GET_SYS_STAT

#include <stdint.h>     /* C99 types */
#include <stdbool.h>    /* bool type */
#include <stdio.h>
#include <stdlib.h>

struct cpu_stat_s {
    char cpu_name[32];
    uint64_t user;
    uint64_t nice;
    uint64_t system;
    uint64_t idle;
    uint64_t iowait;
    uint64_t irq;
    uint64_t softirq;
    uint64_t steal;
};

int get_cpu_stat(struct cpu_stat_s* cpu_stat);

int get_cpu_ratio(float* cpu_ratio);

int get_mem_ratio(float* mem_ratio);

#endif
