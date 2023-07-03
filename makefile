SOURCE	:=maze.c
OBJS	:=maze.o
TARGET	:=./libso/libmaze.so

CC		:=gcc

#link
$(TARGET):$(OBJS)
	$(CC) -shared $^ -o $@
#clear
	rm -rf *.o

#compile
$(OBJS):$(SOURCE)
	$(CC) -c -fpic $^ -o $@