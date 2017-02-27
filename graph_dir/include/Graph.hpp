//
// Graph.hpp for PSU_2015_zappy in /home/quief_h/Projets/rendu/PSU_2015_zappy
//
// Made by Hippolyte Quief
// Login   <quief_h@epitech.net>
//
// Started on  Tue Jun 14 14:01:01 2016 Hippolyte Quief
// Last update Sun Jun 26 23:33:43 2016 Lucas Parsy
//

#ifndef ZAPPY_GRAPH_HPP
#define ZAPPY_GRAPH_HPP

#define CELL_HEIGHT 62
#define CELL_WIDTH 147

#include <SFML/Graphics.hpp>
#include <vector>

//#include "../../server_dir/include/map.h"
#include "Square.hpp"

class Graph
{
private:
  int			_width;
  int			_height;

  sf::RenderWindow	_window{{1500, 1000}, "zappy client"};
  sf::View		_view;

  sf::Texture		_texCell;
  sf::Sprite		_cell;
  sf::Texture		_texResources;
  sf::Sprite		_spResources[7];

  sf::Texture		_texBackground;
  sf::Sprite		_background;
  sf::Texture		_texDescCell;
  sf::Sprite		_descCell;
  sf::Clock		_descTimer;
  sf::Text		_descText;

  sf::Texture		_texMessageBoard;
  sf::Sprite		_messageBoard;
  sf::Clock		_boardTimer;
  sf::Text		_boardText;

  bool			_newPlayer;
  bool			_isDescPlayer;
  int			_currentPlayer;
  sf::Texture		_texPlayerInfo;
  sf::Sprite		_playerInfo;
  sf::Clock		_playerInfoTimer;
  sf::Text		_playerInfoText;
  sf::Text		_playerInventoryText;

  sf::Font		_font;

  bool			_isDescCell;
  sf::Vector2i		_moveOrigin;
  bool			_clicked = false;
  bool		        _hideUnused;
  float			_zoom = 1;
  std::vector< Square >	_map;


  void	        drawPlayers(std::vector< Square* > &map,
			    std::vector< Player > &players);
  void		drawBoard(std::vector< Square* > &map);
  void	        movingHandle(sf::Event &event);
  void		inputHandle(std::vector< Square* > &map,
			    std::vector< Player > &players);
  bool		clickPlayer(std::vector< Player > &players, float x, float y);
  void		clickCell(std::vector< Square* >&map, float x, float y);
  void		clickHandle(std::vector< Square* > &map,
			  std::vector< Player > &players);
  void		playerUpdateDesc(std::vector<std::string> &teamNames,
				 std::vector< Player > &players);

public:
  Graph();
  ~Graph();

    void	setSize(int width, int height);
    void	askSizeMap();
    void	askSquareContent(int x, int y);
    void	askMapContent();
    void	askTeam();
    void	askPos(unsigned int id);
    void	askLvl(unsigned int id);
    void	askInventory(unsigned int id);
    void	askTime();
    void	askModifyTime(unsigned int time);

  bool		update(std::vector< Square* > &map,
		       std::vector< Player > &players,
		       std::vector<std::string> &teamNames);
};


#endif //ZAPPY_GRAPH_HPP
