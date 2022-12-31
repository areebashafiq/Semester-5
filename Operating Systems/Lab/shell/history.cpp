// this file implements a shell that maintains a history of last 10 commands
// and allows the user to execute any of the last 10 commands by typing !n
// where n is the index of the command in the history
// when user types !! the last command is executed

#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <cstring>

using namespace std;

// function to execute a command
// todo: implement part1 in this function
void execute_command(string command)
{
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

    // implementing cd command
    if (strcmp(args[0], "cd") == 0)
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
            // print error if command is not found
            if (execvp(args[0], args) == -1)
            {
                cout << "Command not found" << endl;
            }
        }
        else
        {
            // parent process
            wait(NULL);
        }
    }
}

int main()
{
    // just maintains history, implements some checks and passes the command to execute_command

    system("clear");
    string command;
    while (true)
    {
        // vector to store history of last 10 commands
        static vector<string> history;

        int flag = 0;

        // printing current directory
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        cout << cwd << " $ ";
        getline(cin, command);

        // implementing exit command
        if (strcmp(command.c_str(), "exit") == 0)
        {
            goto END;
        }

        // implementing !!
        if (strcmp(command.c_str(), "!!") == 0)
        {
            flag = 1;
            // print the last command if history is not empty
            if (history.size() > 0)
            {
                command = history[history.size() - 1];
            }
            else
            {
                cout << "No commands in history" << endl;
                continue;
            }
        }

        // implementing !n
        if (command[0] == '!')
        {
            flag = 1;
            int n = stoi(command.substr(1));
            if (n > 0 && n <= history.size())
            {
                command = history[n - 1];
            }
            else
            {
                cout << "No such command in history" << endl;
                continue;
            }
        }

        if (flag == 0)
        {
            // implementing history
            if (history.size() == 10)
            {
                history.erase(history.begin());
            }
            history.push_back(command);
        }

        // executing command
        execute_command(command);
    }
END:;
    return 0;
}