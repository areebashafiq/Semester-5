// This file contains an implementation of open system call

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    int fd = open("test.txt", O_CREAT | O_RDWR, 0666);
    if (fd == -1)
    {
        perror("open");
        return 1;
    }
    write(fd, "Hello World", 11);
    close(fd);
    return 0;
}