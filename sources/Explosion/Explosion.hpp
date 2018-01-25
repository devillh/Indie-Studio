//
// Explosion.hpp for IndieStudio in /home/leroy_h/rendu/CPP/IndieStudio/home/src/Explosion
// 
// Made by romain1 leroy
// Login   <leroy_h@epitech.net>
// 
// Started on  Wed Jun 14 15:03:48 2017 romain1 leroy
// Last update Sun Jun 18 16:22:59 2017 romain1 leroy
//

#ifndef					EXPLOSION_HPP_
# define				EXPLOSION_HPP_
# include				<irrlicht.h>

class					Explosion
{
public:
  Explosion(irr::IrrlichtDevice *device, irr::core::vector3df const &pos,
	    irr::core::vector3df const &direction, unsigned int const bombPower);
  ~Explosion();
private:
  irr::scene::IParticleSystemSceneNode	*_particleSystem;
};

#endif					// !EXPLOSION_HPP_
