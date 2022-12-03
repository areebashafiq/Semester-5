// implementing reading writing problem using semaphores

#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>

using namespace std;

sem_t mutex, wrt;
int readcount = 0;
int data = 0;

void *reader(void *arg)
{
    int f;
    f = ((int)arg);
    sem_wait(&mutex);
    readcount++;
    if (readcount == 1)
        sem_wait(&wrt);
    sem_post(&mutex);
    cout << "Data read by the reader " << f << " is " << data << endl;
    sleep(1);
    sem_wait(&mutex);
    readcount--;
    if (readcount == 0)
        sem_post(&wrt);
    sem_post(&mutex);
}

void *writer(void *arg)
{
    int f;
    f = int(arg);
    sem_wait(&wrt);
    data++;
    cout << "Data written by the writer " << f << " is " << data << endl;
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
        pthread_create(&wtid[i], NULL, writer, (void *)i);
        pthread_create(&rtid[i], NULL, reader, (void *)i);
    }
    for (i = 0; i <= 2; i++)
    {
        pthread_join(wtid[i], NULL);
        pthread_join(rtid[i], NULL);
    }
}