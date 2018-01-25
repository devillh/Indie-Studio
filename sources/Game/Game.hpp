//
// Game.hpp for Indie Studio in /home/devill_h/back_up/rendu/cpp_indie_studio/sources/Game
// 
// Made by Héloïse de Villepin
// Login   <devill_h@epitech.net>
// 
// Started on  Mon Jun 12 11:11:07 2017 Héloïse de Villepin
// Last update Sun Jun 18 18:17:40 2017 Héloïse de Villepin
//

#ifndef				_GAME_HPP_
# define			_GAME_HPP_
# include			<irrlicht.h>
# include			<vector>
# include			"Character.hpp"
# include			"Map.hpp"


class				Game
{
public:
  bool				isPlayerDead(unsigned int i) const;
  void				generateMapAndPlayers();
  void				running();

  Game(int const &, int const &, irr::IrrlichtDevice *,
       irr::video::IVideoDriver *, EventManager &,
       Map &, int const &, irr::scene::ISceneManager *);
  ~Game();
private:
  int				_nbPlayers;
  int				_height;
  int				_width;
  Map				&_map;
  irr::IrrlichtDevice		*_device;
  irr::video::IVideoDriver	*_driver;
  irr::scene::ISceneManager	*_sceneManager;
  EventManager			&_receiver;
  std::vector<Character *>	_listPlayers;
};

#endif				// !GAME_HPP_
