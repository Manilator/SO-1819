
CC = gcc
CFLAGS = -Wall -g


EXEC : utils.o sv.o ag.o main.c
	$(CC) $(CFLAGS) utils.o sv.o ag.o main.c -o EXEC

utils.o: utils.c
	$(CC) $(CFLAGS) -c utils.c -o utils.o

sv.o: sv.c 
	$(CC) $(CFLAGS) -c sv.c -o sv.o

ag.o: ag.c 
	$(CC) $(CFLAGS) -c ag.c -o ag.o


clean:
	rm EXEC
	rm *.o
	rm -rf vendas
	rm -rf agregadores