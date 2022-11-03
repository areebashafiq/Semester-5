#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <pthread.h>

using namespace std;

void *thread1(void *arg)
{
    int id = (long)arg;
    cout << "Hello from thread " << id << endl;
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    int n = atoi(argv[1]);
    pthread_t t[n];
    for (int i = 0; i < n; i++)
    {
        cout << "Creating thread " << i << endl;
        pthread_create(&t[i], NULL, thread1, (void *)i);
        if (i % 4 == 0)
            sleep(1);
    }
    for (int i = 0; i < n; i++)
        pthread_join(t[i], NULL);

    pthread_exit(NULL);
    return 0;
}