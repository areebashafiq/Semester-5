// this file is an implementation of simple shell

#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main()
{
    string command;
    while (true)
    {
        // printing current directory
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        cout << cwd << " $ ";
        getline(cin, command);

        // splitting command into arguments into a dynamic char array
        char **args = new char *[command.length()];
        int i = 0;
        string arg;
        for (char c : command)
        {
            if (c == ' ')
            {
                args[i] = new char[arg.length() + 1];
                strcpy(args[i], arg.c_str());
                i++;
                arg = "";
            }
            else
            {
                arg += c;
            }
        }
        args[i] = new char[arg.length() + 1];
        strcpy(args[i], arg.c_str());
        i++;
        args[i] = NULL;

        // checking if first argument is exit
        if (strcmp(args[0], "exit") == 0)
        {
            goto END;
        }
        // implementing cd command
        else if (strcmp(args[0], "cd") == 0)
        {
            chdir(args[1]);
        }
        else
        {
            // creating child process
            int pid = fork();
            if (pid == 0)
            {
                // child process
                execvp(args[0], args);
            }
            else
            {
                // parent process
                wait(NULL);
            }
        }
    }
END:;
    return 0;
}