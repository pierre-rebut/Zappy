//
// Graph.cpp for PSU_2015_zappy in /home/quief_h/Projets/rendu/PSU_2015_zappy
//
// Made by Hippolyte Quief
// Login   <quief_h@epitech.net>
//
// Started on  Tue Jun 14 14:00:09 2016 Hippolyte Quief
// Last update Sun Jun 26 23:37:25 2016 Lucas Parsy
//


#include <limits.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <cmath>
#include <unistd.h>

#include <exception>

#include "Graph.hpp"


void Graph::drawPlayers(std::vector< Square* > &map,
			std::vector< Player > &players)
{
  for (auto it = players.begin(); it != players.end(); it++)
    (*it).draw(this->_window);
  (void)map;
}

void Graph::drawBoard(std::vector< Square* > &map)
{
  const sf::Vector2f &viewPos = this->_window.getView().getCenter();
  const sf::Vector2f &viewSize = this->_window.getView().getSize();
  sf::Vector2f pos;

  for (int x = 0; x < this->_width; x++)
    {
      for (int y = 0; y < this->_height; y++)
	{
	  pos = this->_cell.getPosition();
	  if (this->_hideUnused == false ||
	      ((pos.x  + (CELL_HEIGHT * 5) > viewPos.x - (viewSize.x / 2)) &&
	       (pos.y + (CELL_HEIGHT * 3) > viewPos.y - (viewSize.y / 2) &&
		pos.y < viewPos.y + (viewSize.y / 2))))
	    {
	      this->_window.draw(this->_cell);
	      if (map[x * this->_width + y] != NULL)
		map[x * this->_width + y]->drawCell(this->_window,
						    this->_spResources,
						    this->_cell.getPosition());
	    }
	  this->_cell.move(-CELL_WIDTH, CELL_HEIGHT);
	}
      this->_cell.move(CELL_WIDTH * (this->_height + 1),
		       -CELL_HEIGHT * (this->_height - 1));
    }
  this->_cell.move(-CELL_WIDTH * this->_width, -CELL_HEIGHT * this->_width);
}

void Graph::movingHandle(sf::Event &event)
{
  switch(event.type)
    {
    case sf::Event::MouseMoved:
      {
	if(this->_clicked == true)
	  {
	    sf::Vector2f center =
	      sf::Vector2f(sf::Mouse::getPosition(this->_window) -
			   this->_moveOrigin);
	    this->_view.move(-1.0f * center * this->_zoom);
	    this->_moveOrigin = sf::Mouse::getPosition(this->_window);
	  }
	break;
      }
    case sf::Event::MouseButtonPressed:
      {
	if(event.mouseButton.button == sf::Mouse::Middle)
	  {
	    if(this->_clicked != true)
	      {
		this->_clicked = true;
		this->_moveOrigin = sf::Mouse::getPosition(this->_window);
	      }
	  }
	break;
      }
    case sf::Event::MouseButtonReleased:
      {
	if(event.mouseButton.button == sf::Mouse::Middle)
	  this->_clicked = false;
	break;
      }
    case sf::Event::MouseWheelMoved:
      {
	if(event.mouseWheel.delta < 0)
	  {
	    this->_view.zoom(2.0f);
	    this->_zoom *= 2.0f;
	  }
	else
	  {
	    this->_view.zoom(0.5f);
	    this->_zoom *= 0.5f;
	  }
      default:
	break;
      }
    }
}


void Graph::playerUpdateDesc(std::vector<std::string> &teamNames,
			     std::vector< Player > &players)
{
  if (_newPlayer == true ||
      (_playerInfoTimer.getElapsedTime().asSeconds() > 1 &&
       _currentPlayer != -1 && _currentPlayer < (int)players.size()))
    {
      if(players[_currentPlayer].isDead() == true)
	{
	  _isDescPlayer = false;
	  return;
	}
	if (_newPlayer == true)
	_newPlayer = false;
      _playerInfoTimer.restart();
      unsigned int teamNumber;
      unsigned int level = players[_currentPlayer].getLvl();
      std::array< std::string, Item::ITEMSIZE> &inventory =
        players[_currentPlayer].getInventory();
      std::string teamName;
      teamNumber = players[_currentPlayer].getTeam();
      if (teamNumber >= teamNames.size())
	teamName = "???";
      else
	{
	  teamName = teamNames[teamNumber];
	  std::transform(teamName.begin(), teamName.end(),
			 teamName.begin(), ::toupper);
	}
      _playerInfoText.setString(teamName + "\n "
				+ std::to_string(level) + "\n" +
				inventory[0]);
      std::string strInvent;
      for (int i = 0; i < 6; i++)
	{
	  strInvent += inventory[i + 1];
	  if (i == 2)
	    strInvent += '\n';
	  else
	    strInvent += std::string(7 - inventory[i + 1].length(), ' ');
	}
      _playerInventoryText.setString(strInvent);
    }
}


bool Graph::clickPlayer(std::vector< Player > &players, float x, float y)
{
  sf::Vector2f playerPos;
  int i = 0;

  for (auto it = players.begin(); it != players.end(); it++)
    {
      if ((*it).isDead() == false)
	{
	  playerPos = (*it).getPos();
	  if ((*it).getOrientation() % 2 == 0)
	    playerPos.x -= 35;
	  if (y > playerPos.y && y < playerPos.y + 85 &&
	      x > playerPos.x && x < playerPos.x + 35)
	    {
	      _currentPlayer  = i;
	      _isDescPlayer = true;
	      _newPlayer = true;
	      _playerInfoTimer.restart();
	      return true;
	    }
	}
      i++;
    }
  return false;
}

void Graph::clickCell(std::vector< Square* >&map, float x, float y)
{

  float retx, rety;
  int posx, posy;

  x += -(CELL_WIDTH / 2) - 600;
  y += (CELL_HEIGHT / 2) - 200;
  x = x /  CELL_WIDTH;
  y = y /  CELL_HEIGHT;
  y = (y - x) / 2;
  x += y;
  retx = x - (int)x;
  rety = y - (int)y;
  if ((retx > 0.85 || retx < 0.15) && (rety < 0.15 || rety > 0.85))
    return;
  posx = (int)x - 1;
  if (retx > 0.5)
    posx++;
  posy = (int)y;
  if (posy < 0 || posx < 0 || posx >= _width || posy >= _height ||
      map[x * _height + y] == NULL)
    return;
  _isDescCell = true;
  _isDescPlayer = false;
  _descTimer.restart();
  _descText.setPosition(430, 32);
  _descText.setColor(sf::Color::Black);
  _descText.setString(map[posx * _height + posy]->getResources());
  _descText.setCharacterSize(40);
}

void Graph::clickHandle(std::vector< Square* > &map,
			std::vector< Player > &players)
{
  const sf::Vector2i pos = sf::Mouse::getPosition(this->_window);
  const sf::Vector2f size = this->_window.getView().getSize();
  const sf::Vector2f &viewPos = this->_window.getView().getCenter();
  float x, y;

  x = (pos.x + viewPos.x - (size.x / 2) / _zoom) +
       (pos.x - 750) * (_zoom - 1);
  y = (pos.y + viewPos.y - (size.y / 2) / _zoom) +
       (pos.y - 500) * (_zoom - 1);
  if (clickPlayer(players, x, y) == false)
    {
      clickCell(map, x, y);
    }
}

void Graph::inputHandle(std::vector< Square* > &map,
			std::vector< Player > &players)
{
  sf::Event event;
  while (this->_window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed ||
	  sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	this->_window.close();

      if (event.type == sf::Event::MouseButtonPressed &&
	  event.mouseButton.button == sf::Mouse::Left)
	clickHandle(map, players);
      movingHandle(event);
    }
}

bool Graph::update(std::vector< Square* > &map,
		   std::vector< Player > &players,
		   std::vector<std::string> &teamNames)
{
  if (!this->_window.isOpen())
    return false;

  this->_window.clear();
  this->_window.draw(this->_background);
  this->_window.setView(this->_view);
  inputHandle(map, players);
  drawBoard(map);
  drawPlayers(map, players);

  this->_window.setView(this->_window.getDefaultView());
  if (_isDescCell == true &&
      _descTimer.getElapsedTime().asSeconds() > 5)
    _isDescCell = false;
  if (_isDescCell == true)
    {
      this->_window.draw(this->_descCell);
      this->_window.draw(this->_descText);
    }

  if (_isDescPlayer)
    {
      playerUpdateDesc(teamNames, players);
      this->_window.draw(this->_playerInfo);
      this->_window.draw(_playerInfoText);
      this->_window.draw(_playerInventoryText);
    }
  this->_window.display();
  return true;
}

Graph::Graph()
{
  char		*tmp = NULL;

  if ((tmp = realpath("img/", NULL)) == NULL && (tmp = realpath("graph_dir/img/", NULL)) == NULL)
    throw std::runtime_error("cannot allocate memory : Graph.cpp::Graph()");

  std::string path(std::string(tmp) + "/");
  free(tmp);

  if (!this->_texCell.loadFromFile(path + "cell.png"))
    exit(1);
  if (!_font.loadFromFile(path + "Achafexp.ttf"))
    exit(1);
  _descText.setFont(_font);
  _playerInfoText.setFont(_font);
  _playerInventoryText.setFont(_font);
  _playerInfoText.setStyle(sf::Text::Bold);
  _playerInfoText.setPosition(1360, 825);
  _playerInfoText.setColor(sf::Color::Black);
  _playerInfoText.setCharacterSize(17);
  _playerInfoText.setString("LEL\n 42\n7890");

  _playerInventoryText.setStyle(sf::Text::Bold);
  _playerInventoryText.setPosition(1340, 930);
  _playerInventoryText.setColor(sf::Color::Red);
  _playerInventoryText.setCharacterSize(30);

  this->_cell.setTexture(this->_texCell);
  this->_cell.setPosition(600, 200);


    if (!this->_texBackground.loadFromFile(path + "background.jpg"))
    exit(1);
  this->_background.setTexture(this->_texBackground);
  this->_descCell.setPosition(0, 0);

  if (!this->_texDescCell.loadFromFile(path + "cell_desc.png"))
    exit(1);
  this->_descCell.setTexture(this->_texDescCell);
  this->_descCell.setPosition(350, 0);

  if (!this->_texPlayerInfo.loadFromFile(path + "character_desc.png"))
    exit(1);
  _playerInfo.setTexture(this->_texPlayerInfo);
  _playerInfo.setPosition(1278, 650);
  //if (!this->_texMessageBoard.loadFromFile(path + "message_board.png"))
  //exit(1);
  //this->_messageBoard.setTexture(this->_texMessageBoard);
  //this->_messageBoard.setPosition(0, 650);



  this->_window.setFramerateLimit(30);
  this->_view = this->_window.getDefaultView();
  this->_width = 1;
  this->_height = 1;
  this->_hideUnused = true;


  if (!this->_texResources.loadFromFile(path + "orbs.png"))
    exit(1);
  for (int i = 0; i < Item::ITEMSIZE; i++)
    this->_spResources[i].setTexture(this->_texResources);
  this->_spResources[0].setTextureRect(sf::IntRect(12, 3, 120, 160));
  this->_spResources[1].setTextureRect(sf::IntRect(155, 11, 105, 152));
  this->_spResources[2].setTextureRect(sf::IntRect(286, 6, 117, 161));
  this->_spResources[3].setTextureRect(sf::IntRect(422, 10, 120, 160));
  this->_spResources[4].setTextureRect(sf::IntRect(11, 211, 120, 160));
  this->_spResources[5].setTextureRect(sf::IntRect(172, 215, 120, 160));
  this->_spResources[6].setTextureRect(sf::IntRect(310, 203, 120, 160));

  for (int i = 0; i < Item::ITEMSIZE; i++)
    this->_spResources[i].scale(sf::Vector2f(0.2f, 0.2f));

  _currentPlayer = -1;
  _isDescCell = false;
  _isDescPlayer = false;
  _newPlayer = false;

}

Graph::~Graph()
{

}


void	Graph::setSize(int width, int height)
{
  this->_width = width;
  this->_height = height;
  this->_hideUnused = (this->_width * this->_height > 30) ? true : false;
}
