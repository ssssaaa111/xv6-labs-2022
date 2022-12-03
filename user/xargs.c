#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

#define STDIN_FILENO 0
#define MAXLINE 1024

int main(int argc, char **argv)
{
    char line[MAXLINE];
    char *params[MAXARG];
    int n = 0;
    int args_index = 0;
    int i;
    char *cmd = argv[1];
    for (int i = 0; i < argc-1; i++)
    {
        printf("arg %d is:%s \n", args_index, argv[i+1]);
        params[args_index++] = argv[i + 1];
    }
    // printf("size of char * is %d\n", sizeof(line));
    // printf("size of char * is %d", (int)'\0');
    int pid = fork();
    
    
    if (pid == 0)
    {   

        while ((n = read(STDIN_FILENO, line, MAXLINE)) > 0)
        {

            printf("line is:%s \n", line);
            printf("n is:%d \n", n);
            // params[args_index++] = cmd;
            char *arg = (char*) malloc(sizeof(line));
            int index = 0;
            for (i = 0; i < n; i++)
            {
                if (line[i] == ' ' || line[i] == '\n')
                {
                    arg[index] = 0;
                    printf("arg %d is:%s \n", args_index, arg);
                    params[args_index++] = arg;
                    index = 0;
                    arg = (char*) malloc(sizeof(line));
                }
                else arg[index++] = line[i];
            }
            arg[index] = 0;
            params[args_index] = 0;
            args_index = 0;
            exec(cmd, params);
        }
    }
    else
    {
        wait((int*)0);
    }
    return 0;
}