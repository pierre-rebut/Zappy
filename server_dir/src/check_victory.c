/*
** check_victory.c for victory in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Wed Jun 22 11:46:38 2016 Pierre Rebut
** Last update Wed Jun 22 16:19:38 2016 Pierre Rebut
*/

#include	<stdio.h>
#include	<sys/select.h>
#include	"client_display.h"
#include	"server.h"

static int	reset_sel_display(t_client *lst, fd_set *write_sel)
{
  int		max_fd;
  t_othercli	*tmp;

  max_fd = 0;
  FD_ZERO(write_sel);
  tmp = lst->lst_display;
  while (tmp != NULL)
    {
      FD_SET(tmp->fd, write_sel);
      if (max_fd < tmp->fd)
	max_fd = tmp->fd;
      tmp = tmp->next;
    }
  return (max_fd);
}

int		send_victory(t_client *lst, t_config *conf, int server)
{
  int		res;
  fd_set	write_sel;
  t_othercli	*tmp;

  fprintf(stderr, "[INFO] La team %s est vainqueur\n", conf->victory->name);
  send_dl_seg(lst, conf->victory->name);
  res = reset_sel_display(lst, &write_sel);
  if (res <= 0)
    return (-1);
  res = select(res + 1, NULL, &write_sel, NULL, NULL);
  tmp = lst->lst_display;
  while (tmp != NULL)
    {
      if (res != -1 && FD_ISSET(tmp->fd, &write_sel))
	if (write_socket(tmp, &lst->lst_display, 0, 0) != 0)
	  destroy_othercli(tmp, lst);
      tmp = tmp->next;
    }
  close_socket(server, lst);
  return (0);
}

void		check_defeat(t_client *lst, t_config *conf)
{
  t_player	*pl;
  int		i;
  int		nb;

  i = 0;
  while (conf->team[i] != NULL)
    {
      if (conf->team[i]->player == 0)
	{
	  nb = 0;
	  pl = lst->lst_player;
	  while (pl != NULL)
	    {
	      if (pl->team == conf->team[i])
		nb ++;
	      pl = pl->next;
	    }
	  if (nb == 0)
	    {
	      fprintf(stderr, "[INFO] %s: DEFEAT\n", conf->team[i]->name);
	      conf->team[i]->player = conf->nb_players;
	    }
	}
      i++;
    }
}

void		check_victory(t_client *lst, t_config *conf)
{
  t_player	*pl;
  int		i;
  int		nb;

  i = 0;
  while (conf->team[i] != NULL)
    {
      nb = 0;
      pl = lst->lst_player;
      while (pl != NULL)
	{
	  if (pl->team == conf->team[i] && pl->level == 8)
	    nb ++;
	  pl = pl->next;
	}
      if (nb >= 6)
	{
	  conf->victory = conf->team[i];
	  return ;
	}
      i++;
    }
}
