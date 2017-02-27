//
// Square.hpp for PSU_2015_zappy in /home/quief_h/Projets/rendu/PSU_2015_zappy
//
// Made by Hippolyte Quief
// Login   <quief_h@epitech.net>
//
// Started on  Tue Jun 14 14:24:13 2016 Hippolyte Quief
// Last update Tue Jun 21 17:18:13 2016 Lucas Parsy
//

#ifndef ZAPPY_SQUARE_HPP
#define ZAPPY_SQUARE_HPP

#define CELL_HEIGHT 62
#define CELL_WIDTH 147

#include <SFML/Graphics.hpp>

//#include "../../server_dir/include/map.h"
#include "Player.hpp"

#include <vector>
#include <array>

class Square
{
private:
  int _x;
  int _y;
  int _resources[7];
  int _mapResources[9];

public:
  Square(int x, int y, int (&resources)[7]);
    ~Square();

  std::string getResources();
  void setResources(int (&resources)[7]);
  void pickResource(int pos);
  void addResource(int pos);
  void drawCell(sf::RenderWindow &win, sf::Sprite (&sprites)[7],
	        const sf::Vector2f &pos);
};


#endif //ZAPPY_SQUARE_HPP
