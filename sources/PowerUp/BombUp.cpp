//
// BombUp.cpp for IndieStudio in /home/leroy_h/rendu/CPP/IndieStudio/cpp_indie_studio/sources/PowerUp
// 
// Made by romain1 leroy
// Login   <leroy_h@epitech.net>
// 
// Started on  Sat Jun 17 15:22:58 2017 romain1 leroy
// Last update Sun Jun 18 19:02:22 2017 Claptou Claptou
//

#include "Character.hpp"
#include "BombUp.hpp"

BombUp::BombUp(irr::scene::ISceneManager *sceneManager,
	       irr::core::vector3df const &pos)
  : APowerUp("BombUp", "media/models/bomb.3DS", sceneManager, pos)
{
}

BombUp::~BombUp()
{
}

bool		BombUp::onCollision(irr::scene::ISceneNodeAnimatorCollisionResponse const &animator)
{
  Character	*character;

  character = Character::getCharacterFromNode(animator.getTargetNode());
  if (character == NULL)
    return (true);
  character->addBomb(1);
  _end = true;
  return (true);
}
