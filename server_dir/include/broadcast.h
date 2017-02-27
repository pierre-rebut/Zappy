/*
** broadcast.h for zappy in /home/ikkar/SYSTEM_UNIX/PSU_2015_zappy/server_dir/src
** 
** Made by ikkar
** Login   <ikkar@epitech.net>
** 
** Started on  Tue Jun 21 12:54:18 2016 ikkar
** Last update Fri Jun 24 14:24:06 2016 ikkar
*/

#ifndef		BROADCAST_H_
# define       	BROADCAST_H_

# define	ABS(x)  ( ( (x) < 0) ? -(x) : (x) )

# include	<stdbool.h>
# include	"client.h"

typedef struct	s_way
{
  int		x_neg;
  int		y_neg;
  int		x_pos;
  int		y_pos;
  bool		positif_x;
  bool		positif_y;
}		t_way;

void		send_broadcast(t_player *, char *, int);
void		all_neg(t_player *, t_player *, char *);
void		x_neg(t_player *, t_player *, char *);
void		y_neg(t_player *, t_player *, char *);
void		x_null(t_way, t_player *, t_player *, char *);
void		y_null(t_way, t_player *, t_player *, char *);

#endif		/* ! BROADCAST_H */
