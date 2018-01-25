//
// Bomb.cpp for  in /home/gregory.chouquet/Rendu/Now/cpp_indie_studio/test_Hugo
// 
// Made by Claptou Claptou
// Login   <gregory.chouquet@epitech.net>
// 
// Started on  Thu Jun  8 11:06:50 2017 Claptou Claptou
// Last update Sun Jun 18 19:22:36 2017 Claptou Claptou
//

#include <irrlicht.h>
#include <stdexcept>
#include <algorithm>
#include "Bomb.hpp"
#include "APowerUp.hpp"

Bomb::Bomb(irr::scene::IAnimatedMeshSceneNode *node, irr::scene::ISceneManager* smgr,
	   irr::video::IVideoDriver *driver)
  : _smgr(smgr)
{
  irr::scene::IParticleEmitter	*emitter;

  if (!(_noded = smgr->addAnimatedMeshSceneNode(smgr->getMesh("media/models/bomb.3DS"))))
    throw std::runtime_error("Failed to load bomb 3D model");
  setCoor(node);
  putBomb(node);
  _selector = _smgr->createOctreeTriangleSelector(_noded->getMesh(), _noded, 128);
  _noded->setTriangleSelector(_selector);
  _particleSystem = smgr->addParticleSystemSceneNode(false);
  emitter = _particleSystem->createBoxEmitter(irr::core::aabbox3d<irr::f32>
					      (_pos.X + 2.0f, 39.0f, _pos.Z, _pos.X + 2.0f, 39.0f, _pos.Z),
					      irr::core::vector3df(0.0f, 0.6f, 0.0f),
					      10, 12,
					      irr::video::SColor(0, 255, 255, 255),
					      irr::video::SColor(0, 255, 255, 255),
					      4, 4, 0,
					      irr::core::dimension2df(8.0f, 8.0f),
					      irr::core::dimension2df(14.0f, 14.0f));
  _particleSystem->setEmitter(emitter);
  emitter->drop();
  _particleSystem->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  _particleSystem->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
  _particleSystem->setMaterialTexture(0, driver->getTexture("media/textures/fire.bmp"));
  _particleSystem->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
}

void	Bomb::setCoor(irr::scene::IAnimatedMeshSceneNode *node)
{
  if (node->getPosition().X > 0)
    {
      _pos.X = (node->getPosition().X - (static_cast<int>(node->getPosition().X) % 50));
      if (node->getPosition().X > _pos.X + 25)
	_pos.X += 50;
    }
  if (node->getPosition().X < 0)
    {
      _pos.X = (node->getPosition().X - (static_cast<int>(node->getPosition().X) % 50));
      if (node->getPosition().X < _pos.X - 25)
	_pos.X -= 50;
    }
  if (node->getPosition().Z > 0)
    {
      _pos.Z = (node->getPosition().Z - (static_cast<int>(node->getPosition().Z) % 50));
      if (node->getPosition().Z > _pos.Z + 25)
	_pos.Z += 50;
    }
  if (node->getPosition().Z < 0)
    {
      _pos.Z = (node->getPosition().Z - (static_cast<int>(node->getPosition().Z) % 50));
      if (node->getPosition().Z < _pos.Z - 25)
	_pos.Z -= 50;
    }
  _pos.X = static_cast<int>(_pos.X);
  _pos.Z = static_cast<int>(_pos.Z);
}

void	Bomb::putBomb(irr::scene::IAnimatedMeshSceneNode *node)
{
  _noded->setPosition(irr::core::vector3df(_pos.X, 30.f, _pos.Z));
  _noded->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  _noded->setRotation(irr::core::vector3df(0.f, 100.f, 0.f));
}

void					Bomb::assignCollision(irr::scene::IAnimatedMeshSceneNode *model)
{
  irr::scene::ISceneNodeAnimator	*anim;

  anim = _smgr->createCollisionResponseAnimator(_selector, model,
						irr::core::vector3df(10, 10, 10),
						irr::core::vector3df(0.0f, 0.0f, 0.0f),
						irr::core::vector3df(0.0f, 0.0f, 0.0f));
  model->addAnimator(anim);
  anim->drop();
  _collisionTab.push_back({model, anim});
}

Bomb::~Bomb()
{
  std::for_each(_collisionTab.begin(), _collisionTab.end(),
		[](auto &val) {
		  val.first->removeAnimator(val.second);
		});
  _selector->drop();
  _smgr->addToDeletionQueue(_noded);
  _smgr->addToDeletionQueue(_particleSystem);
}

void		Bomb::blowUp(Map &map, unsigned int const bombPower, Character *p1, Character *p2)
{
  blowDirection(map, bombPower, irr::core::vector3df(50.0f, 0.0f, 0.0f), p1, p2);
  blowDirection(map, bombPower, irr::core::vector3df(-50.0f, 0.0f, 0.0f), p1, p2);
  blowDirection(map, bombPower, irr::core::vector3df(0.0f, 0.0f, 50.0f), p1, p2);
  blowDirection(map, bombPower, irr::core::vector3df(0.0f, 0.0f, -50.0f), p1, p2);
}

void		Bomb::blowDirection(Map &map, unsigned int const bombPower,
				    irr::core::vector3df const &dir,
				    Character *p1, Character *p2)
{
  unsigned int	i;
  APowerUp	*powerUp;

  i = 1;
  while (i <= bombPower)
    {
      if (map.eraseWallAtPosition(irr::core::vector3df(_pos.X, 30.0f, _pos.Z) + dir * i))
	{
	  if (!(powerUp = APowerUp::createPowerUp(_smgr,
							    irr::core::vector3df(_pos.X, 30.0f, _pos.Z) + dir * i)))
	    return ;
	  powerUp->assignCollision(p1->getModel());
	  if (p2)
	    powerUp->assignCollision(p2->getModel());
	  return ;
	}
      ++i;
    }
}

irr::core::vector3df const	&Bomb::getPos(void) const
{
  return (_pos);
}
