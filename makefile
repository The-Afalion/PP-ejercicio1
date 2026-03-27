# Variables
#Author:Unai
CC=gcc
CFLAGS= -g -Wall -pedantic -ansi -I.
OBJS = command.o game_actions.o game_loop.o game_reader.o game.o graphic_engine.o object.o player.o space.o


# Crea el ejecutable.
# Enlazamos los objetos y al final la librería screen.
# Dejamos que gcc maneje las librerías del sistema implícitamente.
castle: ${OBJS}
	$(CC) -o castle $(OBJS) -L. -lscreen

command.o: command.c command.h types.h
	$(CC) $(CFLAGS) -c command.c

game_actions.o: game_actions.c game_actions.h command.h types.h game.h space.h player.h object.h character.h set.h
	$(CC) $(CFLAGS) -c game_actions.c

game_loop.o: game_loop.c command.h types.h game.h space.h player.h object.h character.h game_actions.h graphic_engine.h set.h
	$(CC) $(CFLAGS) -c game_loop.c

game_reader.o: game_reader.c game_reader.h game.h command.h types.h space.h player.h object.h character.h set.h
	$(CC) $(CFLAGS) -c game_reader.c

game.o: game.c game.h command.h types.h space.h player.h object.h character.h game_reader.h set.h
	$(CC) $(CFLAGS) -c game.c

graphic_engine.o: graphic_engine.c graphic_engine.h game.h command.h types.h space.h player.h object.h character.h libscreen.h set.h
	$(CC) $(CFLAGS) -c graphic_engine.c

object.o: object.c object.h types.h
	$(CC) $(CFLAGS) -c object.c

player.o: player.c player.h types.h
	$(CC) $(CFLAGS) -c player.c

space.o: space.c space.h types.h set.h
	$(CC) $(CFLAGS) -c space.c

character.o: character.c character.h types.h
	$(CC) $(CFLAGS) -c character.c

set.o: set.c set.h types.h
	$(CC) $(CFLAGS) -c set.c

run: 
	./castle castle.dat
#
# Reglas para tests
#
test:
	$(CC) -o space_test space_test.c space.c set.c link.c $(CFLAGS)
	./space_test
	$(CC) -o set_test set_test.c set.c $(CFLAGS)
	./set_test
	$(CC) -o character_test character_test.c character.c $(CFLAGS)
	./character_test
	$(CC) -o link_test link_test.c link.c $(CFLAGS)
	./link_test
	$(CC) -o inventory_test inventory_test.c inventory.c set.c $(CFLAGS)
	./inventory_test
	$(CC) -o player_test player_test.c player.c set.c inventory.c $(CFLAGS)
	./player_test

#Elimina los compilados
clean:
	rm -rf *.o castle space_test set_test character_test link_test inventory_test
