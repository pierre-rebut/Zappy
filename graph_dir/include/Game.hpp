//
// Game.hpp for Game in /home/tuxlu/proj/PSU_2015_zappy/graph_dir
// 
// Made by Lucas Parsy
// Login   <parsy_a@epitech.net>
// 
// Started on  Sun Jun 19 02:26:25 2016 Lucas Parsy
// Last update Sat Jun 25 01:18:15 2016 Lucas Parsy
//

#ifndef ZAPPY_GAME_HPP
#define ZAPPY_GAME_HPP

#include <iostream>

#include "Network.hpp"
#include "Graph.hpp"
#include "PlayerRessources.hpp"
#include "Player.hpp"
#include "Square.hpp"

class Game
{
private:
  int			_width;
  int			_height;
  Network		_net;
  Graph			_graph;
  PlayerRessources	_playRes;
  std::vector<Player>	_players;
  std::vector<Square*>	_map;

  std::vector<std::string> _teamNames;
  sf::Texture		_texResources;
  sf::Sprite		_spResources[7];

  bool	checkArgLen(const std::vector<std::string> &tab, size_t len);
  unsigned int	myGetnbr(std::string str);

public:
  Game(int Nport, char *Nip);
  ~Game();

  void checkInput(std::string &str);
  void run();

  void msz(const std::vector<std::string> &tab);
  void bct(const std::vector<std::string> &tab);
  void tna(const std::vector<std::string> &tab);
  void pnw(const std::vector<std::string> &tab);
  void ppo(const std::vector<std::string> &tab);
  void plv(const std::vector<std::string> &tab);
  void pin(const std::vector<std::string> &tab);
  void pex(const std::vector<std::string> &tab);
  void pbc(const std::vector<std::string> &tab);
  void pic(const std::vector<std::string> &tab);
  void pie(const std::vector<std::string> &tab);
  void pfk(const std::vector<std::string> &tab);
  void pdr(const std::vector<std::string> &tab);
  void pgt(const std::vector<std::string> &tab);
  void pdi(const std::vector<std::string> &tab);
  void enw(const std::vector<std::string> &tab);
  void eht(const std::vector<std::string> &tab);
  void ebo(const std::vector<std::string> &tab);
  void edi(const std::vector<std::string> &tab);
  void smg(const std::vector<std::string> &tab);
};

#endif //ZAPPY_GAME_HPP
