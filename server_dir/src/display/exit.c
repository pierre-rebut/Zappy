/*
** exit.c for exit in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir/src
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Fri Jun 24 17:24:36 2016 Pierre Rebut
** Last update Fri Jun 24 17:26:51 2016 Pierre Rebut
*/

#include	<stdlib.h>
#include	"client_display.h"

void		cmd_sst(t_othercli *cli, t_client *lst,
			char **tab, t_config *conf)
{
  int		ut;

  ut = atoi(tab[1]);
  if (ut >= 0)
    send_msg(cli->buff_out, "sbp\n");
  conf->u_time = ut;
  send_dl_sgt(lst, conf);
}

void		cmd_sgt(t_othercli *cli, t_client *lst,
			char **tab, t_config *conf)
{
  (void)lst;
  (void)tab;
  send_msg(cli->buff_out, "sgt %d\n", conf->u_time);
}
