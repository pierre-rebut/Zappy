/*
** add_food.c for add_food in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Fri Jun 17 18:18:37 2016 Pierre Rebut
** Last update Fri Jun 24 18:00:20 2016 Pierre Rebut
*/

#include	<time.h>
#include	<stdlib.h>
#include	"config.h"
#include	"client_display.h"

void		pop_food(t_client *lst, t_config *conf, int nb)
{
  int		x;
  int		y;
  int		i;

  i = 0;
  while (i < nb)
    {
      x = random() % conf->x_map;
      y = random() % conf->y_map;
      add_rock(get_pos_map(conf, x, y), FOOD);
      send_dl_bct(lst, conf, x, y);
      i++;
    }
}

void			random_pop_food(t_config *conf, t_client *lst)
{

  if (lst->lst_player != NULL &&
      check_timeout(conf, &conf->time_food, 300. / (double)conf->u_time))
    {
      pop_food(lst, conf, 1 * lst->connexion);
      conf->time_food.tv_sec = conf->time.tv_sec;
      conf->time_food.tv_usec = conf->time.tv_usec;
    }
}
