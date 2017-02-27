/*
** client_display_send.c for send in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Wed Jun 15 17:07:47 2016 Pierre Rebut
** Last update Fri Jun 17 15:15:45 2016 Pierre Rebut
*/

#include	<stdlib.h>
#include	"exec_client.h"

void		send_msz(t_othercli *cli, t_config *conf)
{
  send_msg(cli->buff_out, "msz %d %d\n", conf->x_map, conf->y_map);
}

void		send_bct(t_othercli *cli, t_config *conf, int x, int y)
{
  t_map		*map;

  map = get_pos_map(conf, x, y);
  if (map != NULL)
    {
      send_msg(cli->buff_out, "bct %d %d %d %d %d %d %d %d %d\n", x, y,
	       compte_pierre(map->obj, FOOD), compte_pierre(map->obj, LIMATE),
	       compte_pierre(map->obj, DERAUMERE),
	       compte_pierre(map->obj, SIBUR),
	       compte_pierre(map->obj, MENDIANE),
	       compte_pierre(map->obj, PHIRAS),
	       compte_pierre(map->obj, THYSTAME));
    }
  else
    send_msg(cli->buff_out, "sbp\n");
}

void		send_all_bct(t_othercli *cli, t_config *conf)
{
  int		i;
  t_map		*map;

  i = 0;
  while (i < conf->x_map * conf->y_map)
    {
      map = &(conf->map[i]);
      send_msg(cli->buff_out, "bct %d %d %d %d %d %d %d %d %d\n",
	       i % conf->x_map, i / conf->x_map,
	       compte_pierre(map->obj, FOOD), compte_pierre(map->obj, LIMATE),
	       compte_pierre(map->obj, DERAUMERE),
	       compte_pierre(map->obj, SIBUR),
	       compte_pierre(map->obj, MENDIANE),
	       compte_pierre(map->obj, PHIRAS),
	       compte_pierre(map->obj, THYSTAME));
      i++;
    }
}

void		send_tna(t_othercli *cli, t_config *conf)
{
  int		i;

  i = 0;
  while (conf->team[i] != NULL)
    {
      send_msg(cli->buff_out, "tna %s\n", conf->team[i]->name);
      i++;
    }
}

void		send_all_pnw(t_othercli *cli, t_client *lst)
{
  t_player	*tmp;

  tmp = lst->lst_player;
  while (tmp != NULL)
    {
      send_msg(cli->buff_out, "pnw %d %d %d %d %d %s\n", tmp->fd,
	       tmp->position.x, tmp->position.y, tmp->position.rot,
	       tmp->level, tmp->team->name);
      tmp = tmp->next;
    }
}
