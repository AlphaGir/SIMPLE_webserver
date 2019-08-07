#ifndef _AW_H_
#define _AW_H_
int err(int code,char *m);
void doit(char *url,int *code,char *m,char *sendmsg);
void getstatic(char *uri,char *sendmsg,int *code,char *m);
void getdynamic(char *uri,char *v1,char *value1,char *v2,char *value2,char *sendmsg,int *code,char *m);
#endif
