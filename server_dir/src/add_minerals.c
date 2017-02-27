/*
** add_minerals.c for zappy in /home/ikkar/SYSTEM_UNIX/PSU_2015_zappy/server_dir
** 
** Made by ikkar
** Login   <ikkar@epitech.net>
** 
** Started on  Wed Jun 15 14:36:08 2016 ikkar
** Last update Wed Jun 15 16:07:01 2016 Pierre Rebut
*/

#include	<stdlib.h>

#include	"config.h"

static		t_rock g_rock[] =
  {
    {LIMATE, LIM},
    {DERAUMERE, DER},
    {SIBUR, SIB},
    {MENDIANE, MEN},
    {PHIRAS, PHI},
    {THYSTAME, THY},
    {DEFAULT, -1}
  };

void		init_rock(int mult)
{
  int		i;

  i = 0;
  while (g_rock[i].type != DEFAULT)
    {
      g_rock[i].rock *= mult;
      i++;
    }
}

void		reset_rock(int mult)
{
  int		i;

  i = 0;
  while (g_rock[i].type != DEFAULT)
    {
      g_rock[i].rock /= mult;
      i++;
    }
}

int		count_rock()
{
  int		i;

  i = 0;
  while (g_rock[i].type != DEFAULT)
    {
      if (g_rock[i].rock > 0)
	{
	  g_rock[i].rock--;
	  return (g_rock[i].type);
	}
      i++;
    }
  return (g_rock[i].type);
}

void		add_rock(t_map *map, enum e_type type)
{
  t_elemmap	*elem;

  if ((elem = malloc(sizeof(t_elemmap))) == NULL)
    return ;
  elem->prev = NULL;
  elem->next = map->obj;
  if (map->obj != NULL)
    map->obj->prev = elem;
  map->obj = elem;
  elem->type = type;
}

void		pop_rocks(t_config *conf, int mult)
{
  enum e_type	type;
  int		x;
  int		y;

  init_rock(mult);
  while ((type = count_rock()) != DEFAULT)
    {
      x = random() % conf->x_map;
      y = random() % conf->y_map;
      add_rock(get_pos_map(conf, x, y), type);
    }
  reset_rock(mult);
}
