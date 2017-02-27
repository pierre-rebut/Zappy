/*
** utils.c for utils in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir/src
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Fri Jun 10 16:23:56 2016 Pierre Rebut
** Last update Thu Jun 16 15:25:57 2016 Pierre Rebut
*/

#include	<string.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	"config.h"

char		*my_strcat(char *dest, char src[])
{
  int		i;
  int		u;

  u = 0;
  if (dest == NULL)
    return (strdup(src));
  i = strlen(dest);
  dest = realloc(dest, strlen(dest) + strlen(src) + 1);
  if (dest == NULL)
    return (NULL);
  while (src[u] != '\0')
    dest[i++] = src[u++];
  dest[i] = '\0';
  return (dest);
}

int		count_tab(t_team **tab)
{
  int		i;

  i = 0;
  if (tab == NULL)
    return (i);
  while (tab[i])
    i++;
  return (i);
}

void	aff_team(t_team **tab, int nb_player)
{
  int	i;

  i = 0;
  fprintf(stderr, "Teams :\n");
  while (tab[i])
    {
      fprintf(stderr, "\tName(%s) Max(%d)\n", tab[i]->name, nb_player);
      i++;
    }
}
