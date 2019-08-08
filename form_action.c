#include<stdio.h>
#include"aw.h"
int main(int arg,char *agv[])
{
        char tmp[300];
	char arg1[100];
	if ((tmp==getenv("QUERY_STRING")) != NULL) 
		strcpy(arg1,tmp);
	printf("Content type: text/html\n\n");
        printf("<html>\n");
        printf("<head><title>Congratualation</title></head>\n");
        printf("<body bgcolor=\"#666666\">%s已经成功注册</body>\n",arg1);
        printf("</html>\n");
        fflush(stdout);
}
