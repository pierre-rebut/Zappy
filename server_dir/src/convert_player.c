/*
** convert_player.c for convert in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir/src
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Fri Jun 24 17:30:32 2016 Pierre Rebut
** Last update Sun Jun 26 16:23:26 2016 Pierre Rebut
*/

#include	<stdio.h>
#include	<sys/socket.h>
#include	<stdlib.h>
#include	"server.h"
#include	"client_display.h"
#include	"client_player.h"

static int	player_env_basic(t_player *pl, t_map *map)
{
  t_elemmap	*tmp;
  int		i;

  i = 0;
  if ((tmp = malloc(sizeof(t_elemmap))) == NULL)
    return (-1);
  tmp->type = PLAYER;
  tmp->prev = NULL;
  tmp->next = map->obj;
  if (map->obj != NULL)
    map->obj->prev = tmp;
  map->obj = tmp;
  while (i < 10)
    {
      if ((tmp = malloc(sizeof(t_elemmap))) == NULL)
	return (-1);
      tmp->type = FOOD;
      tmp->prev = NULL;
      tmp->next = pl->inventory;
      if (pl->inventory != NULL)
	pl->inventory->prev = tmp;
      pl->inventory = tmp;
      i++;
    }
  return (0);
}

static void	player_modif(t_player *cli, t_client *lst,
			     t_config *conf, t_team *team)
{
  t_map		*map;

  cli->prev = NULL;
  cli->next = lst->lst_player;
  if (lst->lst_player != NULL)
    lst->lst_player->prev = cli;
  lst->lst_player = cli;
  cli->team = team;
  cli->position.rot = random() % 4 + 1;
  cli->level = 1;
  cli->inventory = NULL;
  cli->exec.fct = NULL;
  cli->life = 0;
  map = get_pos_map(conf, cli->position.x, cli->position.y);
  if (map != NULL)
    player_env_basic(cli, map);
  team->player --;
  send_msg(cli->buff_out, "%d\n%d %d\n", team->player,
	   conf->x_map, conf->y_map);
  pop_food(lst, conf, 10);
  send_dl_pnw(lst, cli);
  send_dl_pin(lst, cli);
  send_dl_all_bct(lst, conf);
}

static t_eggs	*get_team_eggs(t_client *lst, t_team *team)
{
  t_eggs	*tmp;

  tmp = lst->lst_eggs;
  while (tmp != NULL)
    {
      if (tmp->team == team && tmp->eclose == true)
	return (tmp);
      tmp = tmp->next;
    }
  return (NULL);
}

static t_player	*check_team_info(t_othercli *cli, t_client *lst,
				 t_team *team, int fd)
{
  t_player	*tmp;

  if (team->player <= 0)
    {
      fprintf(stderr, "[WRN] %d: can't convert to player\n", cli->fd);
      send_last_msg(cli, &lst->lst_tmp, "ko\n");
      destroy_othercli(cli, lst);
      return (NULL);
    }
  if (cli->prev != NULL)
    cli->prev->next = cli->next;
  else
    lst->lst_tmp = cli->next;
  if (cli->next != NULL)
    cli->next->prev = cli->prev;
  fd = cli->fd;
  tmp = realloc(cli, sizeof(t_player));
  if (tmp == NULL)
    {
      fprintf(stderr, "[WRN] %d: can't convert to player (malloc)\n", fd);
      shutdown(fd, SHUT_RDWR);
      return (NULL);
    }
  fprintf(stderr, "[INFO] %d: convert to player: %s\n", tmp->fd, team->name);
  return (tmp);
}

int		convert_to_player(t_othercli *cli, t_client *lst,
				  t_config *conf, t_team *team)
{
  t_eggs	*egg;
  t_player	*tmp;

  if ((tmp = check_team_info(cli, lst, team, -1)) == NULL)
    return (1);
  if ((egg = get_team_eggs(lst, team)) == NULL)
    {
      tmp->position.x = random() % conf->x_map;
      tmp->position.y = random() % conf->y_map;
    }
  else
    {
      tmp->position.x = egg->position.x;
      tmp->position.y = egg->position.y;
      fprintf(stderr, "[INFO] %d: pop with egg %d\n", tmp->fd, egg->id);
      destroy_eggs(egg, lst);
    }
  player_modif(tmp, lst, conf, team);
  return (0);
}
