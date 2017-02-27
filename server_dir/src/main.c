/*
** main.c for PSU_2015_zappy in /home/quief_h/Projets/rendu/PSU_2015_zappy
**
** Made by Hippolyte Quief
** Login   <quief_h@epitech.net>
**
** Started on  Thu Jun 09 13:40:05 2016 Hippolyte Quief
** Last update Sun Jun 26 16:51:30 2016 Pierre Rebut
*/

#include	<stdlib.h>
#include	<stdbool.h>
#include	<string.h>
#include	<stdio.h>
#include	<signal.h>
#include	<sys/select.h>
#include	<time.h>

#include	"client_display.h"
#include	"client.h"
#include	"server.h"
#include	"get_param.h"
#include	"map.h"
#include	"check_victory.h"

static int	g_server = -1;
static t_client	*g_client = NULL;

int		server_loop(t_config *conf,
			    fd_set *read_sel, fd_set *write_sel)
{
  int		max_fd;
  int		res;

  while (42)
    {
      max_fd = reset_select(g_server, g_client, read_sel, write_sel);
      if (max_fd <= 0)
	return (-1);
      res = select(max_fd + 1, read_sel, write_sel, NULL, &(conf->timeout));
      set_timeout_value(conf);
      if (res != -1 && FD_ISSET(g_server, read_sel))
	new_client(g_server, g_client);
      if (res != -1)
	{
	  if (conf->victory != NULL)
	    return (send_victory(g_client, conf, g_server));
	  random_pop_food(conf, g_client);
	  exec_all_eggs(g_client, g_client->lst_eggs, conf);
	  exec_all_player(g_client, conf, read_sel, write_sel);
	  exec_all_display(g_client, conf, read_sel, write_sel);
	  exec_all_other(g_client, conf, read_sel, write_sel);
	}
    }
}

void		sig_exit(int error)
{
  fprintf(stderr, "[INFO] Exit server (signal: %d)\n", error);
  close_socket(g_server, g_client);
  exit(error);
}

static t_client		*init_lst_client(t_config *conf)
{
  int			i;
  t_client		*new;

  new = malloc(sizeof(t_client));
  if (new == NULL)
    return (NULL);
  new->connexion = 0;
  new->lst_eggs = NULL;
  new->lst_player = NULL;
  new->lst_display = NULL;
  new->lst_tmp = NULL;
  i = 0;
  while (conf->team[i] != NULL)
    {
      conf->team[i]->player = conf->nb_players;
      i++;
    }
  return (new);
}

void			start_server(t_config *conf)
{
  fd_set		read_sel;
  fd_set		write_sel;

  g_server = init_socket(conf->port);
  g_client = init_lst_client(conf);
  conf->victory = NULL;
  init_map(conf);
  pop_rocks(conf, count_tab(conf->team));
  if (g_server <= 0 || g_client == NULL || conf->map == NULL)
    error_socket(g_server);
  else
    {
      fprintf(stderr, "Start listening on port %d\n", conf->port);
      fprintf(stderr, "Config: Max(%d) WorldX(%d) WorldY(%d) T(%d)\n",
	      conf->nb_players, conf->x_map, conf->y_map, conf->u_time);
      aff_team(conf->team, conf->nb_players);
      fprintf(stderr, "Generating wolrd... [done]\n");
      signal(SIGINT, sig_exit);
      signal(SIGTERM, sig_exit);
      server_loop(conf, &read_sel, &write_sel);
    }
}

int		main(int ac, char **av)
{
  int		i;
  t_config	conf;

  if (ac > 2)
    {
      init_config(&conf);
      i = 0;
      while (++i < ac)
	if ((i = check_param(av, &conf, i)) == -1)
	  {
	    print_usage();
	    return (1);
	  }
      if (verif_value(&conf) == -1)
	{
	  print_usage();
	  return (1);
	}
      srandom(time(NULL));
      start_server(&conf);
      return (0);
    }
  print_usage();
  return (1);
}
