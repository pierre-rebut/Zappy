/*
** broadcast.c for zappy in /home/ikkar/SYSTEM_UNIX/PSU_2015_zappy/server_dir
** 
** Made by ikkar
** Login   <ikkar@epitech.net>
** 
** Started on  Wed Jun 22 16:07:35 2016 ikkar
** Last update Sun Jun 26 16:43:00 2016 Pierre Rebut
*/

#include	"broadcast.h"
#include	"client_display.h"
#include	"client_player.h"

void		get_x_neg(t_player *cli, t_config *conf, t_player *tmp, t_way *way)
{
  int		i;

  way->x_neg = 0;
  if (cli->position.x < tmp->position.x)
    {
      i = 1;
      while (cli->position.x - i > -1)
	{
	  i++;
	  way->x_neg++;
	}
      way->x_neg += ABS(conf->x_map - tmp->position.x);
      way->positif_x = false;
    }
  else
    {
      i = 1;
      while (cli->position.x + i < (conf->x_map + 1))
	{
	  i++;
	  way->x_neg++;
	}
      way->x_neg += ABS(0 - tmp->position.x);
      way->positif_x = true;
    }
}

void		get_y_neg(t_player *cli, t_config *conf, t_player *tmp, t_way *way)
{
  int		i;

  way->y_neg = 0;
  if (cli->position.y < tmp->position.y)
    {
      i = 1;
      while (cli->position.y - i > -1)
	{
	  i++;
	  way->y_neg++;
	}
      way->y_neg += ABS(conf->y_map - tmp->position.y);
      way->positif_y = false;
    }
  else
    {
      i = 1;
      while (cli->position.y + i < conf->y_map + 1)
	{
	  i++;
	  way->y_neg++;
	}
      way->y_neg += ABS(0 - tmp->position.y);
      way->positif_y = true;
    }
}

void		all_pos(t_player *cli, t_player *tmp, char *str)
{
  if (cli->position.x > tmp->position.x)
    {
      if (cli->position.y > tmp->position.y)
	send_broadcast(tmp, str, 6);
      else
	send_broadcast(tmp, str, 8);
    }
  else
    {
      if (cli->position.y > tmp->position.y)
	send_broadcast(tmp, str, 4);
      else
	send_broadcast(tmp, str, 2);
    }
}

void		is_min(t_way way, t_player *cli, t_player *tmp, char *msg)
{
  if (way.x_neg == 0 || way.x_pos == 0)
    x_null(way, cli, tmp, msg);
  else if (way.y_neg == 0 || way.y_pos == 0)
    y_null(way, cli, tmp, msg);
  else if (way.x_neg < way.x_pos && way.y_neg < way.y_pos)
    all_neg(cli, tmp, msg);
  else if (way.x_neg > way.x_pos && way.y_neg > way.y_pos)
    all_pos(cli, tmp, msg);
  else if (way.x_neg < way.x_pos && way.y_neg > way.y_pos)
    y_neg(cli, tmp, msg);
  else
    x_neg(cli, tmp, msg);
}

void		cmd_pl_broad(t_player *cli, t_client *lst,
			     char **tab, t_config *conf)
{
  t_player	*tmp;
  t_way		way;

  tmp = lst->lst_player;
  send_dl_pbc(lst, cli, tab[1]);
  while (tmp != NULL)
    {
      if (tmp != cli)
	{
	  get_x_neg(cli, conf, tmp, &way);
	  way.x_pos = ABS(tmp->position.x - cli->position.x);
	  get_y_neg(cli, conf, tmp, &way);
	  way.y_pos = ABS(tmp->position.y - cli->position.y);
	  is_min(way, cli, tmp, tab[1]);
	}
      tmp = tmp->next;
    }
  send_msg(cli->buff_out, "ok\n");
}
