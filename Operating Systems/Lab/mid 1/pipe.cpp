// This file contains an implementation of pipe system call

#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

using namespace std;

int main()
{
    int fd[2];
    int ret = pipe(fd);
    if (ret == -1)
    {
        perror("pipe");
        return 1;
    }
    int pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return 1;
    }
    if (pid == 0)
    {
        // child process
        close(fd[0]);
        dup2(fd[1], 1);
        execlp("ls", "ls", "-l", NULL);
        perror("execlp");
        return 1;
    }
    else
    {
        // parent process
        close(fd[1]);
        dup2(fd[0], 0);
        execlp("wc", "wc", "-l", NULL);
        perror("execlp");
        return 1;
    }
    return 0;
}