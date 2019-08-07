#include"aw.h"
/*
 恶心的操作
 */

int err(int code,char m[]);
void doit(char* url)//获取返回的响应报文
{
   int i;
   char uri[50];
   char method[5];
   char version[5];
   char v1[10];
   char v2[10];
   char value1[100];
   char value2[100];
   sscanf(url,"%s %s %s ",method,uri,version);
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
               sscanf(uri,"%s?%s=%s&%s=%s",path,v1,value1,v2,value2);
	       printf("path:%s v1:%s value1:%s v2:%s value2:%s",path,v1,value1,v2,value2);
               //getdynamic(path,v1,value1,v2,value2,sendmsg,*code,m);
            }
     }
}
//void getdynamic(char *uri,char *v1,char *value1,char *v2,char *value2,char *sendmsg,int *code,char *m)
//{
     
//}
void getstatic()
{
         //建议资源有没有 没有404 然后可不可以访问
         //不可以就 403
         //有&&可以访问 读取资源返回字符串
        int fd;   
	char buff[4096];
	char ss[1024];
	char temp[10];
	int is_static;
	struct stat sbuf;
	if(strcmp(path,"/")==0)
	{
		if((fd=open("index.html",O_RDONLY))!=-1)
		{
			while(read(fd,buff,1024)>0)
			strcpy(sendmsg,buff);
			printf("%s\n",sendmsg);
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
		strcpy(sendmsg,buff);
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
   printf("%d",f);
   return f;
}
int main()
{
   char *url="GET /form_action.cgi?fname=sbsbsbbssbsb&lname=shshdhdhd HTTP/1.1\r\nContent-Type:text/html\r\nContent-Length: 11\r\nServer: mengkang\r\n\r\nhello world";
   int m;
   doit(url);
   printf("%d %s",codetype,msg);
}
