

all:
	@gcc ./src/pipe.c ./src/utils.c ./src/commands.c

run: all
	@gcc ./src/pipe.c ./src/utils.c ./src/commands.c && ./a.out