//
// Map.cpp for IndieStudio in /home/leroy_h/rendu/CPP/IndieStudio/home/Map
// 
// Made by romain1 leroy
// Login   <leroy_h@epitech.net>
// 
// Started on  Wed Jun  7 11:16:12 2017 romain1 leroy
// Last update Sun Jun 18 16:35:49 2017 romain1 leroy
//

#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Map.hpp"

char const	*Map::MapGrid[] =
  {
    "XXOOOOOOOOOXX\0",
    "XXOXOXOXOXOXX\0",
    "OOOOOOOOOOOOO\0",
    "OXOXOXOXOXOXO\0",
    "OOOOOOOOOOOOO\0",
    "OXOXOXOXOXOXO\0",
    "OOOOOOOOOOOOO\0",
    "OXOXOXOXOXOXO\0",
    "OOOOOOOOOOOOO\0",
    "XXOXOXOXOXOXX\0",
    "XXOOOOOOOOOXX\0",
    NULL
  };

irr::core::vector3df const	Map::SpawnPosition[] =
  {
    irr::core::vector3df(-300.f, 30.f, 300.f),
    irr::core::vector3df(300.f, 30.f, -200.f),
    irr::core::vector3df(-300.f, 30.f, -200.f),
    irr::core::vector3df(300.f, 30.f, 300.f)
  };

void		Map::genRandWall()
{
  int		y;
  int		x;

  srand(time(NULL));
  y = 0;
  while (MapGrid[y])
    {
      x = 0;
      while (MapGrid[y][x])
	{
	  if (rand() % 3 == 2 && MapGrid[y][x] != 'X')
	    _wallTab.push_back(std::unique_ptr<Wall>(new Wall(_device,
							      irr::core::vector3df(50.f * (x - 6),
										   30.f,
										   50.f * (y - 5) + 50.f))));
	  ++x;
	}
      ++y;
    }
}

Map::Map(irr::IrrlichtDevice *device)
  : _device(device), _sceneManager(device->getSceneManager())
{
  irr::core::array<irr::scene::ISceneNode *>	nodes;
  irr::scene::ISceneNode			*node;
  irr::scene::ITriangleSelector			*selector;
  unsigned int					i;

  if (!_sceneManager->loadScene("media/maps/map.irr"))
    throw std::runtime_error("Failed to load the scene.");
  _meta = _sceneManager->createMetaTriangleSelector();
  _sceneManager->getSceneNodesFromType(irr::scene::ESNT_CUBE, nodes);
  _sceneManager->addCameraSceneNode(NULL, irr::core::vector3df(0, 450, -200),
				    irr::core::vector3df(0, 0, 0));
  i = 0;
  while (i < nodes.size())
    {
      node = nodes[i];
      selector = _sceneManager->createTriangleSelectorFromBoundingBox(node);
      if (selector)
	{
	  _meta->addTriangleSelector(selector);
	  selector->drop();
	}
      ++i;
    }
  genRandWall();
}

Map::~Map()
{
  _meta->drop();
}

void					Map::assignCollision(irr::scene::IAnimatedMeshSceneNode *model)
{
  irr::scene::ISceneNodeAnimator	*anim;

  anim = _sceneManager->createCollisionResponseAnimator(_meta,
							model,
							irr::core::vector3df(10, 10, 10),
							irr::core::vector3df(0.f, 0.f, 0.f),
							irr::core::vector3df(0.f, 0.f, 0.f));
  model->addAnimator(anim);
  anim->drop();
  std::for_each(_wallTab.begin(), _wallTab.end(),
		[model](auto &wall) {
		  wall->assignCollision(model);
		});
}

irr::core::vector3df const	&Map::getSpawnPosition(int playerId) const
{
  if (playerId < 0 || playerId > 3)
    return (SpawnPosition[0]);
  return (SpawnPosition[playerId]);
}

void	Map::clearWall()
{
  _wallTab.clear();
}

bool		Map::eraseWallAtPosition(irr::core::vector3df const &pos)
{
  unsigned int	i;

  i = 0;
  while (i < _wallTab.size())
    {
      if (_wallTab[i]->getPosition() == pos)
	{
	  _wallTab.erase(_wallTab.begin() + i);
	  return (true);
	}
      ++i;
    }
  return (false);
}
