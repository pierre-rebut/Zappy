/*
** display_incantation.c for incantation in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Sat Jun 18 15:24:24 2016 Pierre Rebut
** Last update Tue Jun 21 15:24:42 2016 Pierre Rebut
*/

#include	"utils.h"
#include	"server.h"
#include	"client_display.h"

void		send_dl_pic(t_client *lst, t_player *pl, int nb)
{
  t_othercli	*tmp;

  tmp = lst->lst_display;
  while (tmp != NULL)
    {
      if (nb == -1)
	send_msg(tmp->buff_out, "\n");
      else if (nb == -2)
	send_msg(tmp->buff_out, "pic %d %d %d %d", pl->position.x,
		 pl->position.y, pl->level, pl->fd);
      else
	send_msg(tmp->buff_out, " %d", pl->fd);
      tmp = tmp->next;
    }
}
