//
// Bomb.hpp for  in /home/gregory.chouquet/Rendu/Now/cpp_indie_studio/test_Hugo
// 
// Made by Claptou Claptou
// Login   <gregory.chouquet@epitech.net>
// 
// Started on  Thu Jun  8 11:02:20 2017 Claptou Claptou
// Last update Sun Jun 18 17:58:13 2017 Héloïse de Villepin
//

#ifndef					_BOMB_HPP_
# define				_BOMB_HPP_
# include				<irrlicht.h>
# include				<vector>
# include				"Map.hpp"
# include				"Character.hpp"

class					Character;

class					Bomb
{
  std::vector<std::pair<irr::scene::IAnimatedMeshSceneNode *, irr::scene::ISceneNodeAnimator *>> _collisionTab;
  irr::core::vector3df			_pos;
  irr::scene::IParticleSystemSceneNode	*_particleSystem;
  irr::scene::IAnimatedMeshSceneNode	*_noded;
  irr::scene::ISceneManager		*_smgr;
  irr::scene::ITriangleSelector		*_selector;
  void					putBomb(irr::scene::IAnimatedMeshSceneNode *node);
  void					setCoor(irr::scene::IAnimatedMeshSceneNode *node);
  void					createCollision(irr::scene::IAnimatedMeshSceneNode *node);
  void					blowDirection(Map &map, unsigned int const bombPower,
						      irr::core::vector3df const &dir,
						      Character *p1, Character *p2);
public:
  Bomb(irr::scene::IAnimatedMeshSceneNode *node, irr::scene::ISceneManager* smgr,
       irr::video::IVideoDriver *driver);
  Bomb();
  void					blowUp(Map &map,
					       unsigned int const bombPower,
					       Character *p1, Character *p2);
  irr::core::vector3df const		&getPos(void) const;
  void					assignCollision(irr::scene::IAnimatedMeshSceneNode *model);
  ~Bomb();
};

#endif					// !BOMB_HPP_
