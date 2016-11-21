all: server client doprocessing.o

server: server.o doprocessing.o
	gcc -o server server.o doprocessing.o

server.o: server.c
	gcc -c server.c

client: client.o
	gcc -o client client.o

client.o: client.c
	gcc -c client.c

doprocessing.o: doprocessing.c
	gcc -c doprocessing.c

clean:
	rm *.o client server
	
