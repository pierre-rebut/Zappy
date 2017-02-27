/*
** exec_cmd_pl.c for pl in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir/src/display
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Wed Jun 15 17:51:48 2016 Pierre Rebut
** Last update Fri Jun 24 17:24:28 2016 Pierre Rebut
*/

#include	<stdlib.h>
#include	"client_display.h"

static t_player	*get_player_by_id(t_client *lst, int id)
{
  t_player	*tmp;

  tmp = lst->lst_player;
  while (tmp != NULL)
    {
      if (tmp->fd == id)
	return (tmp);
      tmp = tmp->next;
    }
  return (NULL);
}

void		cmd_ppo(t_othercli *cli, t_client *lst,
			char **tab, t_config *conf)
{
  t_player	*pl;
  int		value;

  (void)conf;
  value = atoi(tab[1]);
  if (value <= 0)
    send_msg(cli->buff_out, "sbp\n");
  else
    {
      pl = get_player_by_id(lst, value);
      if (pl == NULL)
	send_msg(cli->buff_out, "sbp\n");
      else
	send_msg(cli->buff_out, "ppo %d %d %d %d\n", pl->fd, pl->position.x,
		 pl->position.y, pl->position.rot);
    }
}

void		cmd_plv(t_othercli *cli, t_client *lst,
			char **tab, t_config *conf)
{
  t_player	*pl;
  int		value;

  (void)conf;
  value = atoi(tab[1]);
  if (value <= 0)
    send_msg(cli->buff_out, "sbp\n");
  else
    {
      pl = get_player_by_id(lst, value);
      if (pl == NULL)
	send_msg(cli->buff_out, "sbp\n");
      else
	send_msg(cli->buff_out, "plv %d %d\n", pl->fd, pl->level);
    }
}

void		cmd_pin(t_othercli *cli, t_client *lst,
			char **tab, t_config *conf)
{
  t_player	*pl;
  int		value;

  (void)conf;
  value = atoi(tab[1]);
  if (value <= 0)
    send_msg(cli->buff_out, "sbp\n");
  else
    {
      pl = get_player_by_id(lst, value);
      if (pl == NULL)
	send_msg(cli->buff_out, "sbp\n");
      else
	send_msg(cli->buff_out, "pin %d %d %d %d %d %d %d %d %d %d\n", pl->fd,
		 pl->position.x, pl->position.y,
		 compte_pierre(pl->inventory, FOOD),
		 compte_pierre(pl->inventory, LIMATE),
		 compte_pierre(pl->inventory, DERAUMERE),
		 compte_pierre(pl->inventory, SIBUR),
		 compte_pierre(pl->inventory, MENDIANE),
		 compte_pierre(pl->inventory, PHIRAS),
		 compte_pierre(pl->inventory, THYSTAME));
    }
}
