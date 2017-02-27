##
## Makefile for zappy in /home/quief_h/Projets/rendu/PSU_2015_zappy/graph_src
##
## Made by QUIEF Hippolyte
## Login   <quief_h@epitech.net>
##
## Started on  Thu Jun  9 13:50:52 2016 QUIEF Hippolyte
## Last update Fri Jun 24 17:42:43 2016 QUIEF Hippolyte
##

NAME		=	zappy_graph

SRC		= 	$(shell grep -v ";" sources.mk)

OBJ		=	$(SRC:.cpp=.o)

INCLUDE		=	-I include/

LIB		=	-lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system -lpthread

RM		=	rm -f

CLANG		?=	0

DEBUG		?=	0

ifeq ($(CLANG), 1)
	CXX		=	clang++
	CXXFLAGS	+=	-Weverything -Wno-padded
else
	CXX		=	g++
	CXXFLAGS	+=	-W -Wall -Wextra
endif

ifeq ($(DEBUG), 1)
	CXXFLAGS	+=	-g
endif

	CXXFLAGS	+=	$(INCLUDE) -std=c++11

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CXX) $(CXXFLAGS) $(CFLAGS) $(OBJ) $(LIB) -o $(NAME)
		cp $(NAME) ../

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME) ../$(NAME)

re:		fclean all

.PHONY:		all clean fclean re
