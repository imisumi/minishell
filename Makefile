# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: imisumi <imisumi@student.42.fr>              +#+                      #
#                                                    +#+                       #
#    Created: 2023/06/28 14:49:09 by rhorbach      #+#    #+#                  #
#    Updated: 2023/11/16 16:32:41 by rhorbach      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell

HEADERDIR = includes
OBJDIR = .obj

CFLAGS = -Wall -Wextra -Werror
CFLAGS += $(if $(DEBUG),-g) $(if $(NORL),-DNO_READLINE=1)
ifdef $(SAN)
CFLAGS += -fsanitize=address,undefined
endif
INCLUDES += -I $(HEADERDIR)
CFLAGS += -Wfatal-errors


GREEN := \033[1;32m
RED := \033[1;31m
BLUE := \033[1;34m
PINK := \033[1;38;5;206m
NC := \033[0m

#########################


FILES = \
	src/signals.c								\
	src/signals2.c								\
	src/exit_code.c								\
	src/main.c									\
	src/error.c									\
	src/free.c									\
	src/free2.c									\
												\
	src/cmd_lst/cmd_lstadd_back.c				\
	src/cmd_lst/cmd_lstadd_front.c				\
	src/cmd_lst/cmd_lstclear.c					\
	src/cmd_lst/cmd_lstdelone.c					\
	src/cmd_lst/cmd_lstlast.c					\
	src/cmd_lst/cmd_lstnew.c					\
	src/cmd_lst/cmd_lstnew_back.c				\
	src/cmd_lst/cmd_lstnew_front.c				\
	src/cmd_lst/cmd_lstsize.c					\
												\
	src/env/env.c								\
	src/env/env_get.c							\
	src/env/env_init.c							\
	src/env/env_set.c							\
												\
	src/redir/redirect_lst/redir_lstadd_back.c	\
	src/redir/redirect_lst/redir_lstadd_front.c	\
	src/redir/redirect_lst/redir_lstclear.c		\
	src/redir/redirect_lst/redir_lstdelone.c	\
	src/redir/redirect_lst/redir_lstlast.c		\
	src/redir/redirect_lst/redir_lstnew.c		\
	src/redir/redirect_lst/redir_lstnew_back.c	\
	src/redir/redirect_lst/redir_lstnew_front.c	\
												\
	src/redir/redir_error.c						\
	src/redir/redir_utils.c						\
												\
	src/heredoc/here_doc.c						\
	src/heredoc/here_doc_utils.c				\
	src/heredoc/here_doc_expand.c				\
												\
	src/tokens/all_whitepace.c					\
	src/tokens/ambiguous_redirect.c				\
	src/tokens/clear_whitespace_tokens.c		\
	src/tokens/complete_tokens.c				\
	src/tokens/expand_token_variable.c			\
	src/tokens/expand_tokens.c					\
	src/tokens/join_word_tokens.c				\
	src/tokens/parser_fill_cmd.c				\
	src/tokens/parser.c							\
	src/tokens/split_tokens.c					\
	src/tokens/tokenize.c						\
	src/tokens/validate_tokens.c				\
	src/tokens/add_token/double_quoted_token.c 	\
	src/tokens/add_token/pipe_token.c 			\
	src/tokens/add_token/redirect_token.c 		\
	src/tokens/add_token/single_quoted_token.c 	\
	src/tokens/add_token/space_token.c			\
	src/tokens/add_token/word_token.c			\
												\
	src/builtins/builtins.c						\
	src/builtins/builtins_1.c					\
	src/builtins/builtins_2.c					\
	src/builtins/builtins_3.c					\
	src/utils.c									\
	src/utils2.c								\
	src/exec/pipex.c 							\
	src/exec/pipex2.c 							\
												\

#########################

OBJFILES = $(addprefix $(OBJDIR)/,$(FILES:c=o))
INCLUDES += $(addprefix -I,$(sort $(dir $(HEADERS))))

#########################

LIBFT = ./libft/libft.a
INCLUDES += -I $(dir $(LIBFT)) -I$(READLINE_DIR)/include # -I makes it so that when a file is included without specifying the header's path it will be searched for in this folder
LFLAGS = -L $(dir $(LIBFT)) -lft
LFLAGS += -L$(READLINE_DIR)/lib -lreadline

#########################

all: $(NAME)
	@echo "$(GREEN)[Completed $(NAME)]$(NC)"

$(NAME): $(LIBFT) $(OBJFILES)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJFILES) $(LFLAGS) -o $(NAME)

$(LIBFT):
	@git submodule update --init --recursive $(dir $(LIBFT))
	@$(MAKE) -C $(dir $(LIBFT))

DEPENDS := $(patsubst %.o,%.d,$(OBJFILES))
-include $(DEPENDS)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)[Compiling $<]$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@
	@printf "\033[1A\033[K"

run: all
	./minishell

clean:
	@rm -rf $(OBJDIR)
	@echo "$(RED)[Deleted $(NAME) objects]$(NC)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)[Deleted $(NAME)]$(NC)"

re: fclean all

relib:
	@$(MAKE) -C libft re

#########################

.PHONY: all run clean fclean re relib
