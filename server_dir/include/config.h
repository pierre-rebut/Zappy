/*
** config.h for config in /home/ikkar/SYSTEM_UNIX/PSU_2015_zappy/server_dir/include
** 
** Made by ikkar
** Login   <ikkar@epitech.net>
** 
** Started on  Fri Jun 10 13:52:38 2016 ikkar
** Last update Fri Jun 24 18:01:38 2016 Pierre Rebut
*/

#ifndef		_CONFIG_H_
# define	_CONFIG_H_

# define	PORT 4242
# define	WIDTH 20
# define	HEIGHT 20
# define	LIM_P 1
# define	TIME 100

# include	<stdbool.h>
# include	<time.h>
# include	<sys/time.h>

# include	"map.h"

struct s_client;

typedef	struct	s_team
{
  char		*name;
  int		player;
}		t_team;

typedef struct		s_config
{
  int			port;
  int			x_map;
  int			y_map;
  t_team		**team;
  int			nb_players;
  int			u_time;
  t_map			*map;
  t_team		*victory;
  struct timeval	time;
  struct timeval	time_food;
  struct timeval	timeout;
}			t_config;

typedef struct	s_option
{
  char		*param;
  int		(*fct)(char **, t_config *, int);
}		t_option;

int		port_param(char **, t_config *,  int);
int		x_param(char **, t_config *, int);
int		y_param(char **, t_config *, int);
int		nbP_param(char **, t_config *, int);
int		time_param(char **, t_config *, int);
int		team_param(char **, t_config *, int);

bool		check_int(char *);
bool		check_team(char *);
bool		check_dup(char *, t_team **);

int		count_tab(t_team **);
void		aff_team(t_team **, int);

void		init_map(t_config *);
void		free_map(t_map *);
t_map		*get_pos_map(t_config *, int, int);

void		add_rock(t_map *, enum e_type);
void		pop_rocks(t_config *, int);
void		pop_food(struct s_client *, t_config *, int);
void		random_pop_food(t_config *, struct s_client *);

bool		check_timeout(t_config *, struct timeval *, double);
void		set_timeout_value(t_config *);

#endif /* !_CONFIG_H_ */
