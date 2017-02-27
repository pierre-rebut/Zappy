/*
** exec_display.c for exec_display in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Tue Jun 14 17:36:02 2016 Pierre Rebut
** Last update Fri Jun 24 17:46:49 2016 Pierre Rebut
*/

#include	<time.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	"exec_client.h"
#include	"client_player.h"
#include	"client_display.h"
#include	"wordtab.h"

static const t_clientpl_cmd g_cmd[] =
  {
    { "avance", 1, 7, &cmd_pl_avance, NULL },
    { "droite", 1, 7, &cmd_pl_droite, NULL },
    { "gauche", 1, 7, &cmd_pl_gauche, NULL },
    { "voir", 1, 7, &cmd_pl_voir, NULL },
    { "inventaire", 1, 7, &cmd_pl_invent, NULL },
    { "prend", 2, 7, &cmd_pl_prend, NULL},
    { "pose", 2, 7, &cmd_pl_pose, NULL },
    { "expulse", 1, 7, &cmd_pl_expulse, NULL },
    { "broadcast", 2, 7, &cmd_pl_broad, NULL },
    { "incantation", 1, 300, &cmd_pl_incant, &cmd_pl_incant_before },
    { "fork", 1, 42, &cmd_pl_fork, &cmd_pl_fork_before },
    { "connect_nbr", 1, 0, &cmd_pl_connect, NULL },
    { NULL }
  };

static void		do_cmd(t_player *cli, t_client *lst,
			       t_config *conf, char **tab)
{
  int			i;

  i = 0;
  while (g_cmd[i].cmd != NULL)
    {
      if (strcasecmp(g_cmd[i].cmd, tab[0]) == 0)
	{
	  if (len_wordtab(tab) == g_cmd[i].param)
	    {
	      if (g_cmd[i].fct_before != NULL)
		(*(g_cmd[i].fct_before))(cli, lst, tab, conf);
	      cli->exec.fct = g_cmd[i].fct;
	      cli->exec.limit = g_cmd[i].time / conf->u_time;
	      cli->exec.param = tab;
	      cli->exec.start.tv_sec = conf->time.tv_sec;
	      cli->exec.start.tv_usec = conf->time.tv_usec;
	    }
	  else
	    send_msg(cli->buff_out, "ko\n");
	  return ;
	}
      i++;
    }
  send_msg(cli->buff_out, "ko\n");
}

static void	exec_player_fct(t_player *pl, t_client *lst,
				t_config *conf)
{
  if (check_timeout(conf, &(pl->exec.start), pl->exec.limit))
    {
      (*(pl->exec.fct))(pl, lst, pl->exec.param, conf);
      free_wordtab(pl->exec.param);
      pl->exec.fct = NULL;
    }
}

static int	update_broadcast(char **tab, char *str)
{
  int		i;

  i = 1;
  if (strlen(str) <= strlen("broadcast ") || len_wordtab(tab) < 2)
    return (-1);
  while (tab[i] != NULL)
    free(tab[i++]);
  tab[1] = strdup(str + strlen("broadcast "));
  tab[2] = NULL;
  return (0);
}

int		exec_player(t_player *cli, t_client *lst,
			    t_config *conf)
{
  char		*str;
  char		**tab;

  if (player_is_dead(cli, lst, conf) == -1)
    return (-1);
  if (cli->exec.fct == NULL)
    {
      str = read_buffer(cli->buff_in, true, NULL, 0);
      if (str != NULL)
	{
	  tab = my_wordtab(str, 0, 0);
	  if (tab != NULL && tab[0] != NULL)
	    {
	      if (strcasecmp(tab[0], "broadcast") == 0)
		update_broadcast(tab, str);
	      fprintf(stderr, "[PLAYER] %d: %s\n", cli->fd, str);
	      do_cmd(cli, lst, conf, tab);
	    }
	  free(str);
	}
    }
  else
    exec_player_fct(cli, lst, conf);
  return (0);
}
