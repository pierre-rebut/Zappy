/*
** my_wordtab.c for wordtab in /home/rebut_p/Programmation/PSU/PSU_2015_myftp
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Mon May  2 13:46:58 2016 Pierre Rebut
** Last update Wed Jun 15 18:15:12 2016 Pierre Rebut
*/

#include	<stdlib.h>

size_t		len_wordtab(char **tab)
{
  size_t	i;

  i = 0;
  while (tab[i] != NULL)
    i++;
  return (i);
}

static size_t	len_tab(const char *str)
{
  size_t	nb;
  size_t	i;

  i = 0;
  nb = 1;
  while (str[i] != '\0')
    {
      if (str[i] == ' ')
	{
	  while (str[i] != '\0' && str[i] == ' ')
	    i++;
	  nb++;
	}
      else
	i++;
    }
  return (nb);
}

static size_t	len_word(const char *str, size_t i)
{
  size_t	nb;

  nb = 0;
  while (str[i] != '\0' && str[i] != ' ')
    {
      i++;
      nb++;
    }
  return (nb);
}

void		free_wordtab(char **tab)
{
  size_t	i;

  i = 0;
  while (tab[i] != NULL)
    {
      free(tab[i]);
      i++;
    }
  free(tab);
}

char		**my_wordtab(const char *str, size_t i, size_t y)
{
  char		**tab;
  size_t	x;

  tab = malloc(sizeof(char*) * (len_tab(str) + 1));
  if (tab == NULL)
    return (NULL);
  while (str[i] != '\0')
    {
      if (str[i] != ' ')
	{
	  x = 0;
	  tab[y] = malloc(sizeof(char) * (len_word(str, i) + 1));
	  if (tab[y] == NULL)
	    return (NULL);
	  while (str[i] != '\0' && str[i] != ' ')
	    tab[y][x++] = str[i++];
	  tab[y][x] = '\0';
	  y++;
	}
      else
	i++;
    }
  tab[y] = NULL;
  return (tab);
}
