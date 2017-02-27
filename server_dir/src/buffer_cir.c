/*
** buffer_cir.c for buffer in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir/src
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Fri Jun 10 14:01:59 2016 Pierre Rebut
** Last update Fri Jun 10 16:04:28 2016 Pierre Rebut
*/

#include	<string.h>
#include	<stdlib.h>
#include	"buffer_cir.h"

t_buff		*init_buffer()
{
  t_buff	*new;
  t_cirbuff	*tmp;

  new = malloc(sizeof(t_buff));
  tmp = malloc(sizeof(t_cirbuff));
  if (new == NULL || tmp == NULL)
    return (NULL);
  new->read_buff = tmp;
  new->write_buff = tmp;
  tmp->next = NULL;
  tmp->read_ptr = tmp->buff;
  tmp->write_ptr = tmp->buff;
  return (new);
}

void		free_buffer(t_buff *buf)
{
  t_cirbuff	*tmp;
  t_cirbuff	*tmp2;

  tmp = buf->read_buff;
  while (tmp != NULL)
    {
      tmp2 = tmp->next;
      free(tmp);
      tmp = tmp2;
    }
  free(buf);
}

static t_cirbuff	*add_elem(t_cirbuff *lst)
{
  t_cirbuff		*new;

  new = malloc(sizeof(t_cirbuff));
  if (new == NULL)
    return (NULL);
  new->read_ptr = new->buff;
  new->write_ptr = new->buff;
  new->next = NULL;
  lst->next = new;
  return (new);
}

int		write_buffer(t_buff *buffer, const char *cmd)
{
  t_cirbuff	*tmp;
  int		i;

  i = 0;
  tmp = buffer->write_buff;
  while (cmd[i] != '\0')
    {
      if (tmp->write_ptr >= tmp->buff + BUFFER_SIZE)
	{
	  tmp = add_elem(tmp);
	  if (tmp == NULL)
	    return (-1);
	}
      *(tmp->write_ptr) = cmd[i];
      tmp->write_ptr ++;
      i++;
    }
  buffer->write_buff = tmp;
  return (i);
}
