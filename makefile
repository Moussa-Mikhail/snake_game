CC=g++
CFLAGS=-c -g -O0 -std=c++11 -Wall
LDFLAGS=-static -static-libstdc++ -static-libgcc
SOURCES=main.cpp display.cpp snake_game.cpp snake_game_objects.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=snake

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	del -f $(EXECUTABLE).exe $(OBJECTS)