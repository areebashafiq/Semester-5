// this is an implementation of the grep command

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <vector>

using namespace std;

int main()
{
    // sample grep command
    string command = "grep -c \"Sundus\" test.txt";

    // split command into arguments
    char **args = new char *[command.length()];
    int i = 0;
    string arg;
    for (char c : command)
    {
        if (c == ' ')
        {
            args[i] = new char[arg.length()];
            strcpy(args[i], arg.c_str());
            i++;
            arg = "";
        }
        else
        {
            arg += c;
        }
    }
    args[i] = new char[arg.length()];
    strcpy(args[i], arg.c_str());
    i++;

    // add null to the end of the arguments
    args[i] = NULL;

    // execute the command
    execvp(args[0], args);
}