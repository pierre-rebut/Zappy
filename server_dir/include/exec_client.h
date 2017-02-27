/*
** exec_client.h for exec_client in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Tue Jun 14 17:30:30 2016 Pierre Rebut
** Last update Sat Jun 25 16:43:37 2016 Pierre Rebut
*/

#ifndef		PSU_ZAPPY_EXEC_CLIENT_H_
# define	PSU_ZAPPY_EXEC_CLIENT_H_

# include	"client.h"
# include	"config.h"

int		exec_player(t_player *, t_client *, t_config *);
int		exec_display(t_othercli *, t_client *, t_config *);
int		exec_other(t_othercli *, t_client *, t_config *, int);

int		convert_to_player(t_othercli *, t_client *,
				  t_config *, t_team *);

#endif
