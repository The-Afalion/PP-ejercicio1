# Variables
CC=gcc
CFLAGS= -g -Wall -pedantic -ansi
OBJS = command.o game_actions.o game_loop.o game_reader.o game.o graphic_engine.o object.o player.o space.o

# Crea el ejecutable.
castle: ${OBJS}
	gcc -o castle $(OBJS) -lscreen -L.

command.o: command.c command.h types.h
	$(CC) $(CFLAGS) -c command.c

game_actions.o: game_actions.c game_actions.h command.h types.h game.h space.h player.h object.h
	$(CC) $(CFLAGS) -c game_actions.c

game_loop.o: game_loop.c command.h types.h game.h space.h player.h object.h game_actions.h graphic_engine.h
	$(CC) $(CFLAGS) -c game_loop.c

game_reader.o: game_reader.c game_reader.h game.h command.h types.h space.h player.h object.h
	$(CC) $(CFLAGS) -c game_reader.c

game.o: game.c game.h command.h types.h space.h player.h object.h game_reader.h
	$(CC) $(CFLAGS) -c game.c

graphic_engine.o: graphic_engine.c graphic_engine.h game.h command.h types.h space.h player.h object.h libscreen.h
	$(CC) $(CFLAGS) -c graphic_engine.c

object.o: object.c object.h types.h
	$(CC) $(CFLAGS) -c object.c

player.o: player.c player.h types.h
	$(CC) $(CFLAGS) -c player.c

space.o: space.c space.h types.h
	$(CC) $(CFLAGS) -c space.c
#Elimina los compilados
clean:
	rm -rf *.o castle