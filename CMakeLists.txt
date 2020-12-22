cmake_minimum_required(VERSION 3.17)
project(minishell C)

set(CMAKE_C_STANDARD 11)

set(HEADERS
        includes/minishell.h)

add_executable(minishell
        srcs/minishell.c
        srcs/parser.c
        srcs/errors_handler.c)

include_directories(includes)