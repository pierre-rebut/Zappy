##
## Makefile for zappy in /home/quief_h/Projets/rendu/PSU_2015_zappy
##
## Made by QUIEF Hippolyte
## Login   <quief_h@epitech.net>
##
## Started on  Thu Jun  9 13:47:09 2016 QUIEF Hippolyte
## Last update Sun Jun 26 19:19:08 2016 Simon Desplat
##

all:		graph zappy_server zappy_ai

graph:
		$(MAKE) -C graph_dir/

zappy_server:
		$(MAKE) -C server_dir/

zappy_ai:
		@cp ia_dir/script ./zappy_ai
		@chmod 777 zappy_ai

clean:
		$(MAKE) clean -C graph_dir/
		$(MAKE) clean -C server_dir/

fclean:
		$(MAKE) fclean -C graph_dir/
		$(MAKE) fclean -C server_dir/
		rm -rf zappy_ai

re:		zappy_ai
		$(MAKE) re -C graph_dir/
		$(MAKE) re -C server_dir/

.PHONY:		all clean fclean re
