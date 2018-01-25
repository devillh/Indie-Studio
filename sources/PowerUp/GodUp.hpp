//
// GodUp.hpp for IndieStudio in /home/leroy_h/rendu/CPP/IndieStudio/cpp_indie_studio/sources/PowerUp
// 
// Made by romain1 leroy
// Login   <leroy_h@epitech.net>
// 
// Started on  Sun Jun 18 14:35:45 2017 romain1 leroy
// Last update Sun Jun 18 14:37:39 2017 romain1 leroy
//

#ifndef		GODUP_HPP_
# define	GODUP_HPP_
# include	<irrlicht.h>
# include	"APowerUp.hpp"

class		GodUp : public APowerUp
{
public:
  GodUp(irr::scene::ISceneManager *sceneManager, irr::core::vector3df const &pos);
  ~GodUp();
  virtual bool	onCollision(const irr::scene::ISceneNodeAnimatorCollisionResponse &animator);
};

#endif		// !GODUP_HPP_
