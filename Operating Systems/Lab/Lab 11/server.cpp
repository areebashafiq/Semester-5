// implementation of client server communication using shared memory
// this is the server program

#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main()
{
    int shmid;
    key_t key;
    char *shm, *s;

    key = 567;

    // create the segment
    if ((shmid = shmget(key, 27, IPC_CREAT | 0666)) < 0)
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

    // creating a string that reads from "numbers.txt" and puts it into the shared memory
    FILE *fp;
    char str[1000];
    fp = fopen("numbers.txt", "r");
    fscanf(fp, "%[^\n]", str);
    fclose(fp);
    cout << "Data from the file:\n"
         << str << endl;

    // put some things into the memory for the client to read
    s = shm;
    for (char c = 'a'; c <= 'z'; c++)
        *s++ = c;
    *s = NULL;

    // wait until the client changes the first character of our memory to '*', indicating that it has read what we put there
    while (*shm != '*')
        sleep(1);

    exit(0);
}