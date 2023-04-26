
all:
	gcc -c lista.c
	ar rcs liblista.a lista.o
	gcc -o worker worker.c -pthread 
	gcc -o server server.c -pthread -L. -llista
	gcc -o client client.c -pthread
	
