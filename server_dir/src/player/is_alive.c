/*
** is_alive.c for alive in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Fri Jun 24 17:45:50 2016 Pierre Rebut
** Last update Sun Jun 26 16:36:24 2016 Pierre Rebut
*/

#include	<stdlib.h>
#include	"server.h"
#include	"client_display.h"
#include	"client_player.h"

static void	damage_player(t_player *cli, t_config *conf)
{
  if (check_timeout(conf, &(cli->time_life), (double)1 / conf->u_time))
    {
      cli->life --;
      cli->time_life.tv_sec = conf->time.tv_sec;
      cli->time_life.tv_usec = conf->time.tv_usec;
    }
}

static bool	check_life(t_player *cli, t_config *conf,
			   t_client *lst)
{
  t_elemmap	*tmp;

  if (cli->life == 0)
    {
      tmp = cli->inventory;
      while (tmp != NULL && tmp->type != FOOD)
	tmp = tmp->next;
      if (tmp == NULL)
	return (false);
      if (tmp->prev != NULL)
	tmp->prev->next = tmp->next;
      else
	cli->inventory = tmp->next;
      if (tmp->next != NULL)
	tmp->next->prev = tmp->prev;
      free(tmp);
      pop_food(lst, conf, 1);
      cli->life = 126;
      cli->time_life.tv_sec = conf->time.tv_sec;
      cli->time_life.tv_usec = conf->time.tv_usec;
    }
  else
    damage_player(cli, conf);
  return (true);
}

static void	player_dead(t_player *pl, t_client *lst, t_config *conf)
{
  send_last_msg((t_othercli*)pl, (t_othercli**)&lst->lst_player, "mort\n");
  if (pl->prev != NULL)
    pl->prev->next = pl->next;
  else
    lst->lst_player = pl->next;
  if (pl->next != NULL)
    pl->next->prev = pl->prev;
  destroy_player(pl, lst, conf);
}

int		player_is_dead(t_player *cli, t_client *lst,
			       t_config *conf)
{
  if (check_life(cli, conf, lst) == false)
    {
      player_dead(cli, lst, conf);
      return (-1);
    }
  return (0);
}
