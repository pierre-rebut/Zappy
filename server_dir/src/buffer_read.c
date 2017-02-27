/*
** read_buffer.c for read_buffer in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir/src
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Fri Jun 10 16:03:54 2016 Pierre Rebut
** Last update Wed Jun 22 17:41:48 2016 Pierre Rebut
*/

#include	<stdlib.h>
#include	<string.h>
#include	<stdbool.h>
#include	"utils.h"
#include	"buffer_cir.h"

void		free_elem(t_buff *buffer, t_cirbuff *elem)
{
  t_cirbuff	*tmp;

  while (buffer->read_buff->next != NULL && buffer->read_buff != elem)
    {
      tmp = buffer->read_buff->next;
      free(buffer->read_buff);
      buffer->read_buff = tmp;
    }
}

static int	check_size_buff(int i, char **msg, char str[])
{
  if (i >= BUFFER_SIZE)
    {
      *msg = my_strcat(*msg, str);
      i = 0;
    }
  return (i);
}

static int	check_read_limit(t_cirbuff **tmp, int u, t_buff *buffer)
{
  if ((*tmp)->read_ptr + u >= (*tmp)->buff + BUFFER_SIZE)
    u = update_cirbuffer(tmp);
  if ((*tmp) == NULL || ((*tmp) == buffer->write_buff &&
			 (*tmp)->read_ptr + u == (*tmp)->write_ptr))
    return (-1);
  return (u);
}

char		*read_buffer(t_buff *buffer, bool test, char *msg, int i)
{
  int		u;
  t_cirbuff	*tmp;
  char		str[BUFFER_SIZE + 1];

  u = 0;
  str[0] = '\0';
  tmp = buffer->read_buff;
  while (test)
    {
      if ((u = check_read_limit(&tmp, u, buffer)) == -1)
	return (NULL);
      if (*(tmp->read_ptr + u) == '\n')
	test = false;
      else
	{
	  i = check_size_buff(i, &msg, str);
	  str[i++] = *(tmp->read_ptr + u);
	  str[i] = '\0';
	}
      u ++;
    }
  tmp->read_ptr += u;
  str[i] = '\0';
  free_elem(buffer, tmp);
  return (my_strcat(msg, str));
}

bool		check_if_msg(t_buff *buffer)
{
  if (buffer->read_buff == buffer->write_buff &&
      buffer->read_buff->read_ptr == buffer->write_buff->write_ptr)
    return (false);
  return (true);
}
