/*
** socket_rdwr.c for socket in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Sat Jun 11 16:50:16 2016 Pierre Rebut
** Last update Fri Jun 24 18:48:29 2016 Pierre Rebut
*/

#include	<sys/socket.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	"client.h"

int		read_socket(t_othercli *cli, t_othercli **lst)
{
  int		len;
  char		tmp[BUFFER_SIZE + 1];

  len = recv(cli->fd, tmp, BUFFER_SIZE, 0);
  if (len > 0)
    {
      tmp[len] = '\0';
      write_buffer(cli->buff_in, tmp);
      return (0);
    }
  if (cli->prev != NULL)
    cli->prev->next = cli->next;
  else
    *lst = cli->next;
  if (cli->next != NULL)
    cli->next->prev = cli->prev;
  return (1);
}

int	update_cirbuffer(t_cirbuff **tmp)
{
  *tmp = (*tmp)->next;
  return (0);
}

static int	send_socket(t_othercli *cli, t_othercli **lst,
			    int i, char *msg)
{
  if (i > 0)
    {
      i = send(cli->fd, msg, i, 0);
      if (i < 0)
	{
	  if (cli->prev != NULL)
	    cli->prev->next = cli->next;
	  else
	    *lst = cli->next;
	  if (cli->next != NULL)
	    cli->next->prev = cli->prev;
	  return (1);
	}
    }
  return (0);
}

int		write_socket(t_othercli *cli, t_othercli **lst, int i, int u)
{
  t_cirbuff	*tmp;
  char		msg[BUFFER_SIZE + 1];
  bool		test;

  test = true;
  tmp = cli->buff_out->read_buff;
  while (i < BUFFER_SIZE && test == true)
    {
      if (tmp->read_ptr + u >= tmp->buff + BUFFER_SIZE)
	u = update_cirbuffer(&tmp);
      if (tmp == NULL || (tmp == cli->buff_out->write_buff &&
			  tmp->read_ptr + u == tmp->write_ptr))
	test = false;
      else
	{
	  msg[i] = *(tmp->read_ptr + u);
	  i++;
	  u++;
	}
    }
  if (tmp != NULL)
    tmp->read_ptr += u;
  free_elem(cli->buff_out, tmp);
  return (send_socket(cli, lst, i, msg));
}

