/*
** client_display_all3.c for client display in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Wed Jun 15 17:06:51 2016 Pierre Rebut
** Last update Wed Jun 15 17:11:06 2016 Pierre Rebut
*/

#include	<stdlib.h>
#include	"exec_client.h"

void		send_dl_pdr(t_client *cli, t_player *pl, enum e_type val)
{
  t_othercli	*tmp;

  tmp = cli->lst_display;
  while (tmp != NULL)
    {
      send_msg(tmp->buff_out, "pdr %d %d\n", pl->fd, val);
      tmp = tmp->next;
    }
}

void		send_dl_pgt(t_client *cli, t_player *pl, enum e_type val)
{
  t_othercli	*tmp;

  tmp = cli->lst_display;
  while (tmp != NULL)
    {
      send_msg(tmp->buff_out, "pgt %d %d\n", pl->fd, val);
      tmp = tmp->next;
    }
}

void		send_dl_pdi(t_client *cli, t_player *pl)
{
  t_othercli	*tmp;

  tmp = cli->lst_display;
  while (tmp != NULL)
    {
      send_msg(tmp->buff_out, "pdi %d\n", pl->fd);
      tmp = tmp->next;
    }
}

void		send_dl_seg(t_client *cli, char *team)
{
  t_othercli	*tmp;

  tmp = cli->lst_display;
  while (tmp != NULL)
    {
      send_msg(tmp->buff_out, "seg %s\n", team);
      tmp = tmp->next;
    }
}

void		send_dl_smg(t_client *cli, char *msg)
{
  t_othercli	*tmp;

  tmp = cli->lst_display;
  while (tmp != NULL)
    {
      send_msg(tmp->buff_out, "smg %s\n", msg);
      tmp = tmp->next;
    }
}
