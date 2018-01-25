//
// CrossExplo.hpp for IndieStudio in /home/leroy_h/rendu/CPP/IndieStudio/home/src/CrossExplo
// 
// Made by romain1 leroy
// Login   <leroy_h@epitech.net>
// 
// Started on  Wed Jun 14 16:05:45 2017 romain1 leroy
// Last update Sun Jun 18 16:24:19 2017 romain1 leroy
//

#ifndef			CROSSEXPLO_HPP_
# define		CROSSEXPLO_HPP_
# include		<irrlicht.h>
# include		"Explosion.hpp"

class			CrossExplo
{
public:
  CrossExplo(irr::IrrlichtDevice *device, irr::core::vector3df const &pos,
	     unsigned int const bombPower);
  ~CrossExplo();
private:
  Explosion		_exploUp;
  Explosion		_exploDown;
  Explosion		_exploLeft;
  Explosion		_exploRight;
};

#endif			// !CROSSEXPLO_HPP_
