
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

using namespace std;

int main()


{

    int pipe_fd[2];

    int b=pipe(pipe_fd);

    if(b==-1)
    {
        cout<<"pipe call failed"<<endl;
    }


    int a=fork();

    if(a==0)
    {
          
       /*Child 1 will then read the data from the file, remove special characters, and write the modified data to
        the same file again.*/
      
        char buf[100] ;
        

        int b=read(pipe_fd[0],&buf,sizeof(buf));  // ---> blocking condition

        int fd=open("file.txt",O_RDWR) ;  // 0666---> FOR file access

        char array[1000];
        
        int count= read(fd,&array,b);

        cout<<"data i have read is : "<<count<<endl;

       
char array1[100];

int q=0;

       for(int i=0;i<count;i++){

        if(array[i]>='0' && array[i]<= '9')
        {
             array1[q]=array[i];
             q++;
        }
       }

        cout<<"q is : "<<q<<endl;

       array1[0]='\0';


       int ac= write(fd,&array1,q);
       
       int n_baby=fork();

       if(n_baby==0)
       {


        char array[100];

        int fd=open("file.txt",O_RDWR) ;
   
       
        int count = read(fd,&array,sizeof(array));
         

        char array1[100];
       
       int q=0;
        for(int i=0;i<count;i++)
        {
            if(array[i]=='\0'){
               
                for(int j=i;j<count ;j++)
                {
                    array1[q]=array[j];
                    q++;
                }
            }
        }


       cout<<"data i have read in child 2 is "<<endl<<endl;

       for(int i=0;i<q;i++)
       {
        cout<<array1[i]<<endl;
       }
   

       for (int i=0;i<q;i++)
       {
        for(int j=0;j<q;j++)
        {
            if(array1[i]<array1[j])
            {
                swap(array1[i],array1[j]);
            }
        }
       }


        cout<<"data after soring is : "<<endl;
       for(int i=0;i<q;i++)
       {
        cout<<array1[i]<<endl;
       }
          
          int n2_baby=fork();

          if(n2_baby==0)
          {
              

        char array[100];

        int fd=open("file.txt",O_RDWR) ;
   
       
        int count = read(fd,&array,sizeof(array));
         
        char array1[100];

        int q=0;
        for(int i=0;i<count;i++)
        {
            if(array[i]=='\0'){
               
                for(int j=i+1;j<count ;j++)
                {
                    array1[q]=array[j];
                    q++;
                }
            }
        }
   

        cout<<"The characters that are left in the file are : "<<q<<endl<<endl;


        cout<<"The data i have read in the 3rd child is "<<endl;

        for(int i=0;i<q;i++)
        {
            cout<<array1[i]<<endl;
        }
  
        int fd1=open("final.txt",O_CREAT | O_WRONLY , 0666) ;  //0666---> FOR file access

         int s = write(fd1,&array1,q);

          }

          else if(n2_baby>0)
          {
            //parent process
            wait(NULL);
          }

       }
       else if(n_baby>0)
       {
        //parent process
        
        wait(NULL);

       }

    }
    else if(a>0)
    {

        /*The parent process first creates a file and writes data in it using the write system call and writes the
        data to a pipe. The input file can have any number of integers and special characters.
        The data is as follows: 11!17!21$6$89!43$67*/
        //parent process

        int fd=open("file.txt",O_CREAT | O_WRONLY , 0666) ;  //0666---> FOR file access

        write(fd,"11!17!21$6$89!43$67",19);
        
        write(pipe_fd[1],"11!17!21$6$89!43$67",19);

        wait(NULL);
    }
    else {
     cout<<"fork call failed"<<endl;
    }




}