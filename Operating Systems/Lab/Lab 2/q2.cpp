#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <fstream>
using namespace std;

int main()
{
    pid_t retVal;
    retVal = fork();
    if (retVal < 0)
    {
        // fork failed
        cout << "fork failed" << endl;
    }
    else if (retVal == 0)
    {
        // child process
        fstream fin;
        fin.open("q1.txt", ios::in);
        if (!fin)
        {
            cout << "File not found" << endl;
        }
        else
        {
            int a = 0;
            int e = 0;
            int i = 0;
            int o = 0;
            int u = 0;
            char temp;
            do
            {
                fin.get(temp);
                if ((temp == 'A') || (temp == 'a'))
                {
                    a++;
                }
                else if ((temp == 'E') || (temp == 'e'))
                {
                    e++;
                }
                else if ((temp == 'I') || (temp == 'i'))
                {
                    i++;
                }
                else if ((temp == 'O') || (temp == 'o'))
                {
                    o++;
                }
                else if ((temp == 'U') || (temp == 'u'))
                {
                    u++;
                }

            } while (!fin.eof());
            cout << "Vovel Count: " << endl;
            cout << "a " << a << endl;
            cout << "e " << e << endl;
            cout << "i " << i << endl;
            cout << "o " << o << endl;
            cout << "u " << u << endl;
        }
    }
    else
    {
        wait(NULL);
        // parent process
        cout << "Program Completed." << endl;
    }
}