#ifndef _AW_H_
#define _AW_H_
int err(int code,char *m);
void doit(char *url,int *code,char *m);
void handle_static(char *msg);
void handle_dynamic(char *msg);
#endif
