# Variables
#Author:Unai
CC=gcc
CFLAGS= -g -Wall -pedantic -ansi -I./include
OBJS = ./obj/command.o ./obj/game_actions.o ./obj/game_loop.o ./obj/game_reader.o ./obj/game.o ./obj/graphic_engine.o ./obj/object.o ./obj/player.o ./obj/space.o ./obj/inventory.o ./obj/character.o ./obj/set.o ./obj/link.o

castle: $(OBJS)
	$(CC) -o castle $(OBJS) -L./lib -lscreen

# Regla generica para compilar y asegurar que el directorio obj exista
./obj/%.o: ./src/%.c
	@mkdir -p ./obj
	$(CC) $(CFLAGS) -c $< -o $@

# Dependencias (opcionales si se manejan solas, pero asi mantenemos tu logica)
./obj/command.o: ./src/command.c ./include/command.h ./include/types.h
./obj/game_actions.o: ./src/game_actions.c ./include/game_actions.h ./include/command.h ./include/types.h ./include/game.h ./include/space.h ./include/player.h ./include/object.h ./include/character.h ./include/set.h
./obj/game_loop.o: ./src/game_loop.c ./include/command.h ./include/types.h ./include/game.h ./include/space.h ./include/player.h ./include/object.h ./include/character.h ./include/game_actions.h ./include/graphic_engine.h ./include/set.h
./obj/game_reader.o: ./src/game_reader.c ./include/game_reader.h ./include/game.h ./include/command.h ./include/types.h ./include/space.h ./include/player.h ./include/object.h ./include/character.h ./include/set.h
./obj/game.o: ./src/game.c ./include/game.h ./include/command.h ./include/types.h ./include/space.h ./include/player.h ./include/object.h ./include/character.h ./include/game_reader.h ./include/set.h
./obj/graphic_engine.o: ./src/graphic_engine.c ./include/graphic_engine.h ./include/game.h ./include/command.h ./include/types.h ./include/space.h ./include/player.h ./include/object.h ./include/character.h ./include/libscreen.h ./include/set.h
./obj/object.o: ./src/object.c ./include/object.h ./include/types.h
./obj/player.o: ./src/player.c ./include/player.h ./include/types.h
./obj/space.o: ./src/space.c ./include/space.h ./include/types.h ./include/set.h
./obj/character.o: ./src/character.c ./include/character.h ./include/types.h
./obj/set.o: ./src/set.c ./include/set.h ./include/types.h
./obj/inventory.o: ./src/inventory.c ./include/inventory.h ./include/types.h ./include/set.h
./obj/link.o: ./src/link.c ./include/link.h ./include/types.h

run:
	./castle castle.dat


.PHONY: doc
doc:
	@mkdir -p ./doc
	@if [ ! -f Doxyfile ]; then doxygen -g; fi
	doxygen


test:
	$(CC) -o space_test ./src/space_test.c ./src/space.c ./src/set.c ./src/link.c $(CFLAGS)
	./space_test
	$(CC) -o set_test ./src/set_test.c ./src/set.c $(CFLAGS)
	./set_test
	$(CC) -o character_test ./src/character_test.c ./src/character.c $(CFLAGS)
	./character_test
	$(CC) -o link_test ./src/link_test.c ./src/link.c $(CFLAGS)
	./link_test
	$(CC) -o inventory_test ./src/inventory_test.c ./src/inventory.c ./src/set.c $(CFLAGS)
	./inventory_test
	$(CC) -o player_test ./src/player_test.c ./src/player.c ./src/set.c ./src/inventory.c $(CFLAGS)
	./player_test

clean:
	rm -rf ./obj/*.o castle space_test set_test character_test link_test inventory_test player_test
