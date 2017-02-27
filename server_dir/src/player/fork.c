/*
** fork.c for fork in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Tue Jun 21 10:23:22 2016 Pierre Rebut
** Last update Sun Jun 26 16:20:27 2016 Pierre Rebut
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	"client_display.h"
#include	"client_player.h"

void		cmd_pl_fork_before(t_player *cli, t_client *lst,
				   char **tab, t_config *conf)
{
  (void)tab;
  (void)conf;
  send_dl_pfk(lst, cli);
}

static int	counte_eggs(t_client *lst)
{
  int		i;
  t_eggs	*tmp;

  i = 0;
  tmp = lst->lst_eggs;
  while (tmp != NULL)
    {
      tmp = tmp->next;
      i++;
    }
  return (i);
}

static t_eggs	*create_new_eggs(t_client *lst)
{
  t_eggs	*new;

  new = malloc(sizeof(t_eggs));
  if (new == NULL)
    return (NULL);
  new->next = NULL;
  new->id = counte_eggs(lst) + 1;
  new->prev = lst->lst_eggs;
  if (lst->lst_eggs != NULL)
    lst->lst_eggs->prev = new;
  lst->lst_eggs = new;
  return (new);
}

void		cmd_pl_fork(t_player *cli, t_client *lst,
			    char **tab, t_config *conf)
{
  t_eggs	*new;

  (void)conf;
  (void)tab;
  send_msg(cli->buff_out, "ok\n");
  new = create_new_eggs(lst);
  if (new == NULL)
    return ;
  new->team = cli->team;
  new->position.x = cli->position.x;
  new->position.y = cli->position.y;
  new->eclose = false;
  new->creator = cli->fd;
  send_dl_enw(lst, cli, new);
  new->timeval.tv_sec = conf->time.tv_sec;
  new->timeval.tv_usec = conf->time.tv_usec;
  fprintf(stderr, "[INFO] %d: create new egg => %d\n", cli->fd, new->id);
}
