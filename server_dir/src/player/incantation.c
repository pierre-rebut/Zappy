/*
** incantation.c for incantation in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Fri Jun 17 17:38:50 2016 Pierre Rebut
** Last update Fri Jun 24 15:02:28 2016 ikkar
*/

#include	<stdbool.h>
#include	"client_display.h"
#include	"client_player.h"
#include	"check_victory.h"

static const t_incantation	g_incant[] = {
  { 2, 1, 1, 0, 0, 0, 0, 0 },
  { 3, 2, 1, 1, 1, 0, 0, 0 },
  { 4, 2, 2, 0, 1, 0, 2, 0 },
  { 5, 4, 1, 1, 2, 0, 1, 0 },
  { 6, 4, 1, 2, 1, 3, 0, 0 },
  { 7, 6, 1, 2, 3, 0, 1, 0 },
  { 8, 6, 2, 2, 2, 2, 2, 1 }
};

static int	count_incant_level(t_client *lst, t_player *pl)
{
  int		i;
  t_player	*tmp;

  i = 0;
  tmp = lst->lst_player;
  while (tmp != NULL)
    {
      if (tmp->position.x == pl->position.x &&
	  tmp->position.y == pl->position.y &&
	  tmp->level == pl->level)
	{
	  i++;
	}
      tmp = tmp->next;
    }
  return (i);
}

bool		check_incant(t_player *pl, t_config *conf, t_client *lst)
{
  int		i;
  t_map		*map;

  i = 0;
  map = get_pos_map(conf, pl->position.x, pl->position.y);
  if (map == NULL)
    return (false);
  while (i < 7)
    {
      if (pl->level + 1 == g_incant[i].elevate)
	{
	  if (count_incant_level(lst, pl) == g_incant[i].player &&
	      compte_pierre(map->obj, LIMATE) >= g_incant[i].line &&
	      compte_pierre(map->obj, DERAUMERE) >= g_incant[i].derau &&
	      compte_pierre(map->obj, SIBUR) >= g_incant[i].sibur &&
	      compte_pierre(map->obj, MENDIANE) >= g_incant[i].mendiane &&
	      compte_pierre(map->obj, PHIRAS) >= g_incant[i].phiras &&
	      compte_pierre(map->obj, THYSTAME) >= g_incant[i].thys)
	    return (true);
	  else
	    return (false);
	}
      i++;
    }
  return (false);
}

void		delete_type_rock(t_map *map, enum e_type type, int lim)
{
  t_elemmap	*tmp;
  t_elemmap	*rm;
  int		i;

  i = 0;
  tmp = map->obj;
  while (tmp != NULL && i < lim)
    {
      if (tmp->type == type)
	{
	  if (tmp->prev != NULL)
	    tmp->prev->next = tmp->next;
	  else
	    map->obj = tmp->next;
	  if (tmp->next != NULL)
	    tmp->next->prev = tmp->prev;
	  rm = tmp->next;
	  free(tmp);
	  tmp = rm;
	  i++;
	}
      else
	tmp = tmp->next;
    }
}

void		delete_incant_rock(t_player *pl, t_config *conf)
{
  int		i;
  t_map		*map;

  i = 0;
  map = get_pos_map(conf, pl->position.x, pl->position.y);
  if (map == NULL)
    return ;
  while (i < 7)
    {
      if (pl->level == g_incant[i].elevate)
	{
	  delete_type_rock(map, LIMATE, g_incant[i].line);
	  delete_type_rock(map, DERAUMERE, g_incant[i].derau);
	  delete_type_rock(map, SIBUR, g_incant[i].sibur);
	  delete_type_rock(map, MENDIANE, g_incant[i].mendiane);
	  delete_type_rock(map, PHIRAS, g_incant[i].phiras);
	  delete_type_rock(map, THYSTAME, g_incant[i].thys);
	  return ;
	}
      i++;
    }
}
