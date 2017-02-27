/*
** player_map.c for map in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Fri Jun 17 14:42:19 2016 Pierre Rebut
** Last update Fri Jun 17 15:24:06 2016 Pierre Rebut
*/

#include	"client_player.h"

t_elemmap	*get_objmap(t_elemmap *map, enum e_type value)
{
  while (map != NULL)
    {
      if (map->type == value)
	return (map);
      map = map->next;
    }
  return (NULL);
}

void	move_obj_loot(t_player *cli, t_map *map, t_elemmap *obj)
{
  if (obj->prev != NULL)
    obj->prev->next = obj->next;
  else
    map->obj = obj->next;
  if (obj->next != NULL)
    obj->next->prev = obj->prev;
  obj->prev = NULL;
  obj->next = cli->inventory;
  if (cli->inventory != NULL)
    cli->inventory->prev = obj;
  cli->inventory = obj;
}

void	move_obj_drop(t_player *cli, t_map *map, t_elemmap *obj)
{
  if (obj->prev != NULL)
    obj->prev->next = obj->next;
  else
    cli->inventory = obj->next;
  if (obj->next != NULL)
    obj->next->prev = obj->prev;
  obj->prev = NULL;
  obj->next = map->obj;
  if (map->obj != NULL)
    map->obj->prev = obj;
  map->obj = obj;
}
