// This file contains an implementation of fifo system call

#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

int main()
{
    int ret = mkfifo("fifo", 0666);
    if (ret == -1)
    {
        perror("mkfifo");
        return 1;
    }
    int fd = open("fifo", O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return 1;
    }
    char buf[100];
    int n = read(fd, buf, 100);
    if (n == -1)
    {
        perror("read");
        return 1;
    }
    write(1, buf, n);
    close(fd);
    return 0;
}