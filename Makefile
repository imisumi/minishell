

all:
	@gcc ./src/pipe.c ./src/utils.c ./src/env.c ./src/commands.c

run:
	@gcc ./src/pipe.c ./src/utils.c ./src/env.c ./src/commands.c ./lib/libft/libft.a && ./a.out