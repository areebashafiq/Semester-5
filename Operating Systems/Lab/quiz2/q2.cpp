// This program does following:
// implement reader-writer problem using semaphores
// create a new thread for each reader and writer
// just print out the message when a reader or writer is in the critical section

#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <cstdlib>

using namespace std;

// global variables
sem_t mutex, wrt;
int readcount = 0;

// reader thread
void *reader(void *arg)
{
    int f;
    f = ((intptr_t)arg);
    sem_wait(&mutex);
    readcount++;
    if (readcount == 1)
        sem_wait(&wrt);
    sem_post(&mutex);
    cout << "Reader " << f << " is reading" << endl;
    sleep(1);
    sem_wait(&mutex);
    readcount--;
    if (readcount == 0)
        sem_post(&wrt);
    sem_post(&mutex);
}

// writer thread
void *writer(void *arg)
{
    int f;
    f = ((intptr_t)arg);
    sem_wait(&wrt);
    cout << "Writer " << f << " is writing" << endl;
    sleep(1);
    sem_post(&wrt);
}

int main()
{
    int i, b;
    pthread_t rtid[5], wtid[5];
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);
    for (i = 0; i <= 2; i++)
    {
        pthread_create(&wtid[i], NULL, writer, (void *)(intptr_t)i);
    }
    for (i = 0; i <= 2; i++)
    {
        pthread_create(&rtid[i], NULL, reader, (void *)(intptr_t)i);
    }
    for (i = 0; i <= 2; i++)
    {
        pthread_join(wtid[i], NULL);
    }
    for (i = 0; i <= 2; i++)
    {
        pthread_join(rtid[i], NULL);
    }
    sem_destroy(&mutex);
    sem_destroy(&wrt);
    return 0;
}