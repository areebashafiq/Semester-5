#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fstream>
#include <fcntl.h>
#include <sys/stat.h>

using namespace std;

int main(int argc, char *argv[])
{
    int pid1 = fork();

    // reading from file1 and writing to pipe1 in child
    if (pid1 == 0)
    {
        int fd1 = open(argv[1], O_RDONLY);
        int fd2 = open("pipe1", O_WRONLY);
        char buf[100];
        int n;
        while ((n = read(fd1, buf, 100)) > 0)
        {
            write(fd2, buf, n);
        }
        close(fd1);
        close(fd2);
    }
    else
    {
        int pid2 = fork();
        // reading from file2 and writing to pipe2 in child
        if (pid2 == 0)
        {
            int fd1 = open(argv[2], O_RDONLY);
            int fd2 = open("pipe2", O_WRONLY);
            char buf[100];
            int n;
            while ((n = read(fd1, buf, 100)) > 0)
            {
                write(fd2, buf, n);
            }
            close(fd1);
            close(fd2);
        }
        else
        {
            // reading from pipe1 and pipe2 and writing to output file in parent
            int fd1 = open("pipe1", O_RDONLY);
            int fd2 = open("pipe2", O_RDONLY);
            int fd3 = open(argv[3], O_WRONLY | O_CREAT, 0666);
            char buf[100];
            int n;
            while ((n = read(fd1, buf, 100)) > 0)
            {
                write(fd3, buf, n);
            }
            while ((n = read(fd2, buf, 100)) > 0)
            {
                write(fd3, buf, n);
            }
            close(fd1);
            close(fd2);
            close(fd3);
        }
    }
}