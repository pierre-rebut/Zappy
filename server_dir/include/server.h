/*
** server.h for server in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir/src
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Sat Jun 11 17:20:30 2016 Pierre Rebut
** Last update Sat Jun 25 14:53:47 2016 Pierre Rebut
*/

#ifndef		PSU_ZAPPY_SERVER_H_
# define	PSU_ZAPPY_SERVER_H_

# include	<sys/select.h>
# include	"client.h"

int		init_socket(int);
void		error_socket(int error);
void		close_socket(int server, t_client *);
int		read_socket(t_othercli *, t_othercli **);
int		write_socket(t_othercli *, t_othercli **, int, int);
int		reset_select(int, t_client *, fd_set *, fd_set *);
int		send_last_msg(t_othercli *, t_othercli **, char *);

#endif
