CC=g++
CFLAGS=-c
# -Wall -Werror -Wextra

all: asteroids

asteroids: settings.o gun.o asteroids.o spaceship.o bonus.o game.o field.o menu.o main.o
	$(CC) settings.o gun.o asteroids.o spaceship.o bonus.o game.o field.o menu.o main.o -lncursesw -o ./asteroids

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
bonus.o: bonus.cpp
	$(CC) $(CFLAGS) bonus.cpp
settings.o: settings.cpp
	$(CC) $(CFLAGS) settings.cpp
menu.o: menu.cpp
	$(CC) $(CFLAGS) menu.cpp

clean:
	rm -rf *.o ./asteroids
rebuild:
	rm -rf *.o
	make all