// A program that will create a number N of threads specified in the command line,
// each of which prints out a hello message and its own thread ID. To see how the execution of the
// threads interleaves, make the main thread sleep for 1 second for every 4 or 5 threads it creates.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *print_hello(void *arg)
{
    printf("Hello from thread %d \n", (int)arg);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    int N = atoi(argv[1]);
    pthread_t threads[N];
    for (int i = 0; i < N; i++)
    {
        pthread_create(&threads[i], NULL, print_hello, (void *)i);
        if (i % 4 == 0 || i % 5 == 0)
        {
            sleep(1);
        }
    }
    pthread_exit(NULL);
}