//
// Wall.hpp for IndieStudio in /home/leroy_h/rendu/CPP/IndieStudio/home/Wall
// 
// Made by romain1 leroy
// Login   <leroy_h@epitech.net>
// 
// Started on  Tue Jun  6 10:06:49 2017 romain1 leroy
// Last update Tue Jun 13 22:27:41 2017 Héloïse de Villepin
//

#ifndef				WALL_HPP_
# define			WALL_HPP_
# include			<irrlicht.h>
# include			<utility>
# include			<vector>

class				Wall
{
public:
  Wall(irr::IrrlichtDevice *device, irr::core::vector3df const &pos);
  ~Wall();
  void				assignCollision(irr::scene::IAnimatedMeshSceneNode *model);
  irr::core::vector3df const	&getPosition() const;

private:
  typedef std::pair<irr::scene::IAnimatedMeshSceneNode *, irr::scene::ISceneNodeAnimator *> CollisionInfo;
  irr::scene::IMeshSceneNode	*_wall;
  irr::scene::ITriangleSelector	*_selector;
  irr::scene::ISceneManager	*_sceneManager;
  std::vector<CollisionInfo>	_collisionTab;
  irr::core::vector3df		_pos;
};

#endif				// !WALL_HPP_
