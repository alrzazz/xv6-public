#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
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
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// check and pass arguments to kernel mode
// return status of passing arguments to kernel mode
int
sys_ps(void)
{
  struct proc_info **p;
  int *n;
  if(argptr(0, (void*)&p, sizeof(*p))<0 || argptr(1, (void*)&n, sizeof(*n))<0)
    return -1;
  ps(p,n);
  return 0;
}

int
sys_waitx(void)
{
  int *wtime;
  int *rtime;
  if(argptr(1, (void*)&rtime, sizeof(*rtime))<0 || argptr(0, (void*)&wtime, sizeof(*wtime))<0)
    return -1;
  return waitx(wtime,rtime);
}

int
sys_set_priority(void)
{
  int prio;
  if(argint(0, &prio) < 0)
    return -1;
  return set_priority(prio);
}
