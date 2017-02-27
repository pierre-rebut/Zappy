/*
** player_voir.c for voir in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Fri Jun 17 16:49:24 2016 Pierre Rebut
** Last update Fri Jun 24 14:44:17 2016 ikkar
*/

#include	<stdlib.h>
#include	"client_player.h"

static const t_dir g_dir[] =
  {
    {NORTH, &top_cases},
    {SOUTH, &bot_cases},
    {EAST, &right_cases},
    {WEST, &left_cases},
    {-1, NULL}
  };

void		top_cases(t_config *conf, t_player *cli)
{
  int		lvl;
  int		beg;

  lvl = 0;
  send_msg(cli->buff_out, "{");
  while (lvl <= cli->level)
    {
      if (lvl != 0)
	{
	  beg = lvl * -1 - 1;
	  while (++beg <= lvl)
	    {
	      aff_case(conf, cli, cli->position.x + beg, cli->position.y - lvl);
	      if (beg < cli->level)
	      	send_msg(cli->buff_out, ",");
	    }
	}
      else
	{
	  aff_case(conf, cli, cli->position.x, cli->position.y);
	  send_msg(cli->buff_out, ",");
	}
      lvl++;
    }
  send_msg(cli->buff_out, "}\n");
}

void		bot_cases(t_config *conf, t_player *cli)
{
  int		lvl;
  int		beg;

  lvl = 0;
  send_msg(cli->buff_out, "{");
  while (lvl <= cli->level)
    {
      if (lvl != 0)
	{
	  beg = lvl + 1;
	  while (--beg >= lvl * -1)
	    {
	      aff_case(conf, cli, cli->position.x + beg, cli->position.y + lvl);
	      if (beg > cli->level * -1)
		send_msg(cli->buff_out, ",");
	    }
	}
      else
	{
	  aff_case(conf, cli, cli->position.x, cli->position.y);
	  send_msg(cli->buff_out, ",");
	}
      lvl++;
    }
  send_msg(cli->buff_out, "}\n");
}

void		right_cases(t_config *conf, t_player *cli)
{
  int		lvl;
  int		beg;

  lvl = 0;
  send_msg(cli->buff_out, "{");
  while (lvl <= cli->level)
    {
      if (lvl != 0)
	{
	  beg = lvl * -1 - 1;
	  while (++beg <= lvl)
	    {
	      aff_case(conf, cli, cli->position.x + lvl, cli->position.y + beg);
	      if (beg < cli->level)
		send_msg(cli->buff_out, ",");
	    }
	}
      else
	{
	  aff_case(conf, cli, cli->position.x, cli->position.y);
	  send_msg(cli->buff_out, ",");
	}
      lvl++;
    }
  send_msg(cli->buff_out, "}\n");
}

void		left_cases(t_config *conf, t_player *cli)
{
  int		lvl;
  int		beg;

  lvl = 0;
  send_msg(cli->buff_out, "{");
  while (lvl <= cli->level)
    {
      if (lvl != 0)
	{
	  beg = lvl + 1;
	  while (--beg >= lvl * -1)
	    {
	      aff_case(conf, cli, cli->position.x - lvl, cli->position.y + beg);
	      if (beg > cli->level * -1)
		send_msg(cli->buff_out, ",");
	    }
	}
      else
	{
	  aff_case(conf, cli, cli->position.x, cli->position.y);
	  send_msg(cli->buff_out, ",");
	}
      lvl++;
    }
  send_msg(cli->buff_out, "}\n");
}

void		cmd_pl_voir(t_player *cli, t_client *lst,
			    char **tab, t_config *conf)
{
  int		i;

  i = 0;
  (void)lst;
  while (g_dir[i].fct != NULL)
    {
      if (g_dir[i].dir == cli->position.rot)
	g_dir[i].fct(conf, cli);
      i++;
    }
  (void)tab;
}
