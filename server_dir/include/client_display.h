/*
** client_display.h for client in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Wed Jun 15 17:32:32 2016 Pierre Rebut
** Last update Wed Jun 22 11:45:21 2016 Pierre Rebut
*/

#ifndef		PSU_ZAPPY_CLIENT_DISPLAY_H_
# define	PSU_ZAPPY_CLIENT_DISPLAY_H_

# include	<stdlib.h>
# include	<stdarg.h>
# include	"client.h"

typedef	struct	s_clientdis_cmd
{
  char		*cmd;
  size_t	param;
  void		(*fct)(t_othercli *, t_client *, char **, t_config *);
}		t_clientdis_cmd;

void		cmd_msz(t_othercli *, t_client *, char **, t_config *);
void		cmd_bct(t_othercli *, t_client *, char **, t_config *);
void		cmd_mct(t_othercli *, t_client *, char **, t_config *);
void		cmd_tna(t_othercli *, t_client *, char **, t_config *);
void		cmd_ppo(t_othercli *, t_client *, char **, t_config *);
void		cmd_plv(t_othercli *, t_client *, char **, t_config *);
void		cmd_pin(t_othercli *, t_client *, char **, t_config *);
void		cmd_sst(t_othercli *, t_client *, char **, t_config *);
void		cmd_sgt(t_othercli *, t_client *, char **, t_config *);

void		send_msz(t_othercli *, t_config *);
void		send_bct(t_othercli *, t_config *, int, int);
void		send_all_bct(t_othercli *, t_config *);
void		send_tna(t_othercli *, t_config *);
void		send_all_pnw(t_othercli *, t_client *);
void		send_all_enw(t_othercli *, t_client *);

void		send_dl_sgt(t_client *, t_config *);
void		send_dl_bct(t_client *, t_config *, int, int);
void		send_dl_all_bct(t_client *, t_config *);
void		send_dl_pnw(t_client *, t_player *);
void		send_dl_ppo(t_client *, t_player *);
void		send_dl_plv(t_client *, t_player *);
void		send_dl_pin(t_client *, t_player *);
void		send_dl_pex(t_client *, t_player *);
void		send_dl_pbc(t_client *, t_player *, char *);
void		send_dl_pie(t_client *, int, int, int);
void		send_dl_pfk(t_client *, t_player *);
void		send_dl_pdr(t_client *, t_player *, enum e_type);
void		send_dl_pgt(t_client *, t_player *, enum e_type);
void		send_dl_pdi(t_client *, t_player *);
void		send_dl_seg(t_client *, char *);
void		send_dl_smg(t_client *, char *);
void		send_dl_pic(t_client *, t_player *, int);
void		send_dl_enw(t_client *, t_player *, t_eggs *);
void		send_dl_eht(t_client *, t_eggs *);
void		send_dl_ebo(t_client *, t_eggs *);
void		send_dl_edi(t_client *, t_eggs *);

#endif
