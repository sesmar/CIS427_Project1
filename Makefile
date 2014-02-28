CFLAGS= -g
LDFLAGS= #-lsocket -lnsli
LDFLAGS1= -lpthread
CC=g++

all: client server 

# To make an executable
client: client.o 
	$(CC) $(LDFLAGS) -o client client.o
 
server: server.o MessageManager.o CommandProcessor.o UserManager.o ClientThread.o ServerThread.o Thread.o
	$(CC) $(LDFLAGS1) -o server Thread.o ClientThread.o ServerThread.o MessageManager.o CommandProcessor.o UserManager.o server.o

server.o: MessageManager.o

# To make an object from source
.c.o:
	$(CC) $(CFLAGS) -c $*.c

# clean out the dross
clean:
	-rm client server *.o
