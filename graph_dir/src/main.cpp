
//
// main.cpp for PSU_2015_zappy in /home/quief_h/Projets/rendu/PSU_2015_zappy
//
// Made by Hippolyte Quief
// Login   <quief_h@epitech.net>
//
// Started on  Thu Jun 09 13:37:58 2016 Hippolyte Quief
// Last update Sun Jun 19 13:09:48 2016 Lucas Parsy
//

#include <cstdlib>
#include <stdlib.h>
#include "Game.hpp"

static void	printUsage()
{
  std::cout << "usage: ./server [--help] ip port" << std::endl;
}

static int	parsing(char **av)
{
  size_t	i = 0;

  while (av[i])
  {
    std::string	tmp(av[i]);
    if (!tmp.compare("--help") || !tmp.compare("-h"))
    {
      printUsage();
      std::cout << "\tip :\tip to connect the client to the server\n" << std::endl;
      std::cout << "\tport :\tport to connect the client to the server\n" << std::endl;
      return -1;
    }
    i++;
  }
  if (i != 3)
  {
    printUsage();
    return (-1);
  }
  return (0);
}

int		main(int ac, char **av)
{
  (void)ac;
  if (parsing(av))
    return (-1);
  srand(time(NULL));
  try {
    std::string	tmp(av[2]);
    Game  game(std::stoi(tmp), av[1]);
    game.run();
  } catch(std::exception const & e) {
    std::cout << "error : " << e.what() << std::endl;
  }
}
