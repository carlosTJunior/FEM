OBJS = test.c LinearAlgebra.c

OBJ_NAME = prog

CC = gcc

LIBS = -W -Wall -pedantic -ansi

compile: $(OBJS)
	$(CC) -o $(OBJ_NAME) $(OBJS) $(LIBS)

run: $(OBJ_NAME)
	./$(OBJ_NAME)
