/*
** client_display_all2.c for client in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Wed Jun 15 17:06:05 2016 Pierre Rebut
** Last update Tue Jun 21 15:38:35 2016 Pierre Rebut
*/

#include	<stdlib.h>
#include	"exec_client.h"
#include	"map.h"

void		send_dl_pin(t_client *cli, t_player *pl)
{
  t_othercli	*tmp;

  tmp = cli->lst_display;
  while (tmp != NULL)
    {
      send_msg(tmp->buff_out, "pin %d %d %d %d %d %d %d %d %d %d\n", pl->fd,
	       pl->position.x, pl->position.y,
	       compte_pierre(pl->inventory, FOOD),
	       compte_pierre(pl->inventory, LIMATE),
	       compte_pierre(pl->inventory, DERAUMERE),
	       compte_pierre(pl->inventory, SIBUR),
	       compte_pierre(pl->inventory, MENDIANE),
	       compte_pierre(pl->inventory, PHIRAS),
	       compte_pierre(pl->inventory, THYSTAME));
      tmp = tmp->next;
    }
}

void		send_dl_pex(t_client *cli, t_player *pl)
{
  t_othercli	*tmp;

  tmp = cli->lst_display;
  while (tmp != NULL)
    {
      send_msg(tmp->buff_out, "pex %d\n", pl->fd);
      tmp = tmp->next;
    }
}

void		send_dl_pbc(t_client *cli, t_player *pl, char *msg)
{
  t_othercli	*tmp;

  tmp = cli->lst_display;
  while (tmp != NULL)
    {
      send_msg(tmp->buff_out, "pbc %d %s\n", pl->fd, msg);
      tmp = tmp->next;
    }
}

void		send_dl_pie(t_client *cli, int x, int y, int res)
{
  t_othercli	*tmp;

  tmp = cli->lst_display;
  while (tmp != NULL)
    {
      send_msg(tmp->buff_out, "pie %d %d %d\n", x, y, res);
      tmp = tmp->next;
    }
}

void		send_dl_pfk(t_client *cli, t_player *pl)
{
  t_othercli	*tmp;

  tmp = cli->lst_display;
  while (tmp != NULL)
    {
      send_msg(tmp->buff_out, "pfk %d\n", pl->fd);
      tmp = tmp->next;
    }
}
