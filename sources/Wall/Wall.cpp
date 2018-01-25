//
// Wall.cpp for IndieStudio in /home/leroy_h/rendu/CPP/IndieStudio/home/Wall
// 
// Made by romain1 leroy
// Login   <leroy_h@epitech.net>
// 
// Started on  Tue Jun  6 10:14:58 2017 romain1 leroy
// Last update Tue Jun 13 14:46:29 2017 romain1 leroy
//

#include <algorithm>
#include "Wall.hpp"

Wall::Wall(irr::IrrlichtDevice *device, irr::core::vector3df const &pos)
  : _sceneManager(device->getSceneManager()), _pos(pos)
{
  irr::video::IVideoDriver	*driver;

  driver = device->getVideoDriver();
  _wall = _sceneManager->addCubeSceneNode(50.f, NULL, -1, pos);
  _wall->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  _wall->setMaterialTexture(0, driver->getTexture("media/textures/wood.png"));
  _selector = _sceneManager->createOctreeTriangleSelector(_wall->getMesh(),
							  _wall, 128);
  _wall->setTriangleSelector(_selector);
}

Wall::~Wall()
{
  std::for_each(_collisionTab.begin(), _collisionTab.end(),
		[](auto &collision) {
		  collision.first->removeAnimator(collision.second);
		});
  _selector->drop();
  _sceneManager->addToDeletionQueue(_wall);
}

void					Wall::assignCollision(irr::scene::IAnimatedMeshSceneNode *model)
{
  irr::scene::ISceneNodeAnimator	*anim;

  anim = _sceneManager->createCollisionResponseAnimator(_selector, model,
							irr::core::vector3df(10, 10, 10),
							irr::core::vector3df(0.f, 0.f, 0.f),
							irr::core::vector3df(0.f, 0.f, 0.f));
  model->addAnimator(anim);
  anim->drop();
  _collisionTab.push_back({model, anim});
}

irr::core::vector3df const	&Wall::getPosition() const
{
  return (_pos);
}
