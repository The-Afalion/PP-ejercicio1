cmake_minimum_required(VERSION 4.0)
project(seed_src_2026 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(seed_src_2026
        command.c
        command.h
        game.c
        game.h
        game_actions.c
        game_actions.h
        game_loop.c
        game_reader.c
        game_reader.h
        graphic_engine.c
        graphic_engine.h
        libscreen.h
        object.h
        space.c
        space.h
        types.h)
