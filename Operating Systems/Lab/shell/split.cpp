#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

// function to remove starting and ending spaces from a string
string trim(string str)
{
    int start = 0;
    int end = str.length() - 1;
    while (str[start] == ' ')
    {
        start++;
    }
    while (str[end] == ' ')
    {
        end--;
    }
    return str.substr(start, end - start + 1);
}

// function to split a string based on a delimiter and return a char array
char **split(string command, char delimiter)
{
    char **args = new char *[command.length()];
    int i = 0;
    string arg;
    for (int j = 0; j < command.length(); j++)
    {
        if (command[j] == delimiter)
        {
            arg = trim(arg);
            args[i] = new char[arg.length()];
            strcpy(args[i], arg.c_str());
            i++;
            arg = "";
        }
        else
        {
            arg += command[j];
        }
    }
    arg = trim(arg);
    args[i] = new char[arg.length()];
    strcpy(args[i], arg.c_str());
    i++;
    args[i] = NULL;
    return args;
}

int main()
{
    // get the command from the user
    string command;
    cout << "Enter a command: ";
    getline(cin, command);

    // split the command into commands based on |
    char **commands = split(command, '|');

    // printing the tokens in the commands array
    for (int i = 0; commands[i] != NULL; i++)
    {
        cout << "Arguments in command " << i + 1 << endl;
        char **args = split(commands[i], ' ');
        for (int j = 0; args[j] != NULL; j++)
        {
            cout << args[j] << endl;
        }
        cout << endl
             << "------------------------" << endl;
    }
}