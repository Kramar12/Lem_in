cmake_minimum_required(VERSION 3.12)
project(Lem_in C)

set(CMAKE_C_STANDARD 99)
set(LIBFT ${CMAKE_SOURCE_DIR}/libft/libft.a)

add_executable(Lem_in main.c lem_in.h get_ways.c trash.c)
target_link_libraries(Lem_in ${LIBFT})
