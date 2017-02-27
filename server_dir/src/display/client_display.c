/*
** client_other.c for other in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Tue Jun 14 17:34:28 2016 Pierre Rebut
** Last update Fri Jun 17 18:31:09 2016 Pierre Rebut
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	"exec_client.h"
#include	"wordtab.h"
#include	"client_display.h"

static const t_clientdis_cmd g_cmd[] = {
  { "msz", 1, &cmd_msz },
  { "bct", 3, &cmd_bct },
  { "mct", 1, &cmd_mct },
  { "tna", 1, &cmd_tna },
  { "ppo", 2, &cmd_ppo },
  { "plv", 2, &cmd_plv },
  { "pin", 2, &cmd_pin },
  { "sst", 2, &cmd_sst },
  { "sgt", 1, &cmd_sgt },
  { NULL }
};

static void	do_cmd(t_othercli *cli, t_client *lst,
		       t_config *conf, char **tab)
{
  int		i;

  i = 0;
  while (g_cmd[i].cmd != NULL)
    {
      if (strcasecmp(g_cmd[i].cmd, tab[0]) == 0)
	{
	  if (len_wordtab(tab) == g_cmd[i].param)
	    (*(g_cmd[i].fct))(cli, lst, tab, conf);
	  else
	    send_msg(cli->buff_out, "sbp\n");
	  return ;
	}
      i++;
    }
  send_msg(cli->buff_out, "suc\n");
}

int		exec_display(t_othercli *cli, t_client *lst,
			     t_config *conf)
{
  char		*str;
  char		**tab;

  str = read_buffer(cli->buff_in, true, NULL, 0);
  if (str != NULL)
    {
      tab = my_wordtab(str, 0, 0);
      if (tab != NULL && tab[0] != NULL)
	{
	  fprintf(stderr, "[DISPLAY] %d: %s\n", cli->fd, str);
	  do_cmd(cli, lst, conf, tab);
	  free_wordtab(tab);
	}
      free(str);
    }
  return (0);
}

int		compte_pierre(t_elemmap *map, enum e_type val)
{
  int		nb;

  nb = 0;
  while (map != NULL)
    {
      if (map->type == val)
	nb++;
      map = map->next;
    }
  return (nb);
}

void		send_dl_all_bct(t_client *cli, t_config *conf)
{
  t_othercli	*tmp;

  tmp = cli->lst_display;
  while (tmp != NULL)
    {
      send_all_bct(tmp, conf);
      tmp = tmp->next;
    }
}
