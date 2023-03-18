##
## EPITECH PROJECT, 2020
## makefile
## File description:
## Makefile
##

CFLAGS 			:=  --std=gnu99 -Wextra -Wall -g3 -O2
CPPFLAGS		:= 	-I ./inc

CC 				:= gcc

ifneq (,$(shell command -v ccache))
	CC := ccache gcc
endif

SRC			:=	$(shell find src/ -name "*.c" -type f)
OBJ			:=	$(SRC:.c=.o)
NAME		:=	myftp

VGFLAGS := --leak-check=full --trace-children=yes --quiet --track-origins=yes

all:	 $(NAME)

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(OBJ)

tests:
	make
	./tests/test_ftp.sh 127.0.0.1 4248

valgrind:
	@make
	valgrind $(VGFLAGS) ./$(NAME) -s echo lala
	@make clean

clean:
	rm -f $(OBJ) $(OBJ) *.gcno *.gcda

fclean: clean
	rm -f $(NAME) $(NAME)

re: fclean all

.PHONY: clean fclean re all valgrind tests
