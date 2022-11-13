// This file contains an implementation of the named pipes class.
// This class is used to create a named pipe and to read and write to it.
// The class is used in the main program to create a named pipe and to
// read and write to it.
//
// The class is implemented using the C++ standard library.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

int main()
{
    int fd;
    char *myfifo = "/tmp/myfifo";
    char buf[80];
    mkfifo(myfifo, 0666);
    fd = open(myfifo, O_CREAT | O_WRONLY);
    write(fd, "Hi", sizeof("Hi"));
    close(fd);
    fd = open(myfifo, O_RDONLY);
    read(fd, buf, sizeof(buf));
    cout << buf << endl;
    close(fd);
    unlink(myfifo);
    return 0;
}