/*
Abdul Saboor
20L-1113
BDS-5A

This file excepts a file path and a substring, prints occurences of substring if file exists
*/

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main(int argc, char *arg[])
{
    ifstream fin;
    fin.open(arg[1], ios::in);
    if (!fin)
    {
        cout << "File does not exists." << endl;
    }
    else
    {
        // file exists so we would do the real work
        int count = 0;
        do
        {
            char temp[100];
            fin.getline(temp, 100, ' ');
            if (strcmp(arg[2], temp) == 0)
            {
                count++;
            }
        } while (!fin.eof());
        if (count == 0)
        {
            cout << "No occurences of given word in file" << endl;
        }
        else
        {
            cout << "Word \"" << arg[2] << "\" found " << count << " times in file" << endl;
        }
    }

    return 0;
}