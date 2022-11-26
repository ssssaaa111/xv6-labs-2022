#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(void)
{
    int pid;
    int p1[2];
    int index[35];
    int size = 35;
    // init
    for (int i = 0; i < size; i++)
    {
        index[i] = i + 2;
    }

    while (size > 0)
    {
        /* code */
        pipe(p1);
        pid = fork();
        if (pid < 0)
        {
            printf("init: fork failed\n");
            exit(1);
        }
        if (pid == 0)
        {
            close(p1[1]);
            int temp = 0;
            int prime = 0;
            size = 0;
            while (read(p1[0], &temp, sizeof(temp)) != 0)
            {
                // printf("prime1 %d, temp %d, size %d\n", prime, temp, size);


                // the first number must be prime
                if (prime == 0)
                {
                    prime = temp;
                }
                else
                {
                    if (temp % prime != 0)
                    {
                        index[size] = temp;
                        size++;
                    }
                }
            }
            printf("prime %d\n", prime);
            close(p1[0]);
        }
        // must add  this else, or it will excute two times.......
        else
        {
            close(p1[0]);
            for (int i = 0; i < size; i++)
            {
                write(p1[1], &index[i], sizeof(index[i]));
            }

            close(p1[1]);
            wait((int *)0);
            exit(0);
        }

    }

    exit(0);
}