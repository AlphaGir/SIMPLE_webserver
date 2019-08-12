server:	server.c form_action.cgi
	gcc -o server server.c aw.c form_action.cgi 
form_action.cgi:	form_action.c    
	gcc -o form_action.cgi form_action.c
clean:
	rm -f server
	rm -f form_action.cgi

