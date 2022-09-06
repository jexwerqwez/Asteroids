CC=g++
CFLAGS=-c
# -Wall -Werror -Wextra

all: asteroids

asteroids: asteroids.o aterouds.o
	$(CC) asteroids.o aterouds.o -lcurses -o ./asteroids

aterouds.o: aterouds.cpp
	$(CC) $(CFLAGS) aterouds.cpp
asteroids.o: asteroids.cpp
	$(CC) $(CFLAGS) asteroids.cpp

clean:
	rm -rf *.o ./asteroids
rebuild:
	rm -rf *.o
	make all