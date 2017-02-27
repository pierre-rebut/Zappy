/*
** exec_client.c for exec_client in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Tue Jun 14 16:48:55 2016 Pierre Rebut
** Last update Sat Jun 25 16:43:50 2016 Pierre Rebut
*/

#include	<time.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	"exec_client.h"
#include	"server.h"
#include	"client_display.h"

void		exec_all_player(t_client *clients, t_config *conf,
				fd_set *read_sel, fd_set *write_sel)
{
  int		val;
  t_player	*tmp;
  t_player	*rm;

  tmp = clients->lst_player;
  while (tmp != NULL)
    {
      val = 0;
      rm = tmp->next;
      if (FD_ISSET(tmp->fd, read_sel))
	val = read_socket((t_othercli*)tmp, (t_othercli**)&clients->lst_player);
      if (val == 0)
	{
	  if (check_if_msg(tmp->buff_out) &&
	      FD_ISSET(tmp->fd, write_sel))
	    val = write_socket((t_othercli*)tmp,
			       (t_othercli**)&clients->lst_player, 0, 0);
	  if (val == 0)
	    exec_player(tmp, clients, conf);
	}
      if (val != 0)
	destroy_player(tmp, clients, conf);
      tmp = rm;
    }
}

void		exec_all_display(t_client *clients, t_config *conf,
				fd_set *read_sel, fd_set *write_sel)
{
  int		val;
  t_othercli	*tmp;
  t_othercli	*rm;

  tmp = clients->lst_display;
  while (tmp != NULL)
    {
      val = 0;
      rm = tmp->next;
      if (FD_ISSET(tmp->fd, read_sel))
	val = read_socket(tmp, &clients->lst_display);
      if (val == 0)
	{
	  if (check_if_msg(tmp->buff_out) &&
	      FD_ISSET(tmp->fd, write_sel))
	    val = write_socket(tmp, &clients->lst_display, 0, 0);
	  if (val == 0)
	    exec_display(tmp, clients, conf);
	}
      if (val != 0)
	destroy_othercli(tmp, clients);
      tmp = rm;
    }
}

void		exec_all_other(t_client *clients, t_config *conf,
				fd_set *read_sel, fd_set *write_sel)
{
  int		val;
  t_othercli	*tmp;
  t_othercli	*rm;

  tmp = clients->lst_tmp;
  while (tmp != NULL)
    {
      val = 0;
      rm = tmp->next;
      if (FD_ISSET(tmp->fd, read_sel))
	val = read_socket(tmp, &clients->lst_tmp);
      if (val == 0)
	{
	  if (check_if_msg(tmp->buff_out) &&
	      FD_ISSET(tmp->fd, write_sel))
	    val = write_socket(tmp, &clients->lst_tmp, 0, 0);
	  if (val == 0)
	    exec_other(tmp, clients, conf, 0);
	}
      if (val != 0)
	destroy_othercli(tmp, clients);
      tmp = rm;
    }
}

void		exec_all_eggs(t_client *clients, t_eggs *tmp, t_config *conf)
{
  while (tmp != NULL)
    {
      if (tmp->eclose == false &&
	  check_timeout(conf, &(tmp->timeval), (double)600 / conf->u_time))
	{
	  tmp->eclose = true;
	  tmp->team->player ++;
	  send_dl_eht(clients, tmp);
	  fprintf(stderr, "[INFO] %d: egg eclose\n", tmp->id);
	}
      tmp = tmp->next;
    }
}
