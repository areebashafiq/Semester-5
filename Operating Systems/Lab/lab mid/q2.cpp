// Abdul Saboor
// 20L-1113
// BDS-5A1
// Question 1

// This task creates a pipe named ‘mStreamChannel’. On the writing end, the Writer sends about 580000
// integers to the pipe. The data is not to send as a whole. Your job is to send the data in the following
// format.
// MaxIterations = 5000
// ChunkSize = 29
// IntegerPerChunks=4
// Interval (Microsecond)=250
// Interval to be append after each iteration.

#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <cstring>
#include <string>
#include <sys/wait.h>
#define READ_END 0
#define WRITE_END 1

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
	int fd[2];
	int sum=0, total =580000, chunk=29;
	int arr[29][4];
	if(pipe(fd)==-1)
	{
		cout<<"Pipe Error"<<endl;
	}
	int pid=fork();
	if(pid==-1) 
	{
		cout<<"fork failed"<<endl;
	}
	if (pid==0)
	{
	int prime_num=0;
	for(int i=0;i<total/29;i++)
	{
		close(fd[WRITE_END]);
		read(fd[0],&arr,sizeof(int)*chunk*4);
		prime_num=0;
		for(int i=0;i<chunk;i++)
		{
			for(int j=0;j<4;j++)
			{
				if(prime(arr[i][j])==true)
					prime_num++;
			}
			cout<<i<<" : "<<prime_num<<endl;
			prime_num=0;
		}
		float average = sum/total;
		cout << "average = " << average << endl;
		close(fd[READ_END]);
	}
	}
	else
	{
		close(fd[READ_END]);
		for(int i=0;i<total;i++)
		{
			for(int i=0;i<chunk;i++)
			{
				for(int j=0;j<4;j++)
					arr[i][j] = rand();
			}
			write(fd[1],&arr,sizeof(int)*chunk*4);
		}
		close(fd[WRITE_END]);
		wait(NULL); 
	}
}