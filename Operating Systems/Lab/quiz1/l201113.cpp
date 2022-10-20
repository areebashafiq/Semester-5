// Abdul SAboor
// 20L-1113
// BDS-5A1

#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;

#define READ_END 0
#define WRITE_END 1
#define array_size 1000
#define array_size2 9

int main()
{
    int pipefd[2];
    if (pipe(pipefd) == -1)
    {
        cout << "Pipe failed" << endl;
        return 1;
    }
    int pid = fork();
    if (pid == 0)
    {
        // child process
        close(pipefd[WRITE_END]);
        int arr1[array_size][array_size2];
        read(pipefd[READ_END], arr1, sizeof(arr1));

        // calculating average
        long avg = 0;
        for (int i = 0; i < array_size; i++)
        {
            int avg1 = 0;
            for (int j = 0; j < array_size2; j++)
            {
                avg1 += arr1[i][j];
            }
            avg += avg1 / array_size2;
        }
        cout << "Average of numbers is: " << avg / array_size << endl;
        close(pipefd[READ_END]);
        exit(0);
    }
    else if (pid > 0)
    {
        // parent process
        close(pipefd[READ_END]);
        int arr[array_size][array_size2];
        for (int i = 0; i < array_size; i++)
        {
            for (int j = 0; j < array_size2; j++)
            {
                arr[i][j] = rand() % (array_size * array_size2);
            }
        }
        cout << endl;
        write(pipefd[WRITE_END], arr, sizeof(arr));
        close(pipefd[WRITE_END]);
    }
    else
    {
        // error
        cout << "fork failed" << endl;
    }
}