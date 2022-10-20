// Abdul Saboor
// 20L-1113
// BDS-5A1

// program to explain working of file descriptors

#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
using namespace std;

int main()
{
    int file_desc = open("dup.txt", O_WRONLY | O_APPEND);
    if (file_desc < 0)
        cout << "Error opening the file" << endl;
    int pid = fork();
    if (pid == 0)
    {
        // child process
        int copy1_desc = dup(file_desc);
        write(copy1_desc, "This will be output to the file named dup.txt\n", 46);
        execlp("ls", "ls", "-l", NULL);
        exit(0);
    }
    else
    {
        // parent process
        cout << "Parent process" << endl;
        int copy2_desc = dup(file_desc);
        write(copy2_desc, "This will also be output to the file named dup.txt\n", 51);
        wait(NULL);
    }
    return 0;
}