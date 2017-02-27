/*
** other_commands.c for zappy in /home/ikkar/SYSTEM_UNIX/PSU_2015_zappy/server_dir
** 
** Made by ikkar
** Login   <ikkar@epitech.net>
** 
** Started on  Fri Jun 24 14:31:08 2016 ikkar
** Last update Fri Jun 24 17:36:25 2016 Pierre Rebut
*/

#include	<stdlib.h>
#include	"client_display.h"
#include	"client_player.h"

void		cmd_pl_connect(t_player *cli, t_client *lst,
			      char **tab, t_config *conf)
{
  (void)tab;
  (void)lst;
  (void)conf;
  send_msg(cli->buff_out, "%d\n", cli->team->player);
}

void		cmd_pl_invent(t_player *cli, t_client *lst,
			      char **tab, t_config *conf)
{
  (void)tab;
  (void)conf;
  (void)lst;
  send_msg(cli->buff_out, "{nourriture %d,linemate %d,deraumere %d,",
	   compte_pierre(cli->inventory, FOOD),
	   compte_pierre(cli->inventory, LIMATE),
	   compte_pierre(cli->inventory, DERAUMERE));
  send_msg(cli->buff_out, "sibur %d,mendiane %d,phiras %d,thystame %d}\n",
	   compte_pierre(cli->inventory, SIBUR),
	   compte_pierre(cli->inventory, MENDIANE),
	   compte_pierre(cli->inventory, PHIRAS),
	   compte_pierre(cli->inventory, THYSTAME));
}

void		move_player(t_player *cli, t_client *lst, t_config *conf, int rot)
{
  int		move_x;
  int		move_y;
  t_elemmap	*obj;

  move_x = 0;
  move_y = 0;
  if (rot == 1)
    move_y -= 1;
  else if (rot == 2)
    move_x += 1;
  else if (rot == 3)
    move_y += 1;
  else
    move_x -= 1;
  obj = get_player_pos(conf, cli);
  cli->position.x = (cli->position.x + move_x) % conf->x_map;
  cli->position.y = (cli->position.y + move_y) % conf->y_map;
  if (cli->position.x < 0)
    cli->position.x = conf->x_map - 1;
  if (cli->position.y < 0)
    cli->position.y = conf->y_map - 1;
  move_player_pos(conf, cli, obj);
  send_dl_ppo(lst, cli);
}

void		aff_case(t_config *conf, t_player *cli, int x, int y)
{
  t_map		*pos_player;
  t_elemmap	*tmp;
  char		*name;

  x = x % conf->x_map;
  y = y % conf->y_map;
  if (x < 0)
    x = conf->x_map - x;
  if (y < 0)
    y = conf->y_map - y;
  if ((pos_player = get_pos_map(conf, x, y)) == NULL)
    return ;
  tmp = pos_player->obj;
  while (tmp != NULL)
    {
      name = get_objname(tmp->type);
      if (name != NULL)
	send_msg(cli->buff_out, " %s", name);
      tmp = tmp->next;
    }
}
