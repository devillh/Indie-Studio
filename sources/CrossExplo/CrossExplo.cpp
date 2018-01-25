//
// CrossExplo.cpp for IndieStudio in /home/leroy_h/rendu/CPP/IndieStudio/home/src/CrossExplo
// 
// Made by romain1 leroy
// Login   <leroy_h@epitech.net>
// 
// Started on  Wed Jun 14 15:43:36 2017 romain1 leroy
// Last update Wed Jun 14 16:08:34 2017 romain1 leroy
//

#include "CrossExplo.hpp"

CrossExplo::CrossExplo(irr::IrrlichtDevice *device, irr::core::vector3df const &pos,
		       unsigned int const bombPower)
  : _exploUp(device, pos, irr::core::vector3df(0.0f, 0.0f, 0.6f), bombPower),
    _exploDown(device, pos, irr::core::vector3df(0.0f, 0.0f, -0.6f), bombPower),
    _exploLeft(device, pos, irr::core::vector3df(-0.6f, 0.0f, 0.0f), bombPower),
    _exploRight(device, pos, irr::core::vector3df(0.6f, 0.0f, 0.0f), bombPower)
{
}

CrossExplo::~CrossExplo()
{
}
