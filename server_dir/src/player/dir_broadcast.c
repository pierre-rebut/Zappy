/*
** dir_broadcast.c for zappy in /home/ikkar/SYSTEM_UNIX/PSU_2015_zappy/server_dir
** 
** Made by ikkar
** Login   <ikkar@epitech.net>
** 
** Started on  Fri Jun 24 14:18:45 2016 ikkar
** Last update Sun Jun 26 16:42:29 2016 Pierre Rebut
*/

#include	"broadcast.h"
#include	"client_display.h"
#include	"client_player.h"

void		all_neg(t_player *cli, t_player *tmp, char *str)
{
  if (cli->position.x > tmp->position.x)
    {
      if (cli->position.y > tmp->position.y)
	send_broadcast(tmp, str, 2);
      else
	send_broadcast(tmp, str, 4);
    }
  else
    {
      if (cli->position.y > tmp->position.y)
	send_broadcast(tmp, str, 8);
      else
	send_broadcast(tmp, str, 6);
    }
}

void		x_neg(t_player *cli, t_player *tmp, char *str)
{
  if (cli->position.x > tmp->position.x)
    {
      if (cli->position.y > tmp->position.y)
	send_broadcast(tmp, str, 4);
      else
	send_broadcast(tmp, str, 2);
    }
  else
    {
      if (cli->position.y > tmp->position.y)
	send_broadcast(tmp, str, 6);
      else
	send_broadcast(tmp, str, 8);
    }
}

void		y_neg(t_player *cli, t_player *tmp, char *str)
{
  if (cli->position.x > tmp->position.x)
    {
      if (cli->position.y > tmp->position.y)
	send_broadcast(tmp, str, 8);
      else
	send_broadcast(tmp, str, 6);
    }
  else
    {
      if (cli->position.y > tmp->position.y)
	send_broadcast(tmp, str, 2);
      else
	send_broadcast(tmp, str, 4);
    }
}

void		x_null(t_way way, t_player *cli, t_player *tmp, char *str)
{
  if (way.y_neg == 0 || way.y_pos == 0)
    send_broadcast(tmp, str, 0);
  else if (way.y_neg < way.y_pos)
    {
      if (cli->position.y > tmp->position.y)
	send_broadcast(tmp, str, 1);
      else
	send_broadcast(tmp, str, 5);
    }
  else
    {
      if (cli->position.y > tmp->position.y)
	send_broadcast(tmp, str, 5);
      else
	send_broadcast(tmp, str, 1);
    }
}

void		y_null(t_way way, t_player *cli, t_player *tmp, char *str)
{
  if (way.x_neg == 0 || way.x_pos == 0)
    send_broadcast(tmp, str, 0);
  else if (way.x_neg < way.x_pos)
    {
      if (cli->position.x > tmp->position.x)
	send_broadcast(tmp, str, 3);
      else
	send_broadcast(tmp, str, 7);
    }
  else
    {
      if (cli->position.x > tmp->position.x)
	send_broadcast(tmp, str, 7);
      else
	send_broadcast(tmp, str, 3);
    }
}
