#include "priority_queue.h"

int insert(struct proc *newproc, proc_priority *priority_queue[])
{
    uint priority = newproc->priority;
    if (priority < 0 || priority > 9)
    {
        newproc->killed = 1;
        return -1;
    }
    if (priority_queue[priority]->first == NULL)
    {
        priority_queue[priority]->first = newproc;
        priority_queue[priority]->last = newproc;
    }
    else
    {
        struct proc *old_last_proc = priority_queue[priority]->last;
        old_last_proc->next = newproc;
        priority_queue[priority]->last = newproc;
    }
    return 0;
}

struct proc *extract(proc_priority *priority_queue[])
{
    struct proc *extracted;
    for (int i = 0; i < N_queue; i++)
    {
        if (priority_queue[i] != NULL)
        {
            if (priority_queue[i]->first != NULL)
            {
                extracted = priority_queue[i]->first;
                priority_queue[i]->first = extracted->next;
                return extracted;
            }
        }
    }

    return -1;
}

struct proc *search_and_remove(int pid, proc_priority *priority_queue[])
{
    struct proc *objective, *proc;

    for (int i = 0; i < N_queue; i++)
    {
        if (priority_queue[i] != NULL)
        {
            proc = priority_queue[i]->first;
            while (proc->next != NULL && proc->next->pid != pid)
            {
                proc = proc->next;
            }
            if (proc->next == NULL)
            {
                return NULL;
            }
            else
            {
                objective = proc->next;
                proc->next = objective->next;
                return objective;
            }
        }
    }
}
