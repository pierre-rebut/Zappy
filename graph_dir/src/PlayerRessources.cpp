//
// PlayerRessources.cpp for Zappy in /home/tuxlu/proj/PSU_2015_zappy/graph_dir
// 
// Made by Lucas Parsy
// Login   <parsy_a@epitech.net>
// 
// Started on  Wed Jun 22 17:04:51 2016 Lucas Parsy
// Last update Sun Jun 26 16:15:02 2016 Etienne Jeanmart
//

#include "PlayerRessources.hpp"

PlayerRessources::PlayerRessources()
{
  char		*tmp = NULL;

  if ((tmp = realpath("img/", NULL)) == NULL && (tmp = realpath("graph_dir/img/", NULL)) == NULL)
    throw std::runtime_error("cannot allocate memory : PlayerRessources.cpp::PlayerRessources()");

  std::string path(std::string(tmp) + "/");
  free(tmp);

  if (!_TexEgg.loadFromFile(path + "Omlete.png"))
    exit(1);
  if (!_TexPlayer.loadFromFile(path + "character.png"))
    exit(1);
  if (!_TexBubble.loadFromFile(path + "bubble.png"))
    exit(1);
  if (!_font.loadFromFile(path + "Achafexp.ttf"))
    exit(1);
  text.setFont(_font);
  text.setCharacterSize(35);
  spBubble.setTexture(_TexBubble);
  spDead.setTexture(_TexPlayer);
  spIncantation.setTexture(_TexPlayer);
  spEgg.setTexture(_TexEgg);
  spDead.setTextureRect(sf::IntRect(0, 22, 46, 69));
  spIncantation.setTextureRect(sf::IntRect(78, 25, 41, 65));
  spEgg.setTextureRect(sf::IntRect(0, 0, 30, 60));

  animEgg.setSpriteSheet(_TexEgg);
  animMoveUp.setSpriteSheet(_TexPlayer);
  animMoveDown.setSpriteSheet(_TexPlayer);
  animPickUp.setSpriteSheet(_TexPlayer);
  animPickDown.setSpriteSheet(_TexPlayer);

  animMoveUp.addFrame(sf::IntRect(477, 4, 34, 86));
  animMoveUp.addFrame(sf::IntRect(418, 4, 34, 86));
  animMoveUp.addFrame(sf::IntRect(362, 2, 34, 88));

  animMoveDown.addFrame(sf::IntRect(316, 0, 43, 90));
  animMoveDown.addFrame(sf::IntRect(257, 0, 43, 90));
  animMoveDown.addFrame(sf::IntRect(204, 0, 43, 90));
  animMoveDown.addFrame(sf::IntRect(153, 0, 43, 90));

  animPickUp.addFrame(sf::IntRect(477, 4, 34, 86));
  animPickUp.addFrame(sf::IntRect(516, 4, 37, 86));

  animPickDown.addFrame(sf::IntRect(316, 0, 43, 90));
  animPickDown.addFrame(sf::IntRect(78, 25, 41, 65));
}

PlayerRessources::~PlayerRessources()
{
}
