OBJS = test.c LinearAlgebra.c FiniteDifferences.c

OBJ_NAME = prog

CC = gcc

LIBS = -W -Wall -pedantic -ansi -lm

compile: $(OBJS)
	$(CC) -o $(OBJ_NAME) $(OBJS) $(LIBS)

run: $(OBJ_NAME)
	./$(OBJ_NAME)
