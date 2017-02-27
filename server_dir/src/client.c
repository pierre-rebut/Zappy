/*
** client.c for client in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Sat Jun 11 16:33:48 2016 Pierre Rebut
** Last update Wed Jun 22 13:55:53 2016 Pierre Rebut
*/

#include	<sys/socket.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<string.h>
#include	"client.h"
#include	"server.h"
#include	"client_display.h"
#include	"client_player.h"
#include	"check_victory.h"

int	init_client(int fd, t_client *lst)
{
  t_othercli	*new;

  new = malloc(sizeof(t_othercli));
  if (new == NULL)
    {
      shutdown(fd, SHUT_RDWR);
      close(fd);
      fprintf(stderr, "[WRN] %d: can't init client (malloc)\n", fd);
      return (-1);
    }
  new->fd = fd;
  new->prev = NULL;
  new->next = lst->lst_tmp;
  new->buff_in = init_buffer();
  new->buff_out = init_buffer();
  if (new->buff_in == NULL || new->buff_out == NULL)
    return (-1);
  if (lst->lst_tmp != NULL)
    lst->lst_tmp->prev = new;
  lst->lst_tmp = new;
  send_msg(new->buff_out, "BIENVENUE\n");
  return (0);
}

void		destroy_player(t_player *cli, t_client *lst, t_config *conf)
{
  t_elemmap	*tmp;
  t_map		*map;

  if (conf != NULL)
    {
      map = get_pos_map(conf, cli->position.x, cli->position.y);
      tmp = get_objmap(map->obj, PLAYER);
      if (tmp->prev != NULL)
	tmp->prev->next = tmp->next;
      else
	map->obj = tmp->next;
      if (tmp->next != NULL)
	tmp->next->prev = tmp->prev;
      free(tmp);
    }
  send_dl_pdi(lst, cli);
  shutdown(cli->fd, SHUT_RDWR);
  close(cli->fd);
  fprintf(stderr, "[INFO] %d: player exit\n", cli->fd);
  free_buffer(cli->buff_in);
  free_buffer(cli->buff_out);
  free(cli);
  lst->connexion --;
  if (conf != NULL)
    check_defeat(lst, conf);
}

void		destroy_othercli(t_othercli *cli, t_client *lst)
{
  shutdown(cli->fd, SHUT_RDWR);
  close(cli->fd);
  fprintf(stderr, "[INFO] %d: client exit\n", cli->fd);
  free_buffer(cli->buff_in);
  free_buffer(cli->buff_out);
  free(cli);
  lst->connexion --;
}

void		destroy_eggs(t_eggs *egg, t_client *lst)
{
  send_dl_ebo(lst, egg);
  if (egg->prev != NULL)
    egg->prev->next = egg->next;
  else
    lst->lst_eggs = egg->next;
  if (egg->next != NULL)
    egg->next->prev = egg->prev;
  free(egg);
}
