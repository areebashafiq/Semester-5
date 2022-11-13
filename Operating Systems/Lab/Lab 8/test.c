#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <fcntl.h>

void *thread_fReader(void *arg)
{
    printf("in thread\n");
    char *f_name = (char *)arg;
    printf("%s\n", f_name);

    char *file_contents;

    int num_count = 0;
    int arr[500];

    int fd = open(arg, O_RDONLY, 0777);
    read(fd, &file_contents, 10000);
    printf("%s\n", file_contents);

    printf("End of function\n");
}

int main()
{
    pthread_t thread_a;
    pthread_t thread_b;

    char *f1 = "f1.txt";
    char *f2 = "f2.txt";

    pthread_create(&thread_a, NULL, *thread_fReader, f1);
    printf("Started thread [A]\n");
    pthread_create(&thread_b, NULL, *thread_fReader, f2);
    printf("Started thread [B]\n");

    pthread_join(thread_a, NULL);
    printf("\n\nEnded thread [A]\n");
    pthread_join(thread_b, NULL);
    printf("Ended thread [B]\n");

    return 0;
}