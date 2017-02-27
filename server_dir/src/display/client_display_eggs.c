/*
** client_display_eggs.c for eggs in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Tue Jun 21 10:39:21 2016 Pierre Rebut
** Last update Tue Jun 21 14:42:53 2016 Pierre Rebut
*/

#include	"client_display.h"

void		send_dl_enw(t_client *lst, t_player *pl, t_eggs *egg)
{
  t_othercli	*tmp;

  tmp = lst->lst_display;
  while (tmp != NULL)
    {
      send_msg(tmp->buff_out, "enw %d %d %d %d\n", egg->id, pl->fd,
	       egg->position.x, egg->position.y);
      tmp = tmp->next;
    }
}

void		send_dl_eht(t_client *lst, t_eggs *egg)
{
  t_othercli	*tmp;

  tmp = lst->lst_display;
  while (tmp != NULL)
    {
      send_msg(tmp->buff_out, "eht %d\n", egg->id);
      tmp = tmp->next;
    }
}

void		send_dl_edi(t_client *lst, t_eggs *egg)
{
  t_othercli	*tmp;

  tmp = lst->lst_display;
  while (tmp != NULL)
    {
      send_msg(tmp->buff_out, "edi %d\n", egg->id);
      tmp = tmp->next;
    }
}

void		send_dl_ebo(t_client *lst, t_eggs *egg)
{
  t_othercli	*tmp;

  tmp = lst->lst_display;
  while (tmp != NULL)
    {
      send_msg(tmp->buff_out, "ebo %d\n", egg->id);
      tmp = tmp->next;
    }
}

void		send_all_enw(t_othercli *cli, t_client *lst)
{
  t_eggs	*tmp;

  tmp = lst->lst_eggs;
  while (tmp != NULL)
    {
      send_msg(cli->buff_out, "enw %d %d %d %d\n", tmp->id, tmp->creator,
	       tmp->position.x, tmp->position.y);
      tmp = tmp->next;
    }
}
