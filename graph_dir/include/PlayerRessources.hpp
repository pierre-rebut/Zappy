//
// PlayerRessources.hpp for Zappy in /home/tuxlu/proj/PSU_2015_zappy/graph_dir
// 
// Made by Lucas Parsy
// Login   <parsy_a@epitech.net>
// 
// Started on  Wed Jun 22 16:59:47 2016 Lucas Parsy
// Last update Thu Jun 23 01:21:51 2016 Lucas Parsy
//

#ifndef ZAPPY_PLAYERRESOURCES_HPP
#define ZAPPY_PLAYERRESOURCES_HPP

#include "Animation.hpp"
#include <SFML/Graphics.hpp>

class PlayerRessources
{
  sf::Texture	_TexPlayer;
  sf::Texture	_TexEgg;
  sf::Texture	_TexBubble;
  sf::Font	_font;

public:
  sf::Sprite	spBubble;
  sf::Text	text;
  sf::Sprite	spIncantation;
  sf::Sprite	spDead;
  sf::Sprite	spEgg;
  Animation	animEgg;
  Animation	animMoveUp;
  Animation	animMoveDown;
  Animation	animPickUp;
  Animation	animPickDown;

  PlayerRessources();
  ~PlayerRessources();
};

#endif /*ZAPPY_PLAYERRESOURCES_HPP*/
