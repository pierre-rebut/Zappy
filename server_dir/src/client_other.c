/*
** client_other.c for other in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Tue Jun 14 17:34:28 2016 Pierre Rebut
** Last update Sun Jun 26 16:30:48 2016 Pierre Rebut
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	"server.h"
#include	"exec_client.h"
#include	"client_display.h"

static int	convert_to_display(t_othercli *cli, t_client *lst,
				   t_config *conf, char *str)
{
  free(str);
  fprintf(stderr, "[INFO] %d: convert to display\n", cli->fd);
  if (cli->prev != NULL)
    cli->prev->next = cli->next;
  else
    lst->lst_tmp = cli->next;
  if (cli->next != NULL)
    cli->next->prev = cli->prev;
  cli->prev = NULL;
  cli->next = lst->lst_display;
  if (lst->lst_display != NULL)
    lst->lst_display->prev = cli;
  lst->lst_display = cli;
  send_msz(cli, conf);
  send_dl_sgt(lst, conf);
  send_all_bct(cli, conf);
  send_tna(cli, conf);
  send_all_pnw(cli, lst);
  send_all_enw(cli, lst);
  return (0);
}

int		exec_other(t_othercli *cli, t_client *lst,
			   t_config *conf, int i)
{
  char		*str;

  str = read_buffer(cli->buff_in, true, NULL, 0);
  if (str != NULL)
    {
      if (strcmp(str, "GRAPHIC") == 0)
	return (convert_to_display(cli, lst, conf, str));
      else
	{
	  while (conf->team[i] != NULL)
	    {
	      if (strcmp(conf->team[i]->name, str) == 0)
		{
		  free(str);
		  return (convert_to_player(cli, lst, conf, conf->team[i]));
		}
	      i++;
	    }
	}
      free(str);
      send_last_msg(cli, &lst->lst_tmp, "ko\n");
      destroy_othercli(cli, lst);
    }
  return (1);
}
