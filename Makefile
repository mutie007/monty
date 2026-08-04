CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu89

SRC = main.c interpreter.c opcodes.c free_stack.c
OBJ = $(SRC:.c=.o)

all: monty

monty: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o monty

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f monty

re: fclean all

.PHONY: all clean fclean re
