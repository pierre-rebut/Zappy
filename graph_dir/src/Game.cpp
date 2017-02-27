//
// Game.cpp for Zappy in /home/tuxlu/proj/PSU_2015_zappy/graph_dir
// 
// Made by Lucas Parsy
// Login   <parsy_a@epitech.net>
// 
// Started on  Sun Jun 19 02:33:35 2016 Lucas Parsy
// Last update Sat Jun 25 19:11:22 2016 Lucas Parsy
//

#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

#include "Game.hpp"

unsigned int  Game::myGetnbr(std::string str)
{
  if (str[0] == '#')
    str = str.substr(1);
  unsigned int nbr;
  try
    {
      nbr = std::stoul(str);
    }
  catch (...)
    {
      return 0;
    }
  return nbr;
}

bool Game::checkArgLen(const std::vector<std::string> &tab, size_t len)
{
  if (tab.size() < len + 1)
    return true;
  return false;
}

void		Game::checkInput(std::string &str)
{
  const std::string funcNames[] = {"msz", "bct", "tna", "pnw", "ppo",
				   "plv", "pin", "pex", "pbc", "pie",
				   "pic", "pfk", "pdr", "pgt", "pdi",
				   "enw", "eht", "ebo", "edi", "smg"};


  void (Game::*functions[]) (const std::vector<std::string>&) =
    {
      &Game::msz, &Game::bct,  &Game::tna, &Game::pnw, &Game::ppo,
      &Game::plv, &Game::pin, &Game::pex, &Game::pbc, &Game::pie,
      &Game::pic, &Game::pfk, &Game::pdr, &Game::pgt, &Game::pdi,
      &Game::enw, &Game::eht, &Game::ebo, &Game::edi, &Game::smg
    };

  std::istringstream stream(str);
  std::vector<std::string> splitted{std::istream_iterator<std::string>{stream},
      std::istream_iterator<std::string>{}};

  for (int i = 0; i < 18; i++)
    {
      if (splitted.front() == funcNames[i])
	(this->*functions[i])(splitted);
    }
}


Game::Game(int Nport, char *Nip) : _net(Nport, Nip)
{
  this->_map.resize(2, NULL);
}

Game::~Game()
{
  for (auto it = _map.begin(); it != _map.end(); it++)
    delete(*it);
}

void Game::run()
{
  std::string str;

  while (this->_graph.update(this->_map, this->_players, this->_teamNames)
	 != false)
    {
      str = this->_net.read();
      if (!str.empty())
	{
	  std::cout << str << std::endl;
	  checkInput(str);
	}
    }
}

void Game::msz(const std::vector<std::string> &tab)
{
  if (checkArgLen(tab, 2))
    return;

  try
    {
      _width = std::stoi(tab.at(1));
      _height = std::stoi(tab.at(2));
    }
  catch (...)
    {
      return;
    }
  this->_graph.setSize(_width, _height);
  this->_map.resize(_width * _height, NULL);
}

void Game::bct(const std::vector<std::string> &tab)
{
  if (checkArgLen(tab, 9))
    return;

  int resources[7];
  int x;
  int y;
  try
    {
      x = std::stoi(tab[1]);
      y = std::stoi(tab[2]);
      for (int i = 3; i <= 9; i++)
	resources[i - 3] = std::stoi(tab[i]);
    }
  catch (...)
    {
      return;
    }
  if (x * _width + y < static_cast<int>(_map.size()))
    {
      if (_map[x * _width + y] == NULL)
	_map[x * _width + y] = new Square(x, y, resources);
      else
	_map[x * _width + y]->setResources(resources);
    }
}

void Game::tna(const std::vector<std::string> &tab)
{
  if (checkArgLen(tab, 1))
    return;
  for (auto it = _teamNames.begin(); it != _teamNames.end(); it++)
    if (*it == tab[1])
      return;
  _teamNames.push_back(tab[1]);
}

void Game::pnw(const std::vector<std::string> &tab)
{
  if (checkArgLen(tab, 6))
    return;
  unsigned int id = myGetnbr(tab[1]);
  unsigned int x = myGetnbr(tab[2]);
  unsigned int y = myGetnbr(tab[3]);
  unsigned int orient = myGetnbr(tab[4]);
  unsigned int level = myGetnbr(tab[5]);
  unsigned int teamId = 0;
  for (auto it = _teamNames.begin(); it != _teamNames.end(); it++)
    {
      if (*it == tab[6])
	break;
      teamId++;
    }

  if (teamId >= _teamNames.size())
    {
      std::cout << "invalid team name " << tab[6] << std::endl;
      return;
    }

    for (auto it = _players.begin(); it != _players.end(); it++)
    if ((*it).getId() == id && (*it).isEgg() == true)
      {
	(*it).setValues(id, x, y, orient, level, teamId, false);
	return;
      }

  for (auto it = _players.begin(); it != _players.end(); it++)
    if ((*it).getId() == id && (*it).isDead() == false)
      {
	std::cout << "player " << id << " already exists" << std::endl;
	return;
      }
  for (auto it = _players.begin(); it != _players.end(); it++)
    if ((*it).isDead() == true || (*it).isEgg() == true)
      {
	(*it).setValues(id, x, y, orient, level, teamId, false);
	return;
      }
  _players.push_back(Player(id, x, y, orient, level, teamId, false, _playRes));
}

void Game::ppo(const std::vector<std::string> &tab)
{
  if (checkArgLen(tab, 4))
    return;
  unsigned int id = myGetnbr(tab[1]);
  unsigned int x = myGetnbr(tab[2]);
  unsigned int y = myGetnbr(tab[3]);
  unsigned int orient = myGetnbr(tab[4]);

  for (auto it = _players.begin(); it != _players.end(); it++)
    if ((*it).getId() == id)
      {
	(*it).move(x, y, orient);
	return;
      }
  std::cout << "player " << id << " doesnt exists" << std::endl;
}

void Game::plv(const std::vector<std::string> &tab)
{
  const sf::Color col(11, 182, 25);

  if (checkArgLen(tab, 2))
    return;
  unsigned int id = myGetnbr(tab[1]);
  unsigned int lvl = myGetnbr(tab[2]);

  for (auto it = _players.begin(); it != _players.end(); it++)
    if ((*it).getId() == id)
      {
	(*it).setLvl(lvl);
	(*it).setText("level " + std::to_string(lvl), col);
	return;
      }
  std::cout << "player " << id << " doesnt exists" << std::endl;
}

void Game::pin(const std::vector<std::string> &tab)
{
  if (checkArgLen(tab, 10))
    return;

  unsigned int id = myGetnbr(tab[1]);
  unsigned int x = myGetnbr(tab[2]);
  unsigned int y = myGetnbr(tab[3]);

  for (auto it = _players.begin(); it != _players.end(); it++)
    if ((*it).getId() == id)
      {
	(*it).move(x, y);
	(*it).setInventory(tab);
	return;
      }
  std::cout << "player " << id << " doesnt exists" << std::endl;
}

void Game::pex(const std::vector<std::string> &tab)
{
  if (checkArgLen(tab, 1))
    return;

  unsigned int id = myGetnbr(tab[1]);
  for (auto it = _players.begin(); it != _players.end(); it++)
    if ((*it).getId() == id)
      {
	(*it).setText("expulsion!", sf::Color::Red);
	return;
      }
  std::cout << "player " << id << " doesnt exists" << std::endl;

}

void Game::pbc(const std::vector<std::string> &tab)
{
  if (checkArgLen(tab, 2))
    return;
  unsigned int id = myGetnbr(tab[1]);
  std::string str;

  for (unsigned int i = 2; i < tab.size(); i++)
    str += tab[i] + " ";

  if (str.length() > 12)
    str = str.substr(0, 12) + "...";
  for (auto it = _players.begin(); it != _players.end(); it++)
    if ((*it).getId() == id)
      {
	(*it).setText(str);
	return;
      }
  std::cout << "player " << id << " doesnt exists" << std::endl;

}

void Game::pic(const std::vector<std::string> &tab)
{
  if (checkArgLen(tab, 4))
    return;

  unsigned int id;

  for (unsigned int i = 4; i < tab.size(); i++)
    {
      id = myGetnbr(tab[i]);
      for (auto it = _players.begin(); it != _players.end(); it++)
	if ((*it).getId() == id)
	  {
	    if (i == 4)
	      (*it).setText("incantation!");
	    (*it).startEvolution();
	    break;
	  }
      std::cout << "player " << id << " doesnt exists" << std::endl;
    }
}


void Game::pie(const std::vector<std::string> &tab)
{
  if (checkArgLen(tab, 3))
    return;

  int x, y;
  std::pair< int, int > pos;
  x = myGetnbr(tab[1]);
  y = myGetnbr(tab[2]);
  for (auto it = _players.begin(); it != _players.end(); it++)
    {
      pos = (*it).getCellPos();
      if (pos.first == x && pos.second == y)
	(*it).endEvolution();
    }
}

void Game::pfk(const std::vector<std::string> &tab)
{
  if (checkArgLen(tab, 1))
    return;
}

void Game::pdr(const std::vector<std::string> &tab)
{
  if (checkArgLen(tab, 2))
    return;
}

void Game::pgt(const std::vector<std::string> &tab)
{
  if (checkArgLen(tab, 2))
    return;
}

void Game::pdi(const std::vector<std::string> &tab)
{
  if (checkArgLen(tab, 1))
    return;
  unsigned int id = myGetnbr(tab[1]);

  for (auto it = _players.begin(); it != _players.end(); it++)
    if ((*it).getId() == id)
    {
      (*it).playerDie();
      std::cout << "player " << id << " is dead" << std::endl;
      return;
    }
  std::cout << "player " << id << " doesnt exists" << std::endl;
}

void Game::enw(const std::vector<std::string> &tab)
{
  if (checkArgLen(tab, 4))
    return;

 unsigned int id = myGetnbr(tab[1]);
 unsigned int play = myGetnbr(tab[2]);
  unsigned int x = myGetnbr(tab[3]);
  unsigned int y = myGetnbr(tab[4]);
  unsigned int team = 100000;

  for (auto it = _players.begin(); it != _players.end(); it++)
    if ((*it).getId() == play)
      {
	team = (*it).getTeam();
	(*it).setText("cot cot!");
      }

  for (auto it = _players.begin(); it != _players.end(); it++)
    if ((*it).isDead() == true)
      {
	(*it).setValues(id, x, y, 1, 0, team, true);
	return;
      }
  _players.push_back(Player(id, x, y, 1, 0, team, true, _playRes));
}

void Game::eht(const std::vector<std::string> &tab)
{
  if (checkArgLen(tab, 1))
    return;
}

void Game::ebo(const std::vector<std::string> &tab)
{
  if (checkArgLen(tab, 1))
    return;
}

void Game::edi(const std::vector<std::string> &tab)
{
  if (checkArgLen(tab, 1))
    return;

  unsigned int id = myGetnbr(tab[1]);
  for (auto it = _players.begin(); it != _players.end(); it++)
    if ((*it).getId() == id)
    {
      (*it).playerDie();
      (*it).setText("Egg died!", sf::Color::Red);
      return;
    }
  std::cout << "player " << id << " doesnt exists" << std::endl;

}

void Game::smg(const std::vector<std::string> &tab)
{
  if (checkArgLen(tab, 1))
    return;
}
