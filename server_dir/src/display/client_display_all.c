/*
** client_display_all.c for display in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Wed Jun 15 17:03:25 2016 Pierre Rebut
** Last update Mon Jun 20 17:12:06 2016 Pierre Rebut
*/

#include	<stdlib.h>
#include	"exec_client.h"

void		send_dl_sgt(t_client *cli, t_config *conf)
{
  t_othercli	*tmp;

  tmp = cli->lst_display;
  while (tmp != NULL)
    {
      send_msg(tmp->buff_out, "sgt %d\n", conf->u_time);
      tmp = tmp->next;
    }
}

void		send_dl_bct(t_client *cli, t_config *conf, int x, int y)
{
  t_othercli	*tmp;
  t_map		*map;

  map = get_pos_map(conf, x, y);
  if (map == NULL)
    return ;
  tmp = cli->lst_display;
  while (tmp != NULL)
    {
      send_msg(tmp->buff_out, "bct %d %d %d %d %d %d %d %d %d\n", x, y,
	       compte_pierre(map->obj, FOOD), compte_pierre(map->obj, LIMATE),
	       compte_pierre(map->obj, DERAUMERE),
	       compte_pierre(map->obj, SIBUR),
	       compte_pierre(map->obj, MENDIANE),
	       compte_pierre(map->obj, PHIRAS),
	       compte_pierre(map->obj, THYSTAME));
      tmp = tmp->next;
    }
}

void		send_dl_pnw(t_client *cli, t_player *pl)
{
  t_othercli	*tmp;

  tmp = cli->lst_display;
  while (tmp != NULL)
    {
      send_msg(tmp->buff_out, "pnw %d %d %d %d %d %s\n", pl->fd,
	       pl->position.x, pl->position.y, pl->position.rot,
	       pl->level, pl->team->name);
      tmp = tmp->next;
    }
}

void		send_dl_ppo(t_client *cli, t_player *pl)
{
  t_othercli	*tmp;

  tmp = cli->lst_display;
  while (tmp != NULL)
    {
      send_msg(tmp->buff_out, "ppo %d %d %d %d\n", pl->fd, pl->position.x,
	       pl->position.y, pl->position.rot);
      tmp = tmp->next;
    }
}

void		send_dl_plv(t_client *cli, t_player *pl)
{
  t_othercli	*tmp;

  tmp = cli->lst_display;
  while (tmp != NULL)
    {
      send_msg(tmp->buff_out, "plv %d %d\n", pl->fd, pl->level);
      tmp = tmp->next;
    }
}
