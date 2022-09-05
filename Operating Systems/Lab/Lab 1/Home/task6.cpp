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
        ofstream out;
        out.open("output.txt", ios::out);
        do
        {
            fin.get(temp);
            if ((temp >= 'A' && temp <= 'Z') || (temp >= 'a' && temp <= 'z'))
            {
                out << temp;
            }
        } while (!fin.eof());
        out.close();
        fin.close();
    }
}