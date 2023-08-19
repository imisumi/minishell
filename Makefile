# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/28 00:51:40 by ichiro            #+#    #+#              #
#    Updated: 2023/08/19 15:26:58 by imisumi-wsl      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME = minishell

# CFLAGS = -g -Iinclude
# LFLAGS = -lreadline

# OBJ_DIR = .obj

# SRC_DIR = srcs

# LIBFT = lib/libft/libft.a

# cc = gcc

# SRC = ./srcs/main.c

# OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

# GREEN := \033[1;32m
# RED := \033[1;31m
# BLUE := \033[1;34m
# PINK := \033[1;38;5;206m
# NC := \033[0m


# $(NAME): $(LIBFT) $(OBJ)
# 	@$(cc) $(CFLAGS) $(INC) -o $(NAME) $^ $(LFLAGS)

# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
# 	@mkdir -p $(OBJ_DIR)
# 	@$(cc) $(CFLAGS) $(LIBFT) $(INC) -c $< -o $@

# # Uncomment the following lines if you need to build the libft library
# # $(NAME): $(LIBFT)
# # 	@$(cc) $(CFLAGS) $(INC) -o $(NAME) $^ $(LFLAGS)
# #
# $(LIBFT):
# 	@$(MAKE) -C lib/libft

# all: $(NAME)
# 	@echo "$(GREEN)[Completed]$(NC)"

# run: all
# 	@./$(NAME)

# clean:
# 	@rm -rf $(OBJ_DIR)

# fclean: clean
# 	@rm -f $(NAME)
	
# relib:
# 	@$(MAKE) -C lib/libft re

# re: fclean all


# NAME = minishell

# all:
# 	@gcc ./srcs/main.c ./lib/libft/libft.a && ./a.out

# CFLAGS = -Wall -Werror -Wextra

LIBFT = lib/libft/libft.a

ENV_DIR = ./src/env/
SRC_DIR = ./src/
BUILTIN_DIR = ./src/builtins/

SRC =	$(SRC_DIR)main.c \
		$(SRC_DIR)utils.c \
		$(SRC_DIR)commands.c \
		$(SRC_DIR)redir_utils.c \
		$(SRC_DIR)cmd_list.c \
		$(SRC_DIR)redir_list.c \
		$(ENV_DIR)env.c \
		$(BUILTIN_DIR)builtin.c \

all:
	@gcc $(SRC) $(LIBFT) -lreadline

run:
	@gcc $(CFLAGS) $(SRC) $(LIBFT) -lreadline && ./a.out

relib:
	@$(MAKE) -C lib/libft re

clean:
	@rm -rf a.out


