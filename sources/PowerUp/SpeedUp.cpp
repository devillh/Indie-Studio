//
// SpeedUp.cpp for IndieStudio in /home/leroy_h/rendu/CPP/IndieStudio/cpp_indie_studio/sources/PowerUp
// 
// Made by romain1 leroy
// Login   <leroy_h@epitech.net>
// 
// Started on  Sun Jun 18 14:19:20 2017 romain1 leroy
// Last update Sun Jun 18 19:40:37 2017 Alfonsi Hugo
//

#include "Character.hpp"
#include "SpeedUp.hpp"

SpeedUp::SpeedUp(irr::scene::ISceneManager *sceneManager,
		 irr::core::vector3df const &pos)
  : APowerUp("SpeedUp", "media/models/boot.3ds", sceneManager, pos)
{
  _model->setScale(irr::core::vector3df(0.075, 0.075, 0.075));
}

SpeedUp::~SpeedUp()
{
}

bool		SpeedUp::onCollision(irr::scene::ISceneNodeAnimatorCollisionResponse const &animator)
{
  Character	*character;

  if (!(character = Character::getCharacterFromNode(animator.getTargetNode())))
    return (true);
  character->addSpeed(3);
  _end = true;
  return (true);
}
