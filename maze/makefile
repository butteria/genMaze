.PHONY: clean

BUILD_DIR = ./build
BIN_DIR = ./bin

TARGET	= $(addprefix $(BIN_DIR)/, maze)
SRCS	= $(wildcard *.c)
OBJS	= $(addprefix $(BUILD_DIR)/, $(patsubst %.c, %.o, $(SRCS)))
INC 	= -I.
CC		= gcc
CFLAG	= -Wall

all: prepare $(TARGET)

#link
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

#compile
$(BUILD_DIR)/%.o: %.c
	$(CC) $(INC) $(CFLAG) -c $< -o $@

prepare:
	if [ ! -d $(BUILD_DIR) ] ; then \
		mkdir -p $(BUILD_DIR); \
	fi
	if [ ! -d $(BIN_DIR) ] ; then \
		mkdir -p $(BIN_DIR); \
	fi

clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET)