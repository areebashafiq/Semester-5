#include <iostream>
#include <unistd.h>
#include <cstring>
using namespace std;
int main()
{
    char buf[1024];
    close(0);
    read(0, buf, 1024);

    write(1, buf, strlen(buf));
    close(1);
    cout << "OS" << endl;
}