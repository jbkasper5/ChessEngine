SRCS=$(shell find $(PWD) -name \*.c)
OBJS=$(SRCS:%.c=%.o)

CC=gcc
OPT=-O3
CFLAGS=-std=c11 
INCLUDE=/opt/homebrew/Cellar/nlohmann-json/3.10.4/include

TARGET=engine

$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(CFLAGS) -I$(INCLUDE)

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS) -I$(INCLUDE)

run:$(TARGET)
	./$(TARGET) 

.PHONY: clean
clean:
	$(RM) -rf $(TARGET)
	$(RM) -rf $(OBJS)
