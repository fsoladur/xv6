#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int sys_fork(void)
{
  return fork();
}

int sys_exit(void)
{
  int status;
  if(argint(0,&status) < 0)
    return -1;
  exit(status<< 8);
  return 0; // not reached
}

int sys_wait(void)
{
  int * status;
  if((argptr(0,(void**)&status,sizeof(int*))) < 0)
      return -1;
  return wait(status);
}

int sys_kill(void)
{
  int pid;

  if (argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int sys_getpid(void)
{
  return myproc()->pid;
}

int sys_sbrk(void)
{
  int sz;
  int n;

  if (argint(0, &n) < 0)
    return -1;
  sz = myproc()->sz;
  //ejercicio 1 boletin 3 reserva diferida
  if (n < 0) {
    if (deallocuvm(myproc()->pgdir, myproc()->sz, myproc()->sz+n) == 0)
      return -1;
    lcr3(V2P(myproc()->pgdir));  // Invalidate TLB.
    // Hacemos exactamente lo mismo que en growproc pero a este nivel sin necesidad de llamar al procedimiento
    // Cuando salte el trap se encargará de gestionar el caso de que el argumento que se le pase sea negativo
  }
  myproc()->sz += n;
  return sz;
}

int sys_sleep(void)
{
  int n;
  uint ticks0;

  if (argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while (ticks - ticks0 < n)
  {
    if (myproc()->killed)
    {
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int sys_date(void)
{
  struct rtcdate *d;
  if (argptr(0, (void **)&d, sizeof(struct rtcdate)) == -1)
    return -1;
  cmostime(d);
  return 0;
}

int sys_getprio(void)
{
  int pid;
  if (argint(0, &pid) < 0)
    return -1;
  return getprio(pid);
}

int sys_setprio(void)
{
  int pid;
  unsigned int new_priority;
  if (argint(0, &pid) < 0 || argint(1, (int *)&new_priority) < 0)
    return -1;
  return setprio(pid, new_priority);
}