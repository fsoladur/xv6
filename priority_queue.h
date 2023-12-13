#ifndef __PRIORITY_QUEUE
#define __PRIORITY_QUEUE
#define N_PRIORITIES 10
#include "types.h"
#include "proc.h"

typedef struct
{
    struct proc *first;
    struct proc *last;
} proc_priority;

int insert(struct proc *newproc, proc_priority *priority_queue)
{
    uint priority = newproc->priority;
    if (priority < 0 || priority > 9)
    {
        newproc->killed = 1;
        return -1;
    }
    newproc->next = NULL;
    if (priority_queue[priority].first == NULL)
    {
        priority_queue[priority].first = newproc;
        priority_queue[priority].last = newproc;
    }
    else
    {
        priority_queue[priority].last->next = newproc;
        priority_queue[priority].last = newproc;
    }
    return 0;
}

struct proc *extract(proc_priority *priority_queue)
{
    struct proc *extracted;
    for (int i = 0; i < N_PRIORITIES; i++)
    {
        if (priority_queue[i].first != NULL)
        {
            extracted = priority_queue[i].first;
            if (priority_queue[i].first != priority_queue[i].last)
            {
                priority_queue[i].first = extracted->next;
            }
            else
            {

                priority_queue[i].first = NULL;
                priority_queue[i].last = NULL;
            }
            extracted->next = NULL;
            return extracted;
        }
    }

    return NULL;
}
#endif