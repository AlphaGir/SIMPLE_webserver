#include"aw.h"



/*
 AW OPERATION
 EW OPERATION
 */
extern char **environ;
 int codetype;//编码
 char last[4096];//发送消息
 char msg[20];//编码解释
 char path[100];//路径
 char v1[100];
 char value1[100];
 char v2[100];
 char value2[100];
 int fd;
 char buff[4096];
 int is_static;
 struct stat sbuf;

void cutout(char *uri,int begin,int end,char *ret)
{
     int i=0;
     int j=0;
     int s,e;
     for(;i<strlen(uri);i++)
     {
         if(uri[i]==begin)
         {
                 s=i;
         }
         if(uri[i]==end&&end!='\0')
          {
                  e=i;
                  if(s<e)
                  break;
          }
     }
     if(end=='\0')
     {
	     int len=strlen(uri)-s;
	     char ss[len];
	     memcpy(ret,uri+s+1,len-1);
	     ret[len]='\0';//EW   傻逼代码 
     }
     else
     {
          int len=e-s;
          memcpy(ret,uri+s+1,len-1);
          ret[len]='\0';
     }

 }

void doit(char* url)//获取返回的响应报文
{
   int i;
   char uri[100];
   char method[5];
   char version[10];
   char p1[300]="./";
   sscanf(url,"%s %s %s",method,uri,version);
   printf("uri:%s method:%s version:%s\n",uri,method,version);
   if(strcmp(method,"GET")!=0&&strcmp(method,"POST")!=0)
     {
       codetype=err(4,msg);
       printf("%s\n",msg);
       return;
     }
   else
     {
            if(!strstr(uri,"cgi"))//静态资源
            {
              strcpy(path,uri);
	      printf("path:%s\n",path);
              getstatic();
            }
            else
            {
	     cutout(uri,'/','?',path);
             strcat(p1,path);
	     strcpy(path,p1);
             cutout(uri,'?','=',v1);
             cutout(uri,'=','&',value1);
             cutout(uri,'&','=',v2);
             cutout(uri,'=','\0',value2);
	     printf("path:%s v1:%s value1:%s v2:%s value2:%s",path,v1,value1,v2,value2);//value2傻逼玩意儿
             getdynamic();
            }
     }
}
void getdynamic()
{
    char *str=value1;
    strcat(str,value2);
    if(stat(path,&sbuf)<0)
    {
                codetype=err(2,msg);
                return;
    }

    if(!(S_ISREG(sbuf.st_mode))||!(S_IXUSR&sbuf.st_mode))
    {
                codetype=err(3,msg);
		return;
    }
    char *data;
    int pid;
    pid=fork();
    //wait(NULL);//
    if(pid==0)
    {
          setenv("QUERY_STRING",value1,1);
	  execl(path,path,NULL);
    }
    
}
void getstatic()
{
         //建议资源有没有 没有404 然后可不可以访问
         //不可以就 403
         //有&&可以访问 读取资源返回字符串
     /*   int fd;   
	char buff[4096];
	char ss[1024];
	char temp[10];
	int is_static;
	struct stat sbuf;*/
	if(strcmp(path,"/")==0)
	{
		if((fd=open("./index.html",O_RDONLY))!=-1)
		{
			while(read(fd,buff,1024)>0)
			strcpy(last,buff);
	//		printf("首页::%s\n",last);
			codetype=err(1,msg);
			return ;
		}
	}
	if(stat(path,&sbuf)<0)
	{
		codetype=err(2,msg);
		return;
	}
	if(!(S_ISREG(sbuf.st_mode))||!(S_IRUSR&sbuf.st_mode))
	{
		codetype=err(3,msg);
		return ;
	}
	if((fd=open(path,O_RDONLY))!=-1)
	{
		while(read(fd,buff,1024)>0);
		strcpy(last,buff);
		codetype=err(1,msg);
		return;
	}
}
int err(int f,char *ret)
{
   switch(f)
   {
     case 1: f=200;strcpy(ret,"ok");break;
     case 2: f=404;strcpy(ret,"not found");break;
     case 3: f=403;strcpy(ret,"fobbiden permission");break;
     case 4: f=501;strcpy(ret,"not implement");break;
   }
   //printf("%d",f);
   return f;
}
