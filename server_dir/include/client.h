/*
** client.h for client in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Sat Jun 11 16:16:50 2016 Pierre Rebut
** Last update Wed Jun 22 18:31:08 2016 Pierre Rebut
*/

#ifndef		PSU_ZAPPY_CLIENT_H_
# define	PSU_ZAPPY_CLIENT_H_

# include	<time.h>
# include	<sys/time.h>
# include	<stdbool.h>
# include	<sys/select.h>
# include	"buffer_cir.h"
# include	"config.h"

# define	NORTH	1
# define	EAST	2
# define	SOUTH	3
# define	WEST	4

typedef	struct	s_pos
{
  int		x;
  int		y;
  int		rot;
}		t_pos;

struct s_player;
struct s_client;

typedef	struct		s_execfct
{
  struct timeval	start;
  double		limit;
  char			**param;
  void			(*fct)(struct s_player *, struct s_client *,
			       char **, t_config *);
}			t_execfct;

typedef	struct		s_player
{
  int			fd;
  t_buff		*buff_in;
  t_buff		*buff_out;
  struct s_player	*prev;
  struct s_player	*next;

  t_team		*team;
  t_pos			position;
  int			level;
  t_elemmap		*inventory;
  t_execfct		exec;

  struct timeval	time_life;
  long			life;
}			t_player;

typedef	struct		s_othercli
{
  int			fd;
  t_buff		*buff_in;
  t_buff		*buff_out;
  struct s_othercli	*prev;
  struct s_othercli	*next;
}			t_othercli;

typedef	struct		s_eggs
{
  int			id;
  int			creator;
  t_team		*team;
  t_pos			position;
  bool			eclose;
  struct timeval	timeval;

  struct s_eggs		*next;
  struct s_eggs		*prev;
}			t_eggs;

typedef	struct		s_client
{
  int			connexion;
  t_eggs		*lst_eggs;
  t_player		*lst_player;
  t_othercli		*lst_display;
  t_othercli		*lst_tmp;
}			t_client;

int			init_client(int fd, t_client *);
void			new_client(int, t_client *);
void			destroy_player(t_player *, t_client *, t_config *);
void			destroy_othercli(t_othercli *, t_client *);
void			destroy_eggs(t_eggs *, t_client *);

void			exec_all_player(t_client *, t_config *,
					fd_set *, fd_set *);
void			exec_all_display(t_client *, t_config *,
					 fd_set *, fd_set *);
void			exec_all_other(t_client *, t_config *,
				       fd_set *, fd_set *);
void			exec_all_eggs(t_client *, t_eggs *, t_config *);

#endif
