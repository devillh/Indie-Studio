//
// Game.cpp for Indie Studio in /home/devill_h/back_up/rendu/cpp_indie_studio/sources
// 
// Made by Héloïse de Villepin
// Login   <devill_h@epitech.net>
// 
// Started on  Mon Jun 12 11:38:48 2017 Héloïse de Villepin
// Last update Sun Jun 18 18:17:30 2017 Héloïse de Villepin
//

#include "EventManager.hpp"
#include "Game.hpp"
#include "Character.hpp"
#include "Map.hpp"
#include "APowerUp.hpp"

bool		Game::isPlayerDead(unsigned int i) const
{
  if (i >= _listPlayers.size())
    return (false);
  return (_listPlayers[i]->isDead());
}

void		Game::generateMapAndPlayers()
{
  _listPlayers.push_back(new Character(_receiver, _device,
				       _map.getSpawnPosition(0), _map, "./media/textures/player.bmp"));
  _map.assignCollision(_listPlayers[0]->getModel());

  if (_nbPlayers == 2)
    {
      _listPlayers.push_back(new Character(_receiver, _device,
					   _map.getSpawnPosition(1), _map, "./media/textures/faerie2.bmp"));
      _listPlayers[0]->setEnemy(_listPlayers[1]);
      _listPlayers[1]->setEnemy(_listPlayers[0]);
      _listPlayers[1]->control().setMoveUp(irr::KEY_UP);
      _listPlayers[1]->control().setMoveDown(irr::KEY_DOWN);
      _listPlayers[1]->control().setMoveLeft(irr::KEY_LEFT);
      _listPlayers[1]->control().setMoveRight(irr::KEY_RIGHT);
      _listPlayers[1]->control().setPlaceBomb(irr::KEY_RETURN);
      _map.assignCollision(_listPlayers[1]->getModel());
      _listPlayers[0]->assignCollision(_listPlayers[1]->getModel());
      _listPlayers[1]->assignCollision(_listPlayers[0]->getModel());
    }
}

void		Game::running()
{
  for (int i = 0; i < _nbPlayers; i++)
    _listPlayers[i]->update();
  APowerUp::checkPowerUp();
}

Game::Game(int const &width, int const &height, irr::IrrlichtDevice *device,
	   irr::video::IVideoDriver *driver, EventManager &receiver,
	   Map &map, int const &nbPlayers, irr::scene::ISceneManager *sceneManager)
  : _width(width), _height(height), _device(device), _driver(driver),
    _receiver(receiver), _map(map), _nbPlayers(nbPlayers), _sceneManager(sceneManager)
{
}

Game::~Game()
{
  for (int i = 0; i < _nbPlayers; i++)
    delete(_listPlayers[i]);
}
