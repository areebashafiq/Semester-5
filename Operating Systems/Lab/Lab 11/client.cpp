// implementing client server communication using shared memory
// this is the client program

#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

using namespace std;

int main()
{
    int shmid;
    key_t key;
    char *shm, *s;

    key = 567;

    // create the segment
    if ((shmid = shmget(key, 27, 0666)) < 0)
    {
        perror("shmget");
        exit(1);
    }

    // attach the segment to our data space
    // if ((shm = shmat(shmid, NULL, 0)) == (char *)-1)
    if ((shm = (char *)shmat(shmid, NULL, 0)) == (char *)-1)
    {
        perror("shmat");
        exit(1);
    }

    // read what the server put in the memory
    for (s = shm; *s != NULL; s++)
        cout << *s;
    cout << endl;

    // change the first character of the segment to '*', indicating we have read the segment
    *shm = '*';

    exit(0);
}
