##
## Makefile for Makefile in /home/chen_c/rendu/AUSP_strace
## 
## Made by Billy CHEN
## Login   <chen_c@epitech.net>
## 
## Started on  Sun May  4 17:54:16 2014 Billy CHEN
## Last update Sun May 18 19:53:04 2014 eliot bardet
##

NAME = strace

SRC = 	main.c\
	syscall_tab.c\
	signal.c\
	tracee.c\
	check_and_print.c\
	print.c\

OBJ = $(SRC:.c=.o)

CC	=	gcc

CFLAGS	+=	-Wall -Werror -pedantic -ansi

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
