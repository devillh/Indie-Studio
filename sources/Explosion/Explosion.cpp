//
// Explosion.cpp for IndieStudio in /home/leroy_h/rendu/CPP/IndieStudio/home/src/Explosion
// 
// Made by romain1 leroy
// Login   <leroy_h@epitech.net>
// 
// Started on  Wed Jun 14 14:45:41 2017 romain1 leroy
// Last update Thu Jun 15 11:34:33 2017 romain1 leroy
//

#include "Explosion.hpp"

Explosion::Explosion(irr::IrrlichtDevice *device,
		     irr::core::vector3df const &pos,
		     irr::core::vector3df const &direction,
		     unsigned int const bombPower)
{
  irr::scene::ISceneManager	*sceneManager;
  irr::video::IVideoDriver	*driver;
  irr::scene::IParticleEmitter	*emitter;
  irr::scene::IParticleAffector	*affector;

  sceneManager = device->getSceneManager();
  driver = device->getVideoDriver();
  _particleSystem = sceneManager->addParticleSystemSceneNode(false);
  emitter = _particleSystem->createBoxEmitter(irr::core::aabbox3d<irr::f32>
					      (pos.X - 10.0f, 30.0f - 10.0f, pos.Z - 10.0f,
					       pos.X + 10.0f, 30.0f + 10.0f, pos.Z + 10.0f),
					      direction, 2080, 2100,
					      irr::video::SColor(0, 255, 255, 255),
					      irr::video::SColor(0, 255, 255, 255),
					      100 * bombPower, 100 * bombPower,
					      0,
					      irr::core::dimension2df(8.0f, 8.0f),
					      irr::core::dimension2df(14.0f, 14.0f));
  _particleSystem->setEmitter(emitter);
  emitter->drop();
  affector = _particleSystem->createFadeOutParticleAffector(irr::video::SColor(0, 0, 0, 0),
							    50);
  _particleSystem->addAffector(affector);
  affector->drop();
  _particleSystem->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  _particleSystem->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
  _particleSystem->setMaterialTexture(0, driver->getTexture("media/textures/fire.bmp"));
  _particleSystem->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
}

Explosion::~Explosion()
{
  _particleSystem->remove();
}
