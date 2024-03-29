CC=g++
CFLAGS=-c -g -O0 -std=c++17 -Wall -pthread
LDFLAGS=-static -static-libstdc++ -static-libgcc
SOURCES=main.cpp snake_game_objects.cpp snake_game_model.cpp terminal_display.cpp key_poller.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=snake

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLE).exe $(OBJECTS)

build-clean: clean $(EXECUTABLE)