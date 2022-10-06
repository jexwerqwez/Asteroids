CC=g++
CFLAGS=-c
# -Wall -Werror -Wextra

all: asteroids

asteroids: asteroids.o other.o aterouds.o
	$(CC) asteroids.o other.o aterouds.o -lcurses -o ./asteroids

aterouds.o: aterouds.cpp
	$(CC) $(CFLAGS) aterouds.cpp
asteroids.o: asteroids.cpp
	$(CC) $(CFLAGS) asteroids.cpp
other.o: other.cpp
	$(CC) $(CFLAGS) other.cpp

clean:
	rm -rf *.o ./asteroids
rebuild:
	rm -rf *.o
	make all