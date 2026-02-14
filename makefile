# Variables
CC = gcc
CFLAGS = -Wall -pedantic -ansi -g
LIBS = -lscreen -L.
OBJETOS = command.o game_actions.o game_loop.o game_reader.o game.o graphic_engine.o object.o player.o space.o

# Regla principal
all: castle

# Enlazado del ejecutable
castle: $(OBJETOS)
	$(CC) -o $@ $(OBJETOS) $(LIBS)

# Se compilan los modulos

command.o: command.c command.h types.h
	$(CC) $(CFLAGS) -c $<

game_actions.o: game_actions.c game_actions.h command.h game.h types.h
	$(CC) $(CFLAGS) -c $<

game_loop.o: game_loop.c command.h game.h game_actions.h graphic_engine.h
	$(CC) $(CFLAGS) -c $<

game_reader.o: game_reader.c game_reader.h game.h types.h
	$(CC) $(CFLAGS) -c $<

game.o: game.c game.h game_reader.h command.h space.h player.h object.h types.h
	$(CC) $(CFLAGS) -c $<

graphic_engine.o: graphic_engine.c graphic_engine.h command.h libscreen.h space.h types.h game.h
	$(CC) $(CFLAGS) -c $<

object.o: object.c object.h types.h
	$(CC) $(CFLAGS) -c $<

player.o: player.c player.h types.h
	$(CC) $(CFLAGS) -c $<

space.o: space.c space.h types.h
	$(CC) $(CFLAGS) -c $<

# Limpieza de archivos 
.PHONY: clean
clean:
	rm -f $(OBJETOS) castle