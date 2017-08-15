cmake_minimum_required(VERSION 3.6)
project(21sh)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra")

set(SOURCE_FILES
        src/main.c
        src/add_del_char.c
        src/right_left_arrows.c
        src/up_down_arrows.c
        src/read_line.c
        src/split_line.c
        src/split_commands.c
        src/execute.c
        src/errors.c
        src/access.c
        src/env_info.c
        src/ft_cd.c
        src/ft_echo.c
        src/ft_help.c
        src/ft_setenv.c
        src/ft_unsetenv.c
        src/parse_dollar.c
        src/env_to_arr.c
        src/parse_quotes.c
        src/set_terminal.c
        src/prompt.c)# sources

include_directories(
        includes
        libft_printf/includes
        libft_printf/libft/includes
) # headers

link_directories(
        libft_printf
) # libraries

add_executable(21sh ${SOURCE_FILES}) # compilation

target_link_libraries(21sh -lftprintf -ltermcap) # linkage