#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

int main()
{
    char buf[500];
    int fd = open("file.txt", O_RDONLY, S_IRUSR);
    ssize_t size = read(fd, buf, sizeof(buf));

    write(2, buf, size);

    // while (size > 0)
    // {

    //     size = read(fd, buf, sizeof(buf));
    //     write(2, buf, size);
    // }

    return 0;
}
