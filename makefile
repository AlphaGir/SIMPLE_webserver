server:	server.c aw.h aw.c form_action.cgi
	gcc -o server.o server.c -o aw.o aw.c form_action.cgi
form_action.cgi:	form_action.c
	gcc -o form_action.cgi form_action.cgi
clean:
	rm -f *.o

