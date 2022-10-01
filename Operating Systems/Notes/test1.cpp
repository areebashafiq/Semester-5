#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main(int argc, char *arg[])
{

    int fd[2];

    if (pipe(fd) == -1)
    {

        cout << "Error Print" << endl;
        return 1;
    }

    int status;
    status = fork();

    if (status == 0)
    {

        close(fd[0]);

        int max = atoi(arg[1]);
        int min = atoi(arg[1]);
        int sum = atoi(arg[1]);

        for (int i = 2; i < argc; i++)
        {

            if (atoi(arg[i]) < min)
            {

                min = atoi(arg[i]);
            }

            if (atoi(arg[i]) > max)
            {

                max = atoi(arg[i]);
            }

            sum += atoi(arg[i]);
        }
        cout << max << " " << min << " " << sum << endl;

        int arr[] = {max, min, sum};

        write(fd[1], &arr, sizeof(arr));

        close(fd[1]);
    }

    else
    {

        wait(NULL);

        close(fd[1]);

        int arr[3];

        read(fd[0], &arr, 3);

        printf("Max: %d  Min: %d  Sum: %d\n", arr[0], arr[1], arr[2]);

        cout << "Im Parent Process" << endl;

        close(fd[0]);
    }
}