/*
** client_player.h for client in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Wed Jun 15 17:32:32 2016 Pierre Rebut
** Last update Fri Jun 24 18:49:27 2016 Pierre Rebut
*/

#ifndef		PSU_ZAPPY_CLIENT_PLAYER_H_
# define	PSU_ZAPPY_CLIENT_PLAYER_H_

# include	<stdlib.h>
# include	"client.h"

typedef	struct	s_clientpl_cmd
{
  char		*cmd;
  size_t	param;
  double	time;
  void		(*fct)(t_player *, t_client *, char **, t_config *);
  void		(*fct_before)(t_player *, t_client *, char **, t_config *);
}		t_clientpl_cmd;

typedef	struct	s_objtype
{
  char		*name;
  enum	e_type	value;
}		t_objtype;

typedef struct	s_dir
{
  int		dir;
  void		(*fct)(t_config *, t_player *);
}		t_dir;

typedef	struct	s_incantation
{
  int		elevate;
  int		player;
  int		line;
  int		derau;
  int		sibur;
  int		mendiane;
  int		phiras;
  int		thys;
}		t_incantation;

char		*get_objname(enum e_type);
t_elemmap	*get_objmap(t_elemmap *, enum e_type);
void		move_obj_loot(t_player *, t_map *, t_elemmap *);
void		move_obj_drop(t_player *, t_map *, t_elemmap *);
void		move_player(t_player *, t_client *, t_config *, int);

void		cmd_pl_avance(t_player *, t_client *, char **, t_config *);
void		cmd_pl_droite(t_player *, t_client *, char **, t_config *);
void		cmd_pl_gauche(t_player *, t_client *, char **, t_config *);
void		cmd_pl_voir(t_player *, t_client *, char **, t_config *);
void		cmd_pl_invent(t_player *, t_client *, char **, t_config *);
void		cmd_pl_prend(t_player *, t_client *, char **, t_config *);
void		cmd_pl_pose(t_player *, t_client *, char **, t_config *);
void		cmd_pl_expulse(t_player *, t_client *, char **, t_config *);
void		cmd_pl_broad(t_player *, t_client *, char **, t_config *);
void		cmd_pl_incant(t_player *, t_client *, char **, t_config *);
void		cmd_pl_incant_before(t_player *, t_client *, char **, t_config *);
void		cmd_pl_fork(t_player *, t_client *, char **, t_config *);
void		cmd_pl_fork_before(t_player *, t_client *, char **, t_config *);
void		cmd_pl_connect(t_player *, t_client *, char **, t_config *);

void		top_cases(t_config *, t_player *);
void		bot_cases(t_config *, t_player *);
void		right_cases(t_config *, t_player *);
void		left_cases(t_config *, t_player *);

t_elemmap	*get_player_pos(t_config *, t_player *);
void		move_player_pos(t_config *, t_player *, t_elemmap *);

int		player_is_dead(t_player *, t_client *, t_config *);
void		aff_case(t_config *, t_player *, int, int);

bool		check_incant(t_player *, t_config *, t_client *);
void		delete_type_rock(t_map *, enum e_type, int);
void		delete_incant_rock(t_player *, t_config *);

int		send_player_dead(t_player *, t_client *);

#endif
