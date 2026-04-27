# Variables used by makefile
SRC = src
HEADERS = include
OBJDIR = obj
LIBS = lib

CC=gcc
CFLAGS= -I$(HEADERS) -g -Wall -pedantic -ansi

# Object files used to compile the program and the tests
OBJECTS = $(OBJDIR)/command.o $(OBJDIR)/game_actions.o $(OBJDIR)/game_loop.o $(OBJDIR)/game_reader.o $(OBJDIR)/game.o $(OBJDIR)/graphic_engine.o $(OBJDIR)/object.o $(OBJDIR)/player.o $(OBJDIR)/space.o $(OBJDIR)/set.o $(OBJDIR)/character.o $(OBJDIR)/link.o $(OBJDIR)/inventory.o
TEST_HELPERS = $(OBJDIR)/test.o
TESTS = space_test set_test character_test object_test player_test link_test inventory_test

EXES = castle $(TESTS)

.PHONY: all clean tests doxygen

# The main task
all: $(OBJECTS)
	$(CC) -o castle $(OBJECTS) -L$(LIBS) -lscreen

# Generates the object files defined below
$(OBJDIR)/%.o: $(SRC)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Builds all test executables.
tests: $(TESTS)

space_test: $(OBJDIR)/space_test.o $(OBJDIR)/space.o $(OBJDIR)/set.o $(OBJDIR)/inventory.o $(OBJDIR)/link.o $(TEST_HELPERS)
	$(CC) -o $@ $^

set_test: $(OBJDIR)/set_test.o $(OBJDIR)/set.o $(TEST_HELPERS)
	$(CC) -o $@ $^

character_test: $(OBJDIR)/character_test.o $(OBJDIR)/character.o $(TEST_HELPERS)
	$(CC) -o $@ $^

object_test: $(OBJDIR)/object_test.o $(OBJDIR)/object.o $(TEST_HELPERS)
	$(CC) -o $@ $^

player_test: $(OBJDIR)/player_test.o $(OBJDIR)/player.o $(OBJDIR)/inventory.o $(OBJDIR)/set.o $(TEST_HELPERS)
	$(CC) -o $@ $^

link_test: $(OBJDIR)/link_test.o $(OBJDIR)/link.o $(TEST_HELPERS)
	$(CC) -o $@ $^

inventory_test: $(OBJDIR)/inventory_test.o $(OBJDIR)/inventory.o $(OBJDIR)/set.o $(TEST_HELPERS)
	$(CC) -o $@ $^

# Program objects
$(OBJDIR)/command.o: $(HEADERS)/command.h $(HEADERS)/types.h
$(OBJDIR)/game_actions.o: $(HEADERS)/game_actions.h $(HEADERS)/command.h $(HEADERS)/types.h $(HEADERS)/game.h $(HEADERS)/space.h $(HEADERS)/player.h $(HEADERS)/object.h $(HEADERS)/character.h $(HEADERS)/link.h $(HEADERS)/inventory.h
$(OBJDIR)/game_loop.o: $(HEADERS)/command.h $(HEADERS)/types.h $(HEADERS)/game.h $(HEADERS)/space.h $(HEADERS)/player.h $(HEADERS)/object.h $(HEADERS)/character.h $(HEADERS)/game_actions.h $(HEADERS)/graphic_engine.h $(HEADERS)/link.h $(HEADERS)/inventory.h
$(OBJDIR)/game_reader.o: $(HEADERS)/game_reader.h $(HEADERS)/game.h $(HEADERS)/command.h $(HEADERS)/types.h $(HEADERS)/space.h $(HEADERS)/set.h $(HEADERS)/player.h $(HEADERS)/object.h $(HEADERS)/character.h $(HEADERS)/link.h $(HEADERS)/inventory.h
$(OBJDIR)/game.o: $(HEADERS)/game.h $(HEADERS)/command.h $(HEADERS)/types.h $(HEADERS)/space.h $(HEADERS)/set.h $(HEADERS)/player.h $(HEADERS)/object.h $(HEADERS)/character.h $(HEADERS)/game_reader.h $(HEADERS)/link.h $(HEADERS)/inventory.h
$(OBJDIR)/graphic_engine.o: $(HEADERS)/graphic_engine.h $(HEADERS)/game.h $(HEADERS)/command.h $(HEADERS)/types.h $(HEADERS)/space.h $(HEADERS)/set.h $(HEADERS)/player.h $(HEADERS)/object.h $(HEADERS)/character.h $(HEADERS)/libscreen.h $(HEADERS)/link.h $(HEADERS)/inventory.h
$(OBJDIR)/object.o: $(HEADERS)/object.h $(HEADERS)/types.h
$(OBJDIR)/player.o: $(HEADERS)/player.h $(HEADERS)/inventory.h $(HEADERS)/set.h $(HEADERS)/types.h
$(OBJDIR)/space.o: $(HEADERS)/space.h $(HEADERS)/types.h $(HEADERS)/set.h
$(OBJDIR)/set.o: $(HEADERS)/set.h $(HEADERS)/types.h
$(OBJDIR)/character.o: $(HEADERS)/character.h $(HEADERS)/types.h
$(OBJDIR)/link.o: $(HEADERS)/link.h $(HEADERS)/types.h
$(OBJDIR)/inventory.o: $(HEADERS)/inventory.h $(HEADERS)/set.h $(HEADERS)/types.h
$(OBJDIR)/test.o: $(HEADERS)/test.h

# Test objects
$(OBJDIR)/inventory_test.o: $(HEADERS)/inventory_test.h $(HEADERS)/set.h $(HEADERS)/types.h $(HEADERS)/test.h
$(OBJDIR)/character_test.o: $(HEADERS)/character_test.h $(HEADERS)/character.h $(HEADERS)/types.h $(HEADERS)/test.h
$(OBJDIR)/space_test.o: $(HEADERS)/space_test.h $(HEADERS)/set.h $(HEADERS)/space.h $(HEADERS)/types.h $(HEADERS)/test.h
$(OBJDIR)/set_test.o: $(HEADERS)/set_test.h $(HEADERS)/set.h $(HEADERS)/types.h $(HEADERS)/test.h
$(OBJDIR)/object_test.o: $(HEADERS)/object_test.h $(HEADERS)/object.h $(HEADERS)/types.h $(HEADERS)/test.h
$(OBJDIR)/player_test.o: $(HEADERS)/player_test.h $(HEADERS)/player.h $(HEADERS)/types.h $(HEADERS)/test.h $(HEADERS)/inventory.h
$(OBJDIR)/link_test.o: $(HEADERS)/link_test.h $(HEADERS)/link.h $(HEADERS)/types.h $(HEADERS)/test.h

# Remove all generated files and folders.
clean:
	rm -rf $(OBJDIR) doc $(EXES)

# Generate doxygen docs from the Doxyfile (C3)
doxygen:
	doxygen Doxyfile
