/*
** delete_rock.c for zappy in /home/ikkar/SYSTEM_UNIX/PSU_2015_zappy/server_dir
** 
** Made by ikkar
** Login   <ikkar@epitech.net>
** 
** Started on  Fri Jun 24 14:53:12 2016 ikkar
** Last update Sat Jun 25 16:46:52 2016 Pierre Rebut
*/

#include	<stdbool.h>
#include	"client_display.h"
#include	"client_player.h"
#include	"check_victory.h"

void		cmd_pl_incant_before(t_player *pl, t_client *lst,
				     char **tab, t_config *conf)
{
  t_player	*tmp;

  (void)tab;
  if (check_incant(pl, conf, lst) == false)
    {
      send_msg(pl->buff_out, "ko\n");
      pl->exec.fct = NULL;
    }
  else
    {
      send_msg(pl->buff_out, "elevation en cours\n");
      tmp = lst->lst_player;
      send_dl_pic(lst, pl, -2);
      while (tmp != NULL)
	{
	  if (tmp != pl && tmp->position.x == pl->position.x &&
	      tmp->position.y == pl->position.y &&
	      tmp->level == pl->level)
	    send_dl_pic(lst, tmp, 0);
	  tmp = tmp->next;
	}
      send_dl_pic(lst, pl, -1);
    }
}

static void	update_incant_level(t_client *lst, t_player *pl)
{
  t_player	*tmp;

  tmp = lst->lst_player;
  while (tmp != NULL)
    {
      if (tmp != pl && tmp->position.x == pl->position.x &&
	  tmp->position.y == pl->position.y &&
	  tmp->level + 1 == pl->level)
	{
	  tmp->level ++;
	  send_msg(tmp->buff_out, "niveau actuel : %d\n", tmp->level);
	  send_dl_plv(lst, tmp);
	}
      tmp = tmp->next;
    }
}

void		cmd_pl_incant(t_player *pl, t_client *lst,
			      char **tab, t_config *conf)
{
  (void)tab;
  if (check_incant(pl, conf, lst) == false)
    {
      send_msg(pl->buff_out, "ko\n");
      send_dl_pie(lst, pl->position.x, pl->position.y, 0);
      return ;
    }
  pl->level ++;
  delete_incant_rock(pl, conf);
  send_dl_pie(lst, pl->position.x, pl->position.y, 1);
  send_msg(pl->buff_out, "niveau actuel : %d\n", pl->level);
  send_dl_plv(lst, pl);
  update_incant_level(lst, pl);
  pop_rocks(conf, 1);
  send_dl_bct(lst, conf, pl->position.x, pl->position.y);
  check_victory(lst, conf);
}
