SRCS=$(shell find $(PWD) -name \*.cpp)
OBJS=$(SRCS:%.cpp=%.o)

CC=g++
OPT=-O3
CPPFLAGS=-std=c++11 
INCLUDE=/opt/homebrew/Cellar/nlohmann-json/3.10.4/include

TARGET=engine

$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(CPPFLAGS) -I$(INCLUDE)

%.o: %.cpp
	$(CC) -c $< -o $@ $(CPPFLAGS) -I$(INCLUDE)

run:$(TARGET)
	./$(TARGET)