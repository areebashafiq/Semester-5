/*
Abdul Saboor
20L-1113
BDS-5A1
*/

#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>
#include <fstream>

#define READ_END 0
#define WRITE_END 1
#define BUFFER_SIZE 1024

using namespace std;

int palindrome(int num)
{
    int n, digit, rev = 0;
    n = num;

    do
    {
        digit = num % 10;
        rev = (rev * 10) + digit;
        num = num / 10;
    } while (num != 0);
    if (n == rev)
        return true;
    else
        return false;
}

void func(string temp)
{
    int num = 0;
    for (int i = 0; i < temp.length(); i++)
    {
        if (temp[i] == ' ')
        {
            if (palindrome(num) == true)
            {
                cout << num << " ";
            }
            num = 0;
        }
        else
        {
            num *= 10;
            num += (int(temp[i]) - 48);
        }
    }
    if (palindrome(num) == true)
    {
        cout << num << " ";
    }
    cout << endl;
}

int main(int argc, char *argv[])
{
    char read_message[BUFFER_SIZE];
    char write_message[BUFFER_SIZE];
    int pipe1[2]; // defining pipe
    if (pipe(pipe1) == -1)
    {
        cout << "Pipe failed" << endl;
    }

    int pid = fork();
    if (pid < 0)
    {
        cout << "Fork Failed" << endl;
    }
    if (pid == 0)
    {
        // child process
        close(pipe1[READ_END]); // closing read end of pipe
        ifstream infile;
        infile.open(argv[1], ios::in);

        infile.read(write_message, BUFFER_SIZE);
        write(pipe1[WRITE_END], write_message, BUFFER_SIZE);
        infile.close();
        close(pipe1[WRITE_END]);
    }
    if (pid > 0)
    {
        // parent process
        close(pipe1[WRITE_END]);
        read(pipe1[READ_END], read_message, BUFFER_SIZE);
        int len = strlen(read_message);
        read_message[len - 4] = '\0';

        // now converting array to integers and finding palindrome
        string temp = strtok(read_message, "\n");
        func(temp);
        temp = strtok(NULL, "\n");
        func(temp);
        temp = strtok(NULL, "\n");
        func(temp);
    }
}