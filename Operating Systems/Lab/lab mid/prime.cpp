#include<iostream>
using namespace std;

bool prime(int num)
{
    int check=0;
    for(int i=1;i<num;i++)
    {
        if((num%i)==0)
            check++;
            cout<<(num%i)<<endl;
    }
    if(check>0)
    {
        return false;
    }
    return true;
}

int main()
{
    bool temp=prime(9);
}