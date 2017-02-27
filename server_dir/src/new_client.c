/*
** new_client.c for client in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir/src
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Sat Jun 11 18:05:01 2016 Pierre Rebut
** Last update Sat Jun 18 15:59:27 2016 Pierre Rebut
*/

#include		<unistd.h>
#include		<arpa/inet.h>
#include		<netdb.h>
#include		<sys/socket.h>
#include		<stdio.h>
#include		"client.h"

void			new_client(int server, t_client *lst)
{
  int			fd;
  int			res;
  socklen_t		len;
  struct sockaddr_in	clientinfo;

  len = sizeof(struct sockaddr_in);
  fd = accept(server, (struct sockaddr*)&clientinfo, &len);
  if (fd < 0)
    {
      fprintf(stderr, "[WRN] can't init client (connexion failed)\n");
      return ;
    }
  if (lst->connexion >= 1024)
    {
      fprintf(stderr, "[WRN] Too much connexion: must close\n");
      shutdown(fd, SHUT_RDWR);
      close(fd);
      return ;
    }
  lst->connexion ++;
  res = init_client(fd, lst);
  if (res == 0)
    fprintf(stderr, "[INFO] new connexion: %d\n", fd);
}
