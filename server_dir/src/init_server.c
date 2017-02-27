/*
** init_server.c for init_server in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir/src
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Sat Jun 11 16:15:49 2016 Pierre Rebut
** Last update Mon Jun 20 18:14:34 2016 Pierre Rebut
*/

#include	<sys/socket.h>
#include	<arpa/inet.h>
#include	<netdb.h>
#include	<stdio.h>
#include	<unistd.h>
#include	<stdlib.h>
#include	"client.h"

int			init_socket(int port)
{
  int			server;
  int			tmp;
  struct protoent	*pe;
  struct sockaddr_in	serverinfo;

  if (!(pe = getprotobyname("TCP")))
    return (-1);
  server = socket(AF_INET, SOCK_STREAM, pe->p_proto);
  if (server < 0)
    return (-2);
  serverinfo.sin_family = AF_INET;
  serverinfo.sin_addr.s_addr = INADDR_ANY;
  serverinfo.sin_port = htons(port);
  tmp = 1;
  setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &tmp, sizeof(int));
  if (bind(server, (const struct sockaddr*)&serverinfo,
	   sizeof(serverinfo)) < 0)
    return (-3);
  listen(server, 42);
  return (server);
}

void			error_socket(int error)
{
  if (error == -1)
    fprintf(stderr, "Error: server: can't init proto\n");
  else if (error == -2)
    fprintf(stderr, "Error: server: can't init socket\n");
  else if (error == -3)
    fprintf(stderr, "Error: server: can't bind socket\n");
  else
    fprintf(stderr, "Error: server: un error occured\n");
}

void			close_socket(int server, t_client *cli)
{
  t_othercli		*tmp;
  t_player		*tmp2;

  while (cli->lst_player != NULL)
    {
      tmp2 = cli->lst_player->next;
      destroy_player(cli->lst_player, cli, NULL);
      cli->lst_player = tmp2;
    }
  while (cli->lst_display != NULL)
    {
      tmp = cli->lst_display->next;
      destroy_othercli(cli->lst_display, cli);
      cli->lst_display = tmp;
    }
  while (cli->lst_tmp != NULL)
    {
      tmp = cli->lst_tmp->next;
      destroy_othercli(cli->lst_tmp, cli);
      cli->lst_tmp = tmp;
    }
  free(cli);
  shutdown(server, SHUT_RDWR);
  close(server);
}
