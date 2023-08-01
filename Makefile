

all:
	@gcc ./src/pipe.c ./src/utils.c ./src/env.c ./src/commands.c

run:
	@gcc ./src/pipe.c ./src/utils.c ./src/env.c ./src/commands.c \
		./src/redir_utils.c ./src/builtin.c ./lib/libft/libft.a -lreadline \
		&& ./a.out

clean:
	@rm -rf a.out