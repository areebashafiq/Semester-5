#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
using namespace std;

int main()
{
char temp[30];

int pipe1[2];
int pipe2[2];

pipe(pipe1);
pipe(pipe2);

int p1=fork();
if(p1>0)
{
wait(NULL);
close(pipe1[1]);
read(pipe1[0], temp, 30);

int p2=fork();
if(p2>0)
{
wait(NULL);
read(pipe2[0], temp, 30);

int p3=fork();
if(p3>0)
{
wait(NULL);
}
else if(p3==0)
{
int arr[30];
int j=0;
int num=0;
for(int i=0; i<30; i++)
{
if(temp[i]==' ')
{
cout<<num<<endl;
arr[j++]=num;
num=0;
continue;
}
else
{
num=num*10+(temp[i]-'0');                
}
}

for(int i=0; i<j; i++)
{
for(int k=i+1; k<j; k++)
{
if(arr[i]>arr[k])
{
int temp=arr[i];
arr[i]=arr[k];
arr[k]=temp;
}
}
}

int fd = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
for(int i=0; i<j; i++)
{
char temp[30];
sprintf(temp, "%d ", arr[i]);
write(fd, temp, strlen(temp));
}
}

}
else if(p2==0)
{
read(pipe1[0], temp, 30);

for(int i=0; i<30; i++)
{
if(temp[i]=='#' || temp[i]=='$' || temp[i]==')' || temp[i]=='*' || temp[i]=='^')
{
temp[i]=' ';
}
}

write(pipe2[1], temp, 30);
}
}
else if(p1==0)
{
close(pipe1[0]);
int fd = open("q3.txt", O_RDONLY);
read(fd, temp, 30);

write(pipe1[1], temp, 30);
close(pipe1[1]);
}

return 0;
}