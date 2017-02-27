/*
** map.h for map in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir
** 
** Made by Pierre Rebut
** Login   <rebut_p@epitech.net>
** 
** Started on  Sat Jun 11 21:44:31 2016 Pierre Rebut
** Last update Fri Jun 17 15:17:12 2016 Pierre Rebut
*/

#ifndef		PSU_ZAPPY_MAP_H_
# define	PSU_ZAPPY_MAP_H_

# define	LIM	9
# define	DER	8
# define	SIB	10
# define	MEN	5
# define	PHI	6
# define	THY	1

enum		e_type
  {
    FOOD = 0,
    LIMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    PLAYER,
    DEFAULT
  };

typedef	struct		s_elemmap
{
  enum e_type		type;
  struct s_elemmap	*prev;
  struct s_elemmap	*next;
}			t_elemmap;

typedef	struct	s_map
{
  int		x;
  int		y;
  t_elemmap	*obj;
}		t_map;

typedef struct	s_rocks
{
  enum e_type	type;
  int		rock;
}		t_rock;

int		compte_pierre(t_elemmap *, enum e_type);

#endif
