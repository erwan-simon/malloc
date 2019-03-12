##
## Makefile for malloc in /home/erwan/Code/teck/PSU_2016_malloc
##
## Made by erwan
## Login   <erwan.simon@epitech.eu>
##
## Started on  Thu Jan 26 14:57:13 2017 erwan
## Last update Sat Feb 11 16:00:52 2017 erwan
##

NAME	= libmy_malloc.so

RM	= rm -f

SRCS	= ./linked_list.c \
	  ./malloc.c \

LIB	= -lmy -L

OBJS	= $(SRCS:.c=.o)

LDFLAGS = -fPIC -g -c -Wall -Wextra -lpthread -D_REENTRANT

LSFLAGS = -shared -Wl

all: $(NAME)

$(NAME):
	gcc $(LDFLAGS) $(SRCS)
	gcc $(LSFLAGS),-soname,$(NAME) -o $(NAME) *.o -lc

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
