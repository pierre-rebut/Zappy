/*
** check_victory.h for victory in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Wed Jun 22 12:45:20 2016 Pierre Rebut
** Last update Wed Jun 22 13:14:47 2016 Pierre Rebut
*/

#ifndef		PSU_ZAPPY_CHECK_VICTORY_H_
# define	PSU_ZAPPY_CHECK_VICTORY_H_

# include	"client.h"
# include	"config.h"

int		send_victory(t_client *, t_config *, int);
void		check_victory(t_client *, t_config *);
void		check_defeat(t_client *, t_config *);

#endif
