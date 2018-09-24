CC = gcc
CFLAGS = -std=gnu11 -W -Werror -Wall
INCLUDE = -I/usr/include/SDL2/
LDFLAGS = -L/usr/lib/x86_64-linux-gnu/libSDL2.a
LDLIBS = -lSDL2 -lSDL2_image -lSDL2main
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = game

rainbow:
	$(CC) $(CFLAGS) $(INCLUDE) $(SOURCES) -c 

cupcake: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LDFLAGS) $(LDLIBS) -o $(EXECUTABLE)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

clean:
	rm -Rf *.o $(EXECUTABLE)
