/*
** move_player.c for player in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir/src/player
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Thu Jun 16 16:26:42 2016 Pierre Rebut
** Last update Fri Jun 24 14:48:15 2016 ikkar
*/

#include	"client_display.h"
#include	"client_player.h"

t_elemmap	*get_player_pos(t_config *conf, t_player *pl)
{
  t_elemmap		*obj;
  t_map			*map;

  map = get_pos_map(conf, pl->position.x, pl->position.y);
  if (map == NULL)
    return (NULL);
  obj = get_objmap(map->obj, PLAYER);
  if (obj == NULL)
    return (NULL);
  if (obj->prev != NULL)
    obj->prev->next = obj->next;
  else
    map->obj = obj->next;
  if (obj->next != NULL)
    obj->next->prev = obj->prev;
  return (obj);
}

void	move_player_pos(t_config *conf, t_player *pl, t_elemmap *obj)
{
  t_map		*map;

  if (obj == NULL)
    return ;
  map = get_pos_map(conf, pl->position.x, pl->position.y);
  if (map == NULL)
    return ;
  obj->prev = NULL;
  obj->next = map->obj;
  if (map->obj != NULL)
    map->obj->prev = obj;
  map->obj = obj;
}

void		cmd_pl_avance(t_player *cli, t_client *lst,
			      char **tab, t_config *conf)
{
  (void)tab;
  move_player(cli, lst, conf, cli->position.rot);
  send_msg(cli->buff_out, "ok\n");
}

void		cmd_pl_droite(t_player *cli, t_client *lst,
			      char **tab, t_config *conf)
{
  (void)tab;
  (void)conf;
  cli->position.rot += 1;
  if (cli->position.rot > 4)
    cli->position.rot = 1;
  send_dl_ppo(lst, cli);
  send_msg(cli->buff_out, "ok\n");
}

void		cmd_pl_gauche(t_player *cli, t_client *lst,
			      char **tab, t_config *conf)
{
  (void)tab;
  (void)conf;
  cli->position.rot = cli->position.rot - 1;
  if (cli->position.rot <= 0)
    cli->position.rot = 4;
  send_dl_ppo(lst, cli);
  send_msg(cli->buff_out, "ok\n");
}
