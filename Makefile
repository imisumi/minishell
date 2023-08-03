

all:
	@gcc $(if $(DEBUG), -g -fsanitize=address) ./src/pipe.c ./src/utils.c ./src/env.c ./src/commands.c \
		./src/redir_utils.c ./src/builtin.c ./lib/libft/libft.a -lreadline

run:
	@gcc ./src/pipe.c ./src/utils.c ./src/env.c ./src/commands.c \
		./src/redir_utils.c ./src/builtin.c ./lib/libft/libft.a -lreadline \
		&& ./a.out

clean:
	@rm -rf a.out