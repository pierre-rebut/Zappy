/*
** get_param.h for param in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir/src
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Sat Jun 11 17:42:29 2016 Pierre Rebut
** Last update Sun Jun 26 16:51:53 2016 Pierre Rebut
*/

#ifndef		PSU_ZAPPY_GET_PARAM_H_
# define	PSU_ZAPPY_GET_PARAM_H_

# include	"config.h"

void		print_usage();
int		team_param(char **, t_config *, int);
void		init_config(t_config *);
int		check_param(char **, t_config *, int);
int		verif_value(t_config *);

#endif
