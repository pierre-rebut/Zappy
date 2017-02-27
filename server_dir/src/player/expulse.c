/*
** expulse.c for expulse in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Wed Jun 22 14:18:33 2016 Pierre Rebut
** Last update Sun Jun 26 16:43:13 2016 Pierre Rebut
*/

#include	"config.h"
#include	"client_display.h"
#include	"client_player.h"

void			send_broadcast(t_player *pl, char *msg, int pos)
{
  int			i;
  static const int	tmp[][10] = {
    { NORTH, 0, 1, 2, 3, 4, 5, 6, 7, 8},
    { EAST, 0, 3, 4, 5, 6, 7, 8, 1, 2},
    { SOUTH, 0, 5, 6, 7, 8, 1, 2, 3, 4},
    { WEST, 0, 7, 8, 1, 2, 3, 4, 5, 6}
  };

  i = 0;
  while (i < 4)
    {
      if (tmp[i][0] == pl->position.rot)
	{
	  send_msg(pl->buff_out, "message %d,%s\n", tmp[i][pos + 1], msg);
	  return ;
	}
      i++;
    }
}

static int		get_oldposition(t_player *pl, t_player *other)
{
  int			i;
  int			rot;
  static const int	tmp[][5] = {
    { NORTH, 1, 7, 5, 3 },
    { EAST, 3, 1, 7, 5 },
    { SOUTH, 5, 3, 1, 7 },
    { WEST, 7, 5, 3, 1 }
  };

  rot = other->position.rot;
  if (rot < 3)
    rot += 2;
  else
    rot -= 2;
  i = 0;
  while (i < 4)
    {
      if (tmp[i][0] == pl->position.rot)
	return (tmp[i][rot]);
      i++;
    }
  return (1);
}

void		cmd_pl_expulse(t_player *pl, t_client *lst,
			      char **tab, t_config *conf)
{
  bool		val;
  int		rot;
  t_player	*tmp;

  (void)tab;
  val = false;
  tmp = lst->lst_player;
  send_dl_pex(lst, pl);
  while (tmp != NULL)
    {
      if (tmp != pl && tmp->position.x == pl->position.x &&
	  tmp->position.y == pl->position.y)
	{
	  rot = get_oldposition(tmp, pl);
	  val = true;
	  move_player(tmp, lst, conf, pl->position.rot);
	  send_msg(tmp->buff_out, "deplacement: %d\n", rot);
	}
      tmp = tmp->next;
    }
  if (val == true)
    send_msg(pl->buff_out, "ok\n");
  else
    send_msg(pl->buff_out, "ko\n");
}
