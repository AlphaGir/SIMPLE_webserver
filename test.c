#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
    char buf[4096];
    int fd;
    if((fd=open("./index.html",O_RDONLY))==0)
     perror("open:");
    else
   {
     printf("open success\n");
  }
    while((read(fd,buf,1024)>0))
    {
    }
    printf("%s",buf);
}
