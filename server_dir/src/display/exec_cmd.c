/*
** exec_cmd.c for exec in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir/src/display
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Wed Jun 15 17:37:52 2016 Pierre Rebut
** Last update Wed Jun 15 18:58:30 2016 Pierre Rebut
*/

#include	<stdlib.h>
#include	"client_display.h"

void		cmd_msz(t_othercli *cli, t_client *lst,
			char **tab, t_config *conf)
{
  (void)tab;
  (void)lst;
  send_msz(cli, conf);
}

void		cmd_bct(t_othercli *cli, t_client *lst,
			char **tab, t_config *conf)
{
  int		x;
  int		y;

  (void)lst;
  x = atoi(tab[1]);
  y = atoi(tab[2]);
  if (x < 0 || y < 0)
    send_msg(cli->buff_out, "sbp\n");
  else
    send_bct(cli, conf, x, y);
}

void		cmd_mct(t_othercli *cli, t_client *lst,
			char **tab, t_config *conf)
{
  (void)tab;
  (void)lst;
  send_all_bct(cli, conf);
}

void		cmd_tna(t_othercli *cli, t_client *lst,
			char **tab, t_config *conf)
{
  (void)tab;
  (void)lst;
  send_tna(cli, conf);
}
