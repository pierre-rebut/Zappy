/*
** get_param.c for param in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir/src
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Sat Jun 11 17:38:35 2016 Pierre Rebut
** Last update Sun Jun 26 17:09:46 2016 Pierre Rebut
*/

#include	<stdlib.h>
#include	<string.h>
#include	<stdio.h>
#include	"config.h"

static const	t_option g_param[] =
  {
    {"-p", &port_param},
    {"-x", &x_param},
    {"-y", &y_param},
    {"-n", &team_param},
    {"-c", nbP_param},
    {"-t", time_param},
    {NULL, NULL}
  };

void		print_usage()
{
  fprintf(stderr, "usage: ./zappy_server [-p port] [-t time] [-c nbplayer]");
  fprintf(stderr, " [-x xmap] [-y ymap] -n equipe1 equipe2 ..\n");
}

int		team_param(char **pam, t_config *conf, int i)
{
  int		j;

  j = 0;
  if (conf->team != NULL)
    return (-1);
  while (pam[++i])
    {
      if (pam[i][0] == '-')
	return (i - 1);
      else if (check_team(pam[i]) && check_dup(pam[i], conf->team) == true)
	{
	  conf->team = realloc(conf->team, sizeof(t_team *) * (j + 2));
	  if (conf->team == NULL)
	    return (-1);
	  if ((conf->team[j] = malloc(sizeof(t_team))) == NULL)
	    return (-1);
	  if ((conf->team[j]->name = strdup(pam[i])) == NULL)
	    return (-1);
	  conf->team[j]->player = 0;
	  conf->team[++j] = NULL;
	}
      else
	return (-1);
    }
  return (i);
}

void		init_config(t_config *conf)
{
  conf->port = PORT;
  conf->x_map = WIDTH;
  conf->y_map = HEIGHT;
  conf->team = NULL;
  conf->nb_players = LIM_P;
  conf->u_time = TIME;
  gettimeofday(&(conf->time), NULL);
  conf->time_food.tv_sec = conf->time.tv_sec;
  conf->time_food.tv_usec = conf->time.tv_usec;
  conf->timeout.tv_sec = 0;
  conf->timeout.tv_usec = 10000;
}

int		check_param(char **param, t_config *conf, int i)
{
  int		j;

  j = 0;
  while (g_param[j].param != NULL)
    {
      if (strcmp(g_param[j].param, param[i]) == 0)
	{
	  if ((i = g_param[j].fct(param, conf, i)) != -1)
	    return (i);
	  else
	    return (-1);
	}
      j++;
    }
  return (-1);
}

int		verif_value(t_config *conf)
{
  if (conf->team == NULL || count_tab(conf->team) <= 1 ||
      conf->nb_players < 1 || conf->u_time < 1 || conf->x_map < 1 ||
      conf->y_map < 1 || conf->x_map > 1000 || conf->y_map > 1000 ||
      conf->u_time > 1000 || conf->nb_players > 1000)
    return (-1);
  return (0);
}
