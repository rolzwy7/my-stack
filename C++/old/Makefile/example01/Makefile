CC = g++
CFLAGS = -Wall -Iinclude

SRC = main.cpp tools.cpp
OBJ = $(SRC:.cpp=.o)
CLEAR = del /Q $(OBJ)


all: build clear
	
build: $(OBJ)
	$(CC) $(CFLAGS) -o main.exe $(OBJ)

# Compile objects
main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

tools.o: tools.cpp
	$(CC) $(CFLAGS) -c tools.cpp

clean:
	$(CLEAR)
	
clear:
	$(CLEAR)



