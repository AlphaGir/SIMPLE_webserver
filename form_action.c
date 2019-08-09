#include<stdio.h>
#include"aw.h"
int main(int arg,char *agv[])
{
        char *p2 = (char *)getenv("QUERY_STRING");
	char arg1[100];
	printf("喂喂喂 有人运行么\n");
	if (p2) 
		//strcpy(arg1,tmp);
	//printf("%s",arg1);
	printf("Content type: text/html\n\n");
        printf("<html>\n");
        printf("<head><title>Congratualation</title></head>\n");
        printf("<body bgcolor=\"#666666\">%s已经成功注册</body>\n",p2);
        printf("</html>\n");
        fflush(stdout);
}
