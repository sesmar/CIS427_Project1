CFLAGS= -g
LDFLAGS= #-lsocket -lnsl
CC=g++

all: client server 

# To make an executable
client: client.o 
	$(CC) $(LDFLAGS) -o client client.o
 
server: server.o MessageManager.o CommandProcessor.o
	$(CC) $(LDFLAGS) -o server MessageManager.o CommandProcessor.o server.o

server.o: MessageManager.o

# To make an object from source
.c.o:
	$(CC) $(CFLAGS) -c $*.c

# clean out the dross
clean:
	-rm client server *.o core
