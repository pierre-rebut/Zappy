/*
** send_msg.c for send_msg in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir/src
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Fri Jun 10 16:11:54 2016 Pierre Rebut
** Last update Sun Jun 26 16:45:20 2016 Pierre Rebut
*/

#include	<stdlib.h>
#include	<stdarg.h>
#include	<stdio.h>
#include	<stdbool.h>
#include	<sys/select.h>
#include	"utils.h"
#include	"server.h"
#include	"buffer_cir.h"

int		send_msg(t_buff *buffer, const char *format, ...)
{
  int		len;
  char		*msg;
  va_list	ap;
  va_list	ap_tmp;

  msg = NULL;
  va_start(ap_tmp, format);
  va_copy(ap, ap_tmp);
  len = vsnprintf(NULL, 0, format, ap_tmp);
  va_end(ap_tmp);
  if (len > 0)
    {
      msg = malloc(sizeof(char) * (len + 1));
      if (msg == NULL)
	return (-1);
      vsprintf(msg, format, ap);
      write_buffer(buffer, msg);
      free(msg);
    }
  va_end(ap);
  return (len);
}

int		send_last_msg(t_othercli *cli, t_othercli **lst, char *msg)
{
  int		res;
  fd_set	write_f;

  if (send_msg(cli->buff_out, "%s", msg) == 0)
    return (1);
  if (cli->prev != NULL)
    cli->prev->next = cli->next;
  else
    *lst = cli->next;
  if (cli->next != NULL)
    cli->next->prev = cli->prev;
  FD_ZERO(&write_f);
  FD_SET(cli->fd, &write_f);
  res = select(cli->fd + 1, NULL, &write_f, NULL, NULL);
  if (res == -1)
    return (-1);
  if (FD_ISSET(cli->fd, &write_f))
      write_socket(cli, lst, 0, 0);
  return (0);
}
