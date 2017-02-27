//
// Player.cpp for PSU_2015_zappy in /home/quief_h/Projets/rendu/PSU_2015_zappy
//
// Made by Hippolyte Quief
// Login   <quief_h@epitech.net>
//
// Started on  Tue Jun 14 14:29:39 2016 Hippolyte Quief
// Last update Sat Jun 25 19:20:42 2016 Lucas Parsy
//

#include <iostream>
#include "Player.hpp"
#include "Graph.hpp"

Player::Player(unsigned int id, int x, int y, int orient, unsigned int level,
	       unsigned int id_team, bool isEgg, PlayerRessources &res):
  _id(id),
  _idTeam(id_team),
  _lvl(level),
  _cellPos(std::make_pair(x, y)),
  _orientation(orient),
  _spResources(res),
  _displayText(false),
  _isDying(false),
  _isDead(false),
  _isEgg(isEgg),
  _incantation(false)
{
  _randPos.x = rand() % (int)(7 * CELL_WIDTH / 10) + (3 * CELL_WIDTH / 10);
  _randPos.y = rand() % (int)(6 * CELL_HEIGHT / 5) + (3 * CELL_HEIGHT / 5);
  move(x, y);
  _inventory.fill("0");
}


void Player::setValues(unsigned int id, int x, int y, int orient,
		       unsigned int level, unsigned int id_team, bool isEgg)
{
  _isDying = false;
  _isDead = false;
  _isEgg = isEgg;
  _id = id;
  move(x, y, orient);
  _lvl = level;
  _idTeam = id_team;
}

Player::~Player()
{

}

void Player::setInventory(const std::vector<std::string> &tab)
{
  for (int i = 4; i < 11; i++)
    _inventory[i - 4] = tab[i];
}

void Player::move(int x, int y, int orient)
{
  _cellPos.first = x;
  _cellPos.second = y;
  _pos.x = 600 + 40 + (x - y) * CELL_WIDTH + _randPos.x;
  _pos.y = 200 - 90 + (y + x) * CELL_HEIGHT + _randPos.y;
  if (orient < 5)
    _orientation = orient;
}

void Player::draw(sf::RenderWindow &window)
{
  const std::vector<sf::Vector2f>movement = {sf::Vector2f(1, 1),
					     sf::Vector2f(1, -1),
					     sf::Vector2f(-1, -1),
					     sf::Vector2f(-1, 1)};

  if (_isDead)
    return;

  if (_incantation)
    {
      _spResources.spIncantation.setPosition(_pos);
      window.draw(_spResources.spIncantation);
    }
  else if (_isDying)
    {
      _spResources.spDead.setPosition(_pos);
      window.draw(_spResources.spDead);
    }
  else if (_isEgg)
    {
      _spResources.spEgg.setPosition(_pos);
      window.draw(_spResources.spEgg);
    }
  else
    {
      Animation &anim = (_orientation == 1 || _orientation == 4) ?
	_spResources.animMoveUp :
	_spResources.animMoveDown;

      _animation.setFlipped(_orientation % 2 == 0 ? true : false);
      _animation.setAnimation(anim);
      _animation.setPosition(_pos);
      window.draw(_animation);
    }

  if (_textTimer.getElapsedTime().asSeconds() > 2)
    {
      if (_displayText == true)
	_displayText = false;
      if (_isDying)
	_isDead = true;
    }
  if (_displayText == true)
    {
      _spResources.text.setString(_text);
      _spResources.text.setColor(_colorText);
      if (_orientation % 2 == 0)
	{
	  _spResources.text.setPosition(_pos.x + 7, _pos.y - 13);
	  _spResources.spBubble.setPosition(_pos.x + 2, _pos.y);
	}
      else
	{
	  _spResources.text.setPosition(_pos.x - 95, _pos.y - 13);
	  _spResources.spBubble.setPosition(_pos.x - 100, _pos.y);
	}
      window.draw(_spResources.spBubble);
      window.draw(_spResources.text);
    }
}

void      Player::setText(const std::string &text, sf::Color color)
{
  _text = text;
  _colorText = color;
  _displayText = true;
  _textTimer.restart();
}

void Player::expludePlayer()
{

}

void Player::doBroadcast()
{

}

void Player::startEvolution()
{
  _incantation = true;
}

void Player::endEvolution()
{
  _incantation = false;
}

void Player::layEgg()
{

}

void Player::throwItem(Item item)
{
  (void)item;
}

void Player::takeItem(Item item)
{
  (void)item;
}

void Player::playerDie()
{
_isDying = true;
_textTimer.restart();
_inventory.fill("0");
}



























