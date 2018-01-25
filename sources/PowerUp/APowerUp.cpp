//
// APowerUp.cpp for IndieStudio in /home/leroy_h/rendu/CPP/IndieStudio/cpp_indie_studio/sources/PowerUp
// 
// Made by romain1 leroy
// Login   <leroy_h@epitech.net>
// 
// Started on  Sat Jun 17 15:03:44 2017 romain1 leroy
// Last update Sun Jun 18 21:39:55 2017 romain1 leroy
//

#include <algorithm>
#include <cstdlib>
#include <stdexcept>
#include "APowerUp.hpp"
#include "BombUp.hpp"
#include "SpeedUp.hpp"
#include "GodUp.hpp"

std::vector<std::unique_ptr<APowerUp>> APowerUp::_allPowerUps;

void		APowerUp::clearAllPowerUp(void)
{
  _allPowerUps.clear();
}

APowerUp	*APowerUp::createPowerUp(irr::scene::ISceneManager *sceneManager,
					 irr::core::vector3df const &pos)
{
  int		type;

  if (rand() % 3 != 0)
    return (NULL);
  type = rand() % 3;
  if (type == 0)
    _allPowerUps.push_back(std::unique_ptr<APowerUp>(new BombUp(sceneManager, pos)));
  else if (type == 1)
    _allPowerUps.push_back(std::unique_ptr<APowerUp>(new SpeedUp(sceneManager, pos)));
  else
    _allPowerUps.push_back(std::unique_ptr<APowerUp>(new GodUp(sceneManager, pos)));
  return (_allPowerUps[_allPowerUps.size() - 1].get());
}

void		APowerUp::checkPowerUp(void)
{
  unsigned int	i;

  i = 0;
  while (i < _allPowerUps.size())
    {
      if (_allPowerUps[i]->_end == true)
	{
	  _allPowerUps.erase(_allPowerUps.begin() + i);
	  i = 0;
	}
      else
	++i;
    }
}

APowerUp::APowerUp(std::string const &name, std::string const &model,
		   irr::scene::ISceneManager *sceneManager,
		   irr::core::vector3df const &pos)
  : _name(name), _sceneManager(sceneManager), _end(false)
{
  if (!(_model = _sceneManager->addAnimatedMeshSceneNode(_sceneManager->getMesh(model.c_str()))))
    throw std::runtime_error("Failed to load the powerUp model");
  _model->setPosition(pos);
  _model->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  _selector = _sceneManager->createOctreeTriangleSelector(_model->getMesh(),
							  _model, 128);
  _model->setTriangleSelector(_selector);
  _model->setName("PowerUp");
}

APowerUp::~APowerUp()
{
  std::for_each(_collisionTab.begin(), _collisionTab.end(),
		[](auto &col) {
		  col.first->removeAnimator(col.second);
		});
  _selector->drop();
  _sceneManager->addToDeletionQueue(_model);
}

irr::scene::IAnimatedMeshSceneNode	*APowerUp::getModel(void)
{
  return (_model);
}

void							APowerUp::assignCollision(irr::scene::IAnimatedMeshSceneNode *model)
{
  irr::scene::ISceneNodeAnimatorCollisionResponse	*anim;

  anim = _sceneManager->createCollisionResponseAnimator(_selector, model,
							irr::core::vector3df(10, 10, 10),
							irr::core::vector3df(0.0f, 0.0f, 0.0f),
							irr::core::vector3df(0.0f, 0.0f, 0.0f));
  model->addAnimator(anim);
  anim->setCollisionCallback(this);
  anim->setTargetNode(model);
  anim->drop();
  _collisionTab.push_back({model, anim});
}
