##
## Makefile for zappy in /home/quief_h/Projets/rendu/PSU_2015_zappy/graph_src
##
## Made by QUIEF Hippolyte
## Login   <quief_h@epitech.net>
##
## Started on  Thu Jun  9 13:50:52 2016 QUIEF Hippolyte
## Last update Sat Jun 11 17:27:44 2016 Pierre Rebut
##

NAME		=	zappy_server

SRC		=	$(shell grep -v ";" sources.mk)

OBJ		=	$(SRC:.c=.o)

INCLUDE		=	-I include/

RM		=	rm -f

CFLAGS		+=	$(INCLUDE)

CLANG		?=	0

DEBUG		?=	0

ifeq ($(CLANG), 1)
	CC	=	clang
	CFLAGS	+=	-Weverything -Wno-padded
else
	CC	=	gcc
	CFLAGS	+=	-W -Wall -Wextra
endif

ifeq ($(DEBUG), 1)
	CFLAGS	+=	-g
endif

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
		cp $(NAME) ../

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME) ../$(NAME)

re:		fclean all

.PHONY:		all clean fclean re
