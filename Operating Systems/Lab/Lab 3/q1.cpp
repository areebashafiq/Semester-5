/*

Abdul Saboor
20L-1113
BDS-5A

*/

#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <fstream>
#include <string.h>
using namespace std;

int main(int argc, char *arg[])
{
    int max = 4;
    pid_t retVal;
    retVal = fork();
    if (retVal < 0)
    {
        // fork failed
        cout << "Fork Failed" << endl;
    }
    else if (retVal == 0)
    {
        // child process

        // checking if arguments are passed, performing computations
        if (argc > 2) // if numbers are passed
        {
            int sum = atoi(arg[2]);
            int max = atoi(arg[2]);
            int min = atoi(arg[2]);
            int temp = 0;
            for (int i = 3; i < argc; i++)
            {
                temp = atoi(arg[i]);
                sum += temp;
                if (temp >= max)
                {
                    max = temp;
                }
                if (temp <= min)
                {
                    min = temp;
                }
            }
            ofstream fout;
            fout.open("temp.txt", ios::out);
            fout << min << "\t" << max << "\t" << sum << endl;
            fout.close();
        }
    }
    else
    {
        wait(NULL);
        // parent process
        // reading params from file and storing in another file
        ifstream fin;
        fin.open("/Users/carbon/Documents/Semester-5/Operating Systems/Lab/Lab 3/temp.txt", ios::in);
        int min;
        int max;
        int sum;
        fin >> min >> max >> sum;
        if (int(sum) < 50)
        {
            cout << "Null Received" << endl;
        }
        else
        {
            ofstream fout;
            fout.open(arg[1], ios::out);
            fout << "Minimum integer is: " << min << endl;
            fout << "Maximum integer is: " << max << endl;
            fout << "Average of integers is: " << int(sum) / (argc - 2);
            fout.close();
        }
        fin.close();
        remove("temp.txt");
    }
}