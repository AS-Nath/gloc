CXX = g++
CC = gcc

CXXFLAGS = -Wall -Wextra -std=c++17 -I../include
CFLAGS   = -Wall -Wextra -I../include

SRC_CPP = ../src/main.cpp \
          ../src/indexer.cpp \
          ../src/search.cpp \
          ../src/tokeniser.cpp \
          ../src/docmap.cpp

SRC_C = ../src/storage.c

OBJ = $(SRC_CPP:.cpp=.o) $(SRC_C:.c=.o)

BIN = ../gloc

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(OBJ) -o $(BIN)

../src/%.o: ../src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

../src/%.o: ../src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f ../src/*.o $(BIN)
