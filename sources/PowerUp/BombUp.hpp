//
// BombUp.hpp for IndieStudio in /home/leroy_h/rendu/CPP/IndieStudio/cpp_indie_studio/sources/PowerUp
// 
// Made by romain1 leroy
// Login   <leroy_h@epitech.net>
// 
// Started on  Sat Jun 17 15:14:56 2017 romain1 leroy
// Last update Sat Jun 17 18:33:32 2017 romain1 leroy
//

#ifndef				BOMBUP_HPP_
# define			BOMBUP_HPP_
# include			<irrlicht.h>
# include			"APowerUp.hpp"

class				BombUp : public APowerUp
{
public:
  BombUp(irr::scene::ISceneManager *sceneManager, irr::core::vector3df const &pos);
  ~BombUp();
  virtual bool				onCollision(const irr::scene::ISceneNodeAnimatorCollisionResponse &animator);
};

#endif				// !BOMBUP_HPP_
