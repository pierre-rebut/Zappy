/*
** take_obj.c for take player in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Fri Jun 17 13:39:22 2016 Pierre Rebut
** Last update Sat Jun 18 15:21:10 2016 Pierre Rebut
*/

#include	<string.h>
#include	"client_display.h"
#include	"client_player.h"

static const t_objtype	g_objtype[] = {
  { "nourriture", FOOD },
  { "linemate", LIMATE },
  { "deraumere", DERAUMERE },
  { "sibur", SIBUR },
  { "mendiane", MENDIANE },
  { "phiras", PHIRAS },
  { "thystame", THYSTAME },
  { "joueur", PLAYER },
  { NULL }
};

char		*get_objname(enum e_type value)
{
  int		i;

  i = 0;
  while (g_objtype[i].name != NULL)
    {
      if (g_objtype[i].value == value)
	return (g_objtype[i].name);
      i++;
    }
  return (NULL);
}

static enum e_type	get_objtype(char *str)
{
  int			i;

  i = 0;
  while (i < 7)
    {
      if (strcasecmp(g_objtype[i].name, str) == 0)
	return (g_objtype[i].value);
      i++;
    }
  return (DEFAULT);
}

void		cmd_pl_prend(t_player *cli, t_client *lst,
			      char **tab, t_config *conf)
{
  t_map		*map;
  t_elemmap	*obj;
  enum e_type	tmp;

  tmp = get_objtype(tab[1]);
  map = get_pos_map(conf, cli->position.x, cli->position.y);
  if (tmp == DEFAULT || map == NULL)
    send_msg(cli->buff_out, "ko\n");
  else
    {
      obj = get_objmap(map->obj, tmp);
      if (obj == NULL)
	send_msg(cli->buff_out, "ko\n");
      else
	{
	  move_obj_loot(cli, map, obj);
	  send_dl_pgt(lst, cli, tmp);
	  send_dl_pin(lst, cli);
	  send_dl_bct(lst, conf, cli->position.x, cli->position.y);
	  send_msg(cli->buff_out, "ok\n");
	}
    }
}

void		cmd_pl_pose(t_player *cli, t_client *lst,
			    char **tab, t_config *conf)
{
  t_map		*map;
  t_elemmap	*obj;
  enum e_type	tmp;

  tmp = get_objtype(tab[1]);
  if (tmp == DEFAULT)
    send_msg(cli->buff_out, "ko\n");
  else
    {
      map = get_pos_map(conf, cli->position.x, cli->position.y);
      obj = get_objmap(cli->inventory, tmp);
      if (obj == NULL || map == NULL)
	send_msg(cli->buff_out, "ko\n");
      else
	{
	  move_obj_drop(cli, map, obj);
	  send_dl_pdr(lst, cli, tmp);
	  send_dl_pin(lst, cli);
	  send_dl_bct(lst, conf, cli->position.x, cli->position.y);
	  send_msg(cli->buff_out, "ok\n");
	}
    }
}
