/*
** reset_select.c for select in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Sat Jun 11 21:38:41 2016 Pierre Rebut
** Last update Tue Jun 14 17:52:33 2016 Pierre Rebut
*/

#include	<stdlib.h>
#include	<sys/select.h>
#include	"client.h"

static int	reset_sel_dl(t_othercli *cli, int max_fd,
			     fd_set *read_sel, fd_set *write_sel)
{
  if (cli->fd > max_fd)
    max_fd = cli->fd;
  FD_SET(cli->fd, read_sel);
  if (check_if_msg(cli->buff_out) == true)
    FD_SET(cli->fd, write_sel);
  return (max_fd);
}

static int	reset_sel_player(t_player *cli, int max_fd,
				 fd_set *read_sel, fd_set *write_sel)
{
  if (cli->fd > max_fd)
    max_fd = cli->fd;
  FD_SET(cli->fd, read_sel);
  if (check_if_msg(cli->buff_out) == true)
    FD_SET(cli->fd, write_sel);
  return (max_fd);
}

static int	reset_sel_other(t_client *clients, int max_fd,
				fd_set *read_sel, fd_set *write_sel)
{
  t_othercli	*tmp;

  tmp = clients->lst_display;
  while (tmp != NULL)
    {
      max_fd = reset_sel_dl(tmp, max_fd, read_sel, write_sel);
      tmp = tmp->next;
    }
  tmp = clients->lst_tmp;
  while (tmp != NULL)
    {
      max_fd = reset_sel_dl(tmp, max_fd, read_sel, write_sel);
      tmp = tmp->next;
    }
  return (max_fd);
}

int		reset_select(int server, t_client *clients,
			     fd_set *read_sel, fd_set *write_sel)
{
  t_player	*pl;
  int		max_fd;

  max_fd = server;
  FD_ZERO(read_sel);
  FD_ZERO(write_sel);
  FD_SET(server, read_sel);
  pl = clients->lst_player;
  while (pl != NULL)
    {
      max_fd = reset_sel_player(pl, max_fd, read_sel, write_sel);
      pl = pl->next;
    }
  max_fd = reset_sel_other(clients, max_fd, read_sel, write_sel);
  return (max_fd);
}
