/*
** map.c for map in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Sat Jun 11 21:47:33 2016 Pierre Rebut
** Last update Sun Jun 26 16:32:43 2016 Pierre Rebut
*/

#include	<stdlib.h>

#include	"config.h"

void		init_map(t_config *conf)
{
  int		i;

  i = 0;
  conf->map = malloc(sizeof(t_map) * conf->x_map * conf->y_map);
  if (conf->map == NULL)
    return ;
  while (i < conf->x_map * conf->y_map)
    {
      conf->map[i].x = i % conf->x_map;
      conf->map[i].y = i / conf->x_map;
      conf->map[i].obj = NULL;
      i++;
    }
}

void		free_map(t_map *map)
{
  t_elemmap	*tmp;

  while (map->obj != NULL)
    {
      tmp = map->obj->next;
	free(map->obj);
      map->obj = tmp;
    }
  free(map);
}

t_map		*get_pos_map(t_config *conf, int x, int y)
{
  int		i;

  if (x >= conf->x_map || y >= conf->y_map)
    return (NULL);
  i = y * conf->x_map + x;
  return (&(conf->map[i]));
}
