//
// Player.hpp for PSU_2015_zappy in /home/quief_h/Projets/rendu/PSU_2015_zappy
//
// Made by Hippolyte Quief
// Login   <quief_h@epitech.net>
//
// Started on  Tue Jun 14 14:29:45 2016 Hippolyte Quief
// Last update Sat Jun 25 18:55:27 2016 Lucas Parsy
//

#ifndef ZAPPY_PLAYER_HPP
#define ZAPPY_PLAYER_HPP

#include <array>
#include "AnimatedSprite.hpp"
#include "PlayerRessources.hpp"

enum PlayerStatus
{
    ALIVE = 0,
    DEAD,
    EGG,
    BEGIN_EVOLUTION,
    END_EVOLUTION,
    STATUSSIZE,
    STATUSERR
};

enum Item
{
    FOOD = 0,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    ITEMSIZE,
    ITEMERR
};

class Player
{
private:
    unsigned int	_id;
    unsigned int	_idTeam;
  std::array<std::string, Item::ITEMSIZE>	_inventory;
    PlayerStatus	_status;
    unsigned int	_lvl;
    std::pair< int, int >	_cellPos;
  sf::Vector2f		_pos;
  sf::Vector2f		_randPos;
  int			_orientation;
  PlayerRessources	&_spResources;
  std::string		_text;
  sf::Color		_colorText;
  sf::Clock		_textTimer;
  bool			_displayText;
  AnimatedSprite	_animation;
  bool			_isDying;
  bool			_isDead;
  bool			_isEgg;
  bool			_incantation;

public:
    Player(unsigned int id, int x, int y, int orient, unsigned int level,
	   unsigned int id_team, bool isEgg, PlayerRessources &res);
    ~Player();

    inline unsigned int		getId() const { return _id; };
    inline unsigned int		getTeam() const { return _idTeam; };
  inline std::array<std::string, Item::ITEMSIZE > &getInventory() {
    return _inventory;
  };
    inline PlayerStatus		getPlayerStatus() const { return _status; };
    inline unsigned int		getLvl() const { return _lvl; };
    inline void		setLvl(unsigned int lvl)  { _lvl = lvl; };
    inline std::pair< int, int >	&getCellPos() { return _cellPos; } ;
    inline const sf::Vector2f	&getPos() { return _pos; } ;
    inline int		getOrientation() const { return _orientation; };
    inline bool		isDead() const { return _isDead; };
  inline bool		isEgg() const { return _isEgg; };



  void		setValues(unsigned int id, int x, int y, int orient,
			  unsigned int level, unsigned int id_team,
			  bool isEgg);
  void		setInventory(const std::vector<std::string> &tab);
    void	setText(const std::string &text,
		sf::Color color = sf::Color::Black);
    void	draw(sf::RenderWindow &window);
    void	expludePlayer();
    void	doBroadcast();
    void	startEvolution();
    void	endEvolution();
    void	layEgg();
    void	throwItem(Item item);
    void	takeItem(Item item);
    void	move(int x, int y, int orient=5);
    void playerDie();
};


#endif //ZAPPY_PLAYER_HPP
