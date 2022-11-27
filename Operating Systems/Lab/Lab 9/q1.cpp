// implementtaion of dining philosophers problem using semaphores

#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>

using namespace std;

// one semaphore for each chopstick
sem_t chopstick[5];

// one thread for each philosopher
pthread_t philosopher[5];

// function to be executed by each thread
void *philosopher_func(int id)
{
    int left = id;
    int right = (id + 1) % 5;

    while (true)
    {
        // think
        cout << "Philosopher " << id << " is thinking" << endl;
        sleep(rand() % 5);

        // hungry
        cout << "Philosopher " << id << " is hungry" << endl;

        // pick up chopsticks (wait if not available)
        sem_wait(&chopstick[left]); // pick up left chopstick if available
        cout << "Philosopher " << id << " picked up left chopstick" << endl;
        sem_wait(&chopstick[right]); // pick up right chopstick if available
        cout << "Philosopher " << id << " picked up right chopstick" << endl;

        // eat
        cout << "Philosopher " << id << " is eating" << endl;
        sleep(rand() % 5);

        // put down chopsticks and think again by using sem_post
        sem_post(&chopstick[left]); // put down left chopstick
        cout << "Philosopher " << id << " put down left chopstick" << endl;
        sem_post(&chopstick[right]); // put down right chopstick
        cout << "Philosopher " << id << " put down right chopstick" << endl;

        cout << "Philosopher " << id << " has finished eating" << endl;
    }
}

int main()
{
    srand(time(NULL));

    // initialize semaphores
    for (int i = 0; i < 5; i++)
        sem_init(&chopstick[i], 0, 1); // create semaphore with initial value 1, which means that the chopstick is available

    // create threads
    for (int i = 0; i < 5; i++)
        pthread_create(&philosopher[i], NULL, (void *(*)(void *))philosopher_func, (void *)i); // create thread with id i

    // wait for threads to finish
    for (int i = 0; i < 5; i++)
        pthread_join(philosopher[i], NULL); // wait for thread with id i to finish and then continue

    return 0;
}