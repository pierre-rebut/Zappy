/*
** timeout.c for timeout in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Wed Jun 22 17:53:02 2016 Pierre Rebut
** Last update Thu Jun 23 11:54:42 2016 Pierre Rebut
*/

#include	<time.h>
#include	<sys/time.h>
#include	"config.h"

bool		check_timeout(t_config *conf, struct timeval *start,
			      double limit)
{
  long		sec;
  long		usec;

  sec = (long)limit;
  usec = (long)(limit * 1000000) - (sec * 1000000);
  if (conf->time.tv_sec > start->tv_sec + sec)
    return (true);
  else if (conf->time.tv_sec < start->tv_sec + sec)
    return (false);
  if (conf->time.tv_usec >= start->tv_usec + usec)
    return (true);
  return (false);
}

void		set_timeout_value(t_config *conf)
{
  long		usec;

  if (conf->timeout.tv_sec == 0 && conf->timeout.tv_usec == 0)
    {
      usec = (1 / (double)conf->u_time) * 1000000;
      if (usec <= 10000 && usec >= 10)
	conf->timeout.tv_usec = usec;
      else if (usec > 10000)
	conf->timeout.tv_usec = 10000;
      else
	conf->timeout.tv_usec = 10;
    }
  gettimeofday(&conf->time, NULL);
}
