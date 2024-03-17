#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"



uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

uint64 sys_procs(void)
{
    printf("process list\n");

    // Loop over process table looking for process with pid.
    struct proc *p;

     printf("name \t pid \t state \n");
    for (p = proc; p < &proc[NPROC]; p++)
    {
        acquire(&p->lock); // Acquire the lock of the current process

        // Now you can access the fields of the process (p->state, p->pid, etc.)
        // and perform operations on them
        if (p->state == SLEEPING)
            printf("%s \t %d \t SLEEPING \n", p->name, p->pid);
        else if (p->state == RUNNING)
            printf("%s \t %d \t RUNNING \n", p->name, p->pid);
        else if (p->state == RUNNABLE)
            printf("%s \t %d \t RUNNABLE \n", p->name, p->pid);
        else if (p->state == USED)
            printf("%s \t %d \t USED \n", p->name, p->pid); 
        else if (p->state == ZOMBIE)
            printf("%s \t %d \t ZOMBIE \n", p->name, p->pid); 

        release(&p->lock); // Release the lock of the current process
    }

    return 22;
}


uint64 sys_writebigfile(void){ 
char *s="cmd : usertests writebig";
printf("%s\n", s);

 return 23;
}