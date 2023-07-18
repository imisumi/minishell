

all:
	@gcc ./src/pipe.c ./src/utils.c

run: all
	@./a.out