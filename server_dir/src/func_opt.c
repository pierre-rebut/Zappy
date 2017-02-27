/*
** func_opt.c for zappy in /home/ikkar/SYSTEM_UNIX/PSU_2015_zappy/server_dir/src
** 
** Made by ikkar
** Login   <ikkar@epitech.net>
** 
** Started on  Fri Jun 10 15:16:19 2016 ikkar
** Last update Fri Jun 10 17:35:41 2016 ikkar
*/

#include	<stdlib.h>
#include	<stdbool.h>

#include	"config.h"

int		port_param(char **param, t_config *conf, int i)
{
  if (param[i + 1] == NULL)
    return (-1);
  if (check_int(param[i + 1]) == false)
    return (-1);
  conf->port = atoi(param[i + 1]);
  if (conf->port < 1024 || conf->port > 65535)
    return (-1);
  return (i + 1);
}

int		x_param(char **param, t_config *conf, int i)
{
  if (param[i + 1] == NULL)
    return (-1);
  if (check_int(param[i + 1]) == false)
    return (-1);
  conf->x_map = atoi(param[i + 1]);
  return (i + 1);
}

int		y_param(char **param, t_config *conf, int i)
{
  if (param[i + 1] == NULL)
    return (-1);
  if (check_int(param[i + 1]) == false)
    return (-1);
  conf->y_map = atoi(param[i + 1]);
  return (i + 1);
}

int		nbP_param(char **param, t_config *conf, int i)
{
  if (param[i + 1] == NULL)
    return (-1);
  if (check_int(param[i + 1]) == false)
    return (-1);
  conf->nb_players = atoi(param[i + 1]);
  return (i + 1);
}

int		time_param(char **param, t_config *conf, int i)
{
  if (param[i + 1] == NULL)
    return (-1);
  if (check_int(param[i + 1]) == false)
    return (-1);
  conf->u_time = atoi(param[i + 1]);
  return (i + 1);
}
