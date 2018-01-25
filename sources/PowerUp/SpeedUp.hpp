//
// SpeedUp.hpp for IndieStudio in /home/leroy_h/rendu/CPP/IndieStudio/cpp_indie_studio/sources/PowerUp
// 
// Made by romain1 leroy
// Login   <leroy_h@epitech.net>
// 
// Started on  Sun Jun 18 14:23:55 2017 romain1 leroy
// Last update Sun Jun 18 14:25:55 2017 romain1 leroy
//

#ifndef			SPEEDUP_HPP_
# define		SPEEDUP_HPP_
# include		<irrlicht.h>
# include		"APowerUp.hpp"

class			SpeedUp : public APowerUp
{
public:
  SpeedUp(irr::scene::ISceneManager *sceneManager, irr::core::vector3df const &pos);
  ~SpeedUp();
  virtual bool		onCollision(const irr::scene::ISceneNodeAnimatorCollisionResponse &animator);
};

#endif			// !SPEEDUP_HPP_
