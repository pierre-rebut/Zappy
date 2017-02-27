//
// Square.cpp for PSU_2015_zappy in /home/quief_h/Projets/rendu/PSU_2015_zappy
//
// Made by Hippolyte Quief
// Login   <quief_h@epitech.net>
//
// Started on  Tue Jun 14 14:23:57 2016 Hippolyte Quief
// Last update Tue Jun 21 17:07:40 2016 Lucas Parsy
//

#include <iostream>
#include <string.h>
#include <cstdlib>
#include <sstream>

#include "Square.hpp"

Square::Square(int x, int y, int (&resources)[7]) :
  _x(x),
  _y(y)
{
  int pos;

  for (int i = 0; i < Item::ITEMSIZE; i++)
    {
      _resources[i] = resources[i];
    }
  for (int i = 0; i < 9; i++)
    _mapResources[i] = 10;
  pos = rand() % 9;
  for (int i = 0; i < 7; i++)
  {
    _mapResources[pos] = i;
    pos += 1;
    if (pos == 9)
      pos = 0;
  }

}

std::string Square::getResources()
{
  const std::string space = "        ";
  std::string str;

  str = std::to_string(_resources[0]) + space +
    std::to_string(_resources[1]) + "         " +
    std::to_string(_resources[2]) + space +
    std::to_string(_resources[3]) + space + "  " +
    std::to_string(_resources[4]) + space +
    std::to_string(_resources[5]) + space +
    std::to_string(_resources[6]);
  return str;
}

void Square::setResources(int (&resources)[7])
{
  for (int i = 0; i < Item::ITEMSIZE; i++)
    _resources[i] = resources[i];
}

void Square::pickResource(int pos)
{
  if (_resources[pos] > 0)
    _resources[pos]--;
}

void Square::addResource(int pos)
{
  _resources[pos]++;
}

void Square::drawCell(sf::RenderWindow &win, sf::Sprite (&sprites)[7],
		      const sf::Vector2f &pos)
{
  int x;
  int y;
  int elem;
  for (int i = 0; i < 9; i++)
  {
    if (_mapResources[i] == 10 || _resources[_mapResources[i]] == 0)
      continue;
    elem = _mapResources[i];
    x = i / 3;
  y = i % 3;
  sprites[elem].setPosition(pos.x + CELL_WIDTH + (x - y) * (CELL_WIDTH / 3),
			 pos.y + (x + y) * (CELL_HEIGHT / 3));
  win.draw(sprites[elem]);
      //std::cout << "drawing: " << _sprites[pos].getPosition().x << "  " <<
      //_sprites[pos].getPosition().y << std::endl;
  }
}

Square::~Square()
{

}



