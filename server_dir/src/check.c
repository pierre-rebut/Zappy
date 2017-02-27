/*
** check.c for zappy in /home/ikkar/SYSTEM_UNIX/PSU_2015_zappy/server_dir
** 
** Made by ikkar
** Login   <ikkar@epitech.net>
** 
** Started on  Fri Jun 10 16:29:18 2016 ikkar
** Last update Thu Jun 16 15:31:54 2016 Pierre Rebut
*/

#include	<stdbool.h>
#include	<string.h>
#include	"config.h"

bool		check_int(char *str)
{
  int		i;

  i = 0;
  while (str[i])
    {
      if (str[i] < '0' || str[i] > '9')
	return (false);
      i++;
    }
  return (true);
}

bool		check_team(char *str)
{
  int		i;

  i = 0;
  while (str[i])
    {
      if (str[i] < '!' || str[i] > '~' || str[i] == '-')
	return (false);
      i++;
    }
  return (true);
}

bool		check_dup(char *str, t_team **tab)
{
  int		i;

  if (tab == NULL)
    return (true);
  i = 0;
  while (tab[i])
    {
      if (strcmp(tab[i]->name, str) == 0)
	return (false);
      i++;
    }
  return (true);
}
