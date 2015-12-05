C_FLAGS = -g -Wall
BIN_DIR = bin
CC = g++

doublet: src/doublet.cpp minheap.o hashtable.o
	$(CC) $(C_FLAGS) minheap.o hashtable.o src/doublet.cpp -o doublet

minheap.o: src/minheap.cpp
	$(CC) $(C_FLAGS) -c src/minheap.cpp -o minheap.o

hashtable.o: src/hashtable.cpp
	$(CC) $(C_FLAGS) -c src/hashtable.cpp -o hashtable.o