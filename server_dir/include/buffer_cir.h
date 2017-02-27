/*
** buffer_cir.h for buffer in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Fri Jun 10 13:53:52 2016 Pierre Rebut
** Last update Mon Jun 20 14:11:32 2016 Pierre Rebut
*/

#ifndef		PSU_2015_BUFFER_CIR_H_
# define	PSU_2015_BUFFER_CIR_H_

# define	BUFFER_SIZE	4096

# include	<stdbool.h>

typedef	struct		s_cirbuff
{
  char			buff[BUFFER_SIZE];
  char			*read_ptr;
  char			*write_ptr;
  struct s_cirbuff	*next;
}			t_cirbuff;

typedef	struct
{
  t_cirbuff		*read_buff;
  t_cirbuff		*write_buff;
}			t_buff;

int		update_cirbuffer(t_cirbuff **);
t_buff		*init_buffer();
void		free_buffer(t_buff *);
void		free_elem(t_buff *, t_cirbuff *);
int		write_buffer(t_buff *, const char *cmd);
char		*read_buffer(t_buff *, bool, char *, int);
int		send_msg(t_buff *, const char *format, ...);
bool		check_if_msg(t_buff *);

#endif
