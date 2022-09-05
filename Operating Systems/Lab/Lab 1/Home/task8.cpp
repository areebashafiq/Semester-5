#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream fin;
    fin.open("input.txt", ios::in);
    if (!fin)
    {
        cout << "Error! File could not be found" << endl;
    }
    else
    {
        char temp;
        int max = 0;
        int num = 0;
        do
        {
            fin.get(temp);
            if (temp >= '0' && temp <= '9')
            {
                num += (int(temp) - 48);
                num *= 10;
            }
            else if (temp == ' ')
            {
                num /= 10;
                if (num >= max)
                {
                    max = num;
                    num = 0;
                }
            }
        } while (!fin.eof());
        fin.close();
        cout << "max number is: " << max << endl;
    }
}