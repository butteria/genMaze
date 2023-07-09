.PHONY: clean

TARGET	 = maze
SOURCE	 = $(wildcard *.c)
OBJS 	 = $(patsubst %.c, %.o, $(SOURCE))
INC 	 = -I.

$(TARGET):$(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

#compile
$(OBJ): $(SRC)
	gcc -c $(SRC) $(INC) -o $(OBJ)

clean:
	rm -rf *.o  $(TARGET)