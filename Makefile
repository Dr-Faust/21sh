# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: opodolia <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/20 16:00:27 by opodolia          #+#    #+#              #
#    Updated: 2017/09/14 20:22:25 by opodolia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh
NAME_BASE = 21sh

# compiler
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

# directories
SH_SRC_DIR = ./srcs/
SH_OBJ_DIR = ./objs/
SH_INC_DIR = ./includes/

# 21sh source files
SH_FILES += main.c
SH_FILES += terminal_settings/set_terminal.c
SH_FILES += prompt/prompt.c
SH_FILES += line_reader/read_line.c \
			line_reader/parse_keys.c
SH_FILES += line_editing/add_del_char.c
SH_FILES += cursor_movement/up_down_arrows.c \
			cursor_movement/right_left_arrows.c \
			cursor_movement/extended_move_left.c
SH_FILES += parser/parse_quotes.c \
			parser/parse_dollar.c \
			parser/split_line.c \
			parser/split_commands.c
SH_FILES += execution/execute.c \
			execution/access.c
SH_FILES += history/manage_history.c \
			history/navigate_history.c
SH_FILES += builtins/ft_cd.c \
			builtins/ft_echo.c \
			builtins/ft_help.c \
			builtins/ft_setenv.c \
			builtins/ft_unsetenv.c
SH_FILES += environment/env_info.c \
			environment/env_to_arr.c
SH_FILES += signals/signals.c
SH_FILES += errors/errors.c

SH_SRCS_DIRS = terminal_settings/ prompt/ line_reader/ line_editing/ \
			   cursor_movement/ parser/ execution/ history/ builtins/ \
			   environment/ signals/ errors/

SH_OBJS_DIRS = $(addprefix $(SH_OBJ_DIR), $(SH_SRCS_DIRS))
SH_OBJ = $(addprefix $(SH_OBJ_DIR), $(OBJ_NAME))

OBJ_NAME = $(SH_FILES:.c=.o)

# libftprintf
LIB_DIR = ./libft_printf/
LIB = $(addprefix $(LIB_DIR), libftprintf.a)
LIB_INC = -I ./libft_printf
LIB_LNK = -L ./libft_printf -lftprintf -lncurses

.SILENT:

all: $(LIB) $(NAME)
	echo "\033[38;5;44m☑️  ALL    $(NAME_BASE) is done\033[0m\033[K"

$(SH_OBJ_DIR)%.o: $(SH_SRC_DIR)%.c
	printf "\r\033[38;5;11m⌛  MAKE $(NAME_BASE) please wait ...\033[0m\033[K"
	mkdir -p $(SH_OBJ_DIR) $(SH_OBJS_DIRS)
	$(CC) $(CFLAGS) $(LIB_INC) -I $(SH_INC_DIR) -o $@ -c $<

$(LIB):
	make -C $(LIB_DIR)

$(NAME): $(SH_OBJ)
	$(CC) $(SH_OBJ) -ltermcap $(LIB_LNK) -lm -o $(NAME)
	echo -en "\r\033[38;5;22m☑️  MAKE $(NAME_BASE)\033[0m\033[K"
	echo "\r\033[38;5;184m👥  GROUP MEMBER(S):\033[0m\033[K"
	echo "\r\033[38;5;15m`cat author | sed s/^/\ \ \ \ /g`\033[0m\033[K 🇺🇦"

clean:
	printf "\r\033[38;5;11m⌛  CLEAN  $(NAME_BASE) please wait ...\033[0m\033[K"
	rm -rf $(SH_OBJ_DIR)
	make -C $(LIB_DIR) clean
	printf "\r\033[38;5;11m☑️  CLEAN  $(NAME_BASE) is done\033[0m\033[K"

fclean: clean
	printf "\r\033[38;5;11m⌛  FCLEAN $(NAME_BASE) please wait ...\033[0m\033[K"
	rm -f $(NAME)
	make -C $(LIB_DIR) fclean
	printf "\r\033[38;5;11m☑️  FCLEAN  $(NAME_BASE) is done\033[0m\033[K"

re: fclean all

.PHONY: fclean clean re
