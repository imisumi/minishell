# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/28 00:51:40 by ichiro            #+#    #+#              #
#    Updated: 2023/08/15 12:09:14 by imisumi          ###   ########.fr        #
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


all:
	@gcc $(if $(DEBUG), -g -fsanitize=address) ./src/main.c ./src/utils.c ./src/env.c ./src/commands.c \
		./src/redir_utils.c ./src/builtin.c ./lib/libft/libft.a -lreadline

run:
	@gcc ./src/main.c ./src/utils.c ./src/env.c ./src/commands.c \
		./src/redir_utils.c ./src/builtin.c ./src/cmd_list.c ./src/redir_list.c \
		./lib/libft/libft.a -lreadline \
		&& ./a.out

clean:
	@rm -rf a.out


