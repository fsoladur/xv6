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

struct proc *search(struct proc *newproc, proc_priority *priority_queue)
{
    struct proc *proc = priority_queue[newproc->priority].first;

    while (proc != NULL && proc != newproc)
    {
        proc = proc->next;
    }

    if (proc == NULL)
    {
        return NULL;
    }
    else
    {
        return proc;
    }
}

int insert(struct proc *newproc, proc_priority *priority_queue)
{
    uint priority = newproc->priority;
    if (priority < 0 || priority > 9)
    {
        newproc->killed = 1;
        return -1;
    }
    if (search(newproc, priority_queue) == NULL)
    {
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

struct proc *search_extract(int pid, proc_priority *priority_queue)
{
    struct proc *current, *prev;
    for (int i = 0; i < N_PRIORITIES; i++)
    {
        prev = NULL;
        current = priority_queue[i].first;
        while (current != NULL)
        {
            if (current->pid == pid)
            {
                // Encontramos el proceso con el PID especificado
                if (prev != NULL)
                {
                    // El proceso no está al principio de la cola
                    prev->next = current->next;
                    if (current == priority_queue[i].last)
                    {
                        priority_queue[i].last = prev;
                    }
                }
                else
                {
                    // El proceso está al principio de la cola
                    priority_queue[i].first = current->next;
                    if (current == priority_queue[i].last)
                    {
                        priority_queue[i].last = NULL;
                    }
                }
                current->next = NULL;
                return current; // Devolvemos el proceso encontrado y eliminado
            }

            prev = current;
            current = current->next;
        }
    }
    return NULL;
}
#endif