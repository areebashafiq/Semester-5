// This file contains implementation of dup2 system call

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
    int fd = open("test.txt", O_RDONLY, 0666);
    if (fd == -1)
    {
        perror("open");
        return 1;
    }
    int fd2 = dup2(fd, 0);
    if (fd2 == -1)
    {
        perror("dup2");
        return 1;
    }
    char buf[100];               // read buffer
    int n = read(fd2, buf, 100); // so read command returns the number of bytes read
    if (n == -1)
    {
        perror("read");
        return 1;
    }
    // cout << n << endl;
    // cout << buf << endl;
    write(1, buf, n);
    close(fd);
    return 0;
}