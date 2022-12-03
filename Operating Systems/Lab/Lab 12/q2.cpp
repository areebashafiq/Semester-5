#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int counter = 0;

// semaphores
int a = 1;
int b = 0;
int c = 0;

void wait(int &s)
{
    while (s <= 0)
        ;
    s--;
}

void signal(int &s)
{
    s++;
}

void *printa(void *args)
{
    while (1)
    {
        wait(a);
        cout << "a";
        counter++;
        if (counter % 3 == 0)
            signal(c);
        else
            signal(a);
    }
}

void *printb(void *args)
{
    while (1)
    {
        wait(b);
        cout << "b";
        signal(a);
    }
}

void *printc(void *args)
{
    while (1)
    {
        wait(c);
        cout << "c";
        signal(b);
    }
}

int main(int argc, char *argv[])
{

    pthread_t t1;
    pthread_t t2;
    pthread_t t3;

    while (1)
    {

        pthread_create(&t1, NULL, printa, NULL);
        pthread_create(&t2, NULL, printb, NULL);
        pthread_create(&t3, NULL, printc, NULL);
    }

    return 0;
}