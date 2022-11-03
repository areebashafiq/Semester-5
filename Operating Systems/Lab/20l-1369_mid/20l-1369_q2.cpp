#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <cstring>
#include <string>
#include <sys/wait.h>

using namespace std;

int main()
{
	int fd[2];
	//abc here is the number of integers we want to write 
	int abc=580000;

    //this is the chunk size as we are asked to make a chunk of 29 

	int chunk=29;

    //making array of 29 rows and 4 columns means   we have 29 chunks and each chunk will have 4 integers

	int arr[29][4];
	if(pipe(fd)==-1)
	{
		cout<<"Pipe Error"<<endl;
	}

    //fork call to make parent and child processes

	int pid=fork();
	if(pid>0)
	{
        //parent child

		for(int i=0;i<abc/116;i++)   //abc here is the limit
		{
			for(int i=0;i<chunk;i++)
			{
				for(int j=0;j<4;j++)
                {
					arr[i][j] = rand();
                }
			}
			write(fd[1],&arr,sizeof(int)*116);
		}

        //parent should wait until the child will read these numbers
		wait(NULL);

	}
	else if (pid==0)
	{
		int q=0;
		for(int i=0;i<abc/116;i++)   //abc/29  as we have deviedd the in the chunks of 29
		{
			//read the data from the parent 
            read(fd[0],&arr,sizeof(int)*116);  
            q=0;

            for (int k=0;k<29;k++)
            {
                for(int j=0;j<4;j++)
                {
                    int n=arr[k][j];

                    for (int w = 2; w <= n/2; ++w) 
                    {
                        if (n % w == 0) 
                        {
                            q++;
                            break;
                        }
                    }
            
                }
            }
			cout<<"count of prime number in "<<i<<" th chunk is "<<q<<endl;
			q=0;
		}
	}
	else 
	{
		cout<<"fork call failed"<<endl;
	}
}