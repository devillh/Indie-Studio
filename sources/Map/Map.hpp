//
// Map.hpp for IndieStudio in /home/leroy_h/rendu/CPP/IndieStudio/home/Map
// 
// Made by romain1 leroy
// Login   <leroy_h@epitech.net>
// 
// Started on  Tue Jun  6 15:54:02 2017 romain1 leroy
// Last update Sun Jun 18 16:34:40 2017 romain1 leroy
//

#ifndef					MAP_HPP_
# define				MAP_HPP_
# include				<irrlicht.h>
# include				<vector>
# include				<memory>
# include				"Wall.hpp"

class					Map
{
public:
  Map(irr::IrrlichtDevice *device);
  ~Map();
  void					assignCollision(irr::scene::IAnimatedMeshSceneNode *model);
  irr::core::vector3df const		&getSpawnPosition(int const playerId) const;
  void					clearWall(void);
  bool					eraseWallAtPosition(irr::core::vector3df const &pos);
private:
  static char const			*MapGrid[];
  static irr::core::vector3df const	SpawnPosition[];
  void					genRandWall(void);
  irr::IrrlichtDevice			*_device;
  irr::scene::ISceneManager		*_sceneManager;
  irr::scene::IMetaTriangleSelector	*_meta;
  std::vector<std::unique_ptr<Wall>>	_wallTab;
};

#endif					// !MAP_HPP_
