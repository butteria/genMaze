.PHONY: clean

TARGET	= ascii
SRCS	= $(wildcard *.c)
OBJS	= $(patsubst %.c, %.o, $(SRCS))
INC 	= -I.
CC		= gcc
CFLAG	= -Wall

$(TARGET):$(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

#compile
$(OBJ): $(SRC)
	gcc -c $(SRC) $(INC) -o $(OBJ)

clean:
	rm -rf *.o $(TARGET)