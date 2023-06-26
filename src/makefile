CC=g++
CFLAGS=-c -g -std=c++20
all: style asteroids

asteroids: settings.o gun.o asteroids.o spaceship.o bonus.o game.o field.o menu.o zone.o fuzzy.o main.o
	$(CC) settings.o gun.o asteroids.o spaceship.o bonus.o game.o field.o menu.o zone.o fuzzy.o main.o -lncursesw -o ./asteroids

zone.o: zone.cpp
	$(CC) $(CFLAGS) zone.cpp
fuzzy.o: fuzzy.cpp
	$(CC) $(CFLAGS) fuzzy.cpp
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
style:
	clang-format -i *.cpp ../includes/*.h
clean:
	rm -rf *.o ./asteroids
rebuild:
	rm -rf *.o
	make all