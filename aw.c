#include"aw.h"
#include<stdio.h>
/*
 
 */
int err(int code,char *m);
void doit(char* url,int *code,char *m,char *sendmsg)//获取返回的响应报文
{
   int i;
   char uri[50];
   char method[5];
   char version[5];
   char msg[20];
   char path[20];
   char v1[10];
   char v2[10];
   char value1[100];
   char value2[100];
   sscanf(url,"%s %s %s ",method,uri,version);
   if(strcmp(method,"GET")!=0&&strcmp(method,"POST")!=0)
     {
       *code=err(4,m);
       exit(1);
     }
   else
     {
            if(!strstr(uri,"cgi"))//静态资源
            {
              strcat(path,uri);
              getstatic(path,sendmsg,*code,m);
            }
            else
            {
               sscanf(uri,"%s?%s=%s&%s=%s",path,v1,value1,v2,value2);
               getdynamic(path,v1,value1,v2,value2,sendmsg,*code,m);
            }
     }
}
void getdynamic(char *uri,char *v1,char *value1,char *v2,char *value2,char *sendmsg,int *code,char *m)
{

}
void getstatic(char *uri,char *sendmsg,int *code,char *m)
{
         //建议资源有没有 没有404 然后可不可以访问
         //不可以就 403
         //有&&可以访问 读取资源返回字符串
           
        
}
int err(int f,char *ret)
{
   switch(f)
   {
     case 1: f=200,strcpy(ret,"ok");break;
     case 2: f=404,strcpy(ret,"not found");break;
     case 3: f=403,strcpy(ret,"fobbiden permission");break;
     case 4: f=501,strcpy(ret,"not implement");break;
   }
   printf("%d",f);
   return f;
}
int main()
{
   char *url="DELETE / HTTP/1.1\r\nContent-Type:text/html\r\nContent-Length: 11\r\nServer: mengkang\r\n\r\nhello world";
   int m;
   char *msg;
   doit(url,&m,msg);
   printf("%d %s",m,msg);
}
