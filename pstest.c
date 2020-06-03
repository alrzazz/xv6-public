#include "types.h"
#include "stat.h"
#include "user.h"

struct proc_info
{
    int pid;
    int memsize;
};

void swap(struct proc_info *p1, struct proc_info *p2)
{
    struct proc_info temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

void sort(struct proc_info *p, int process_count)
{
    for (int i = 0; i < process_count; i++)
    {
        for (int j = 0; j < process_count; j++)
        {
            if (p[i].memsize > p[j].memsize)
            {
                swap(&p[i], &p[j]);
            }
        }
    }
}

int main(void)
{
    int rc = fork();
    if (rc < 0)
    {
        // fork failed
        exit();
    }
    else if (rc == 0)
    {
        // child (new process)
        int *var1 = malloc(sizeof(int) * 3000000);
        for (int i = 0; i < 10000000000; i++)
        {
            for (int j = 0; j < i; j++){}
            *var1 += 1;
        }
    }
    else
    {
        // parent goes down this path (original process)
        int wc = fork();
        if (wc == 0)
        {
            int *var2 = malloc(sizeof(int) * 5000000);
            for (int i = 0; i < 50000000000; i++)
            {
                for (int j = 0; j < i; j++){}
                *var2 += 2;
            }
        }
        else if (wc > 0)
        {
            int process_count = 0;
            struct proc_info *p = malloc(25 * sizeof(struct proc_info));
            ps(&p, &process_count);
            ps(&p, &process_count);
            printf(1, "%d process found.\n", process_count);
            sort(p, process_count);
            printf(1, "#   PID   MEMSIZE\n");
            for (int i = 0; i < process_count; i++)
            {
                printf(1, "%d   %d     %d\n", i+1, p[i].pid, p[i].memsize);
            }
            printf(1, "hint: Sorted in ascending order according to the memory usage of each process.\n");
        }
    }
    exit();
    return 0;
}