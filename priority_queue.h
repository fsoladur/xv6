#ifndef __PRIORITY_QUEUE
#define __PRIORITY_QUEUE
#define N_queue 10
#include "param.h"
#include "types.h"
#include "proc.h"
#include "spinlock.h"

typedef struct {
    struct proc* first;
    struct proc* last;
} proc_priority;

int insert(struct proc *newproc, proc_priority* priority_queue[]);
struct proc *extract(proc_priority* priority_queue[]);
struct proc* search_and_remove(int pid,proc_priority* priority_queue[]);
#endif