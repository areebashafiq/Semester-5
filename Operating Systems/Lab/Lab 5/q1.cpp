// Abdul Saboor
// 20L-1113
// BDS-5A1

// This program sends data to child from a file through pipes, teh child removes special characters and returns through pipe,
// parent then writes back to file

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;
#define BUFFER_SIZE 100
#define READ_END 0
#define WRITE_END 1
int main(void)
{
    char write_msg[BUFFER_SIZE];
    char read_msg[BUFFER_SIZE];
    int pipe1[2], pipe2[2];
    pid_t pid;

    // creating pipe
    if ((pipe(pipe1) == -1) || (pipe(pipe2) == -1))
    {
        cout << "Pipe failed" << endl;
    }

    // creating fork
    pid = fork();
    if (pid < 0)
    {
        cout << "Fork Failed" << endl;
        return 1;
    }
    if (pid > 0)
    {
        // parent
        // closing unused pipes
        close(pipe1[READ_END]);
        close(pipe2[WRITE_END]);

        // reading form file
        char buf[10];
        int fd = open("file.txt", O_RDONLY, S_IRUSR);
        ssize_t size = read(fd, write_msg, sizeof(write_msg));

        write(pipe1[WRITE_END], write_msg, sizeof(write_msg));

        // writing to pipe1
        wait(NULL); // waiting for child to complete

        // reading from pipe2
        read(pipe2[READ_END], read_msg, strlen(write_msg));
        read_msg[size] = '\0';
        cout << size << endl;
        cout << read_msg << endl;

        // writing to file
        int fd1 = open("file1.txt", O_RDWR | O_CREAT, 777);
        write(fd1, read_msg, size);

        // closing pipes
        close(pipe1[WRITE_END]);
        close(pipe2[READ_END]);
    }
    else
    {
        sleep(1);
        // child process
        // closing unused pipes
        close(pipe1[WRITE_END]);
        close(pipe2[READ_END]);

        // reading from pipe1
        read(pipe1[READ_END], read_msg, BUFFER_SIZE);

        // iterating and removing special character
        for (int i = 0; i < strlen(read_msg); i++)
        {
            char temp = read_msg[i]; // storing for comaprison
            if ((temp == '&') || (temp == '@') || (temp == '#') || (temp == '%') || (temp == '?') || (temp == '$') || (temp == '"') || (temp == '~'))
            {
                write_msg[i] = ' ';
            }
            else
            {
                write_msg[i] = read_msg[i];
            }
        }
        // writing to pipe 2
        write(pipe2[WRITE_END], write_msg, strlen(write_msg));

        // closing pipes
        close(pipe1[READ_END]);
        close(pipe2[WRITE_END]);
    }
    return 0;
}
