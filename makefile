CC=g++
CFLAGS=-c
# -Wall -Werror -Wextra

all: asteroids

asteroids: settings.o gun.o asteroids.o spaceship.o game.o field.o main.o
	$(CC) settings.o gun.o asteroids.o spaceship.o game.o field.o main.o -lcurses -o ./asteroids

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
asteroids.o: asteroids.cpp
	$(CC) $(CFLAGS) asteroids.cpp
game.o: game.cpp
	$(CC) $(CFLAGS) game.cpp
field.o: field.cpp
	$(CC) $(CFLAGS) field.cpp
gun.o: gun.cpp
	$(CC) $(CFLAGS) gun.cpp
spaceship.o: gun.cpp
	$(CC) $(CFLAGS) spaceship.cpp
settings.o: settings.cpp
	$(CC) $(CFLAGS) settings.cpp

clean:
	rm -rf *.o ./asteroids
rebuild:
	rm -rf *.o
	make all