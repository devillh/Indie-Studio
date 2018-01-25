//
// MainMenu.cpp for Indie Studio in /home/devill_h/back_up/rendu/cpp_indie_studio/Sources/Menu
// 
// Made by Héloïse de Villepin
// Login   <devill_h@epitech.net>
// 
// Started on  Fri Jun  2 21:41:19 2017 Héloïse de Villepin
// Last update Sun Jun 18 21:50:43 2017 romain1 leroy
//

#include <irrlicht.h>
#include "Game.hpp"
#include "EscMenu.hpp"
#include "MainMenu.hpp"

void	MainMenu::createButtons()
{
  int	y;
  int	i;

  y = _height / 3;
  i = 0;
  while (i < 3)
    {
      _allButtons.push_back(_gui->addButton(irr::core::rect<irr::s32>
					    (_width / 3, y - _height / 16,
					     _width / 1.5, y += _height / 10)));
      _allButtons[i]->setImage(_allImages[i]);
      _allButtons[i]->setScaleImage();
      _allButtons[i]->setIsPushButton();
      i++;
    }
}

void		MainMenu::deleteButtons()
{
  if (!_allButtons.empty())
    {
      _allButtons[0]->remove();
      _allButtons[1]->remove();
      _allButtons[2]->remove();
      _allButtons.clear();
    }
}

void		MainMenu::restart(Map *map, Game *game, EscMenu *Menuesc, int nbPlayers, irrklang::ISoundEngine *engine)
{
  APowerUp::clearAllPowerUp();
  if (engine)
    engine->drop();
  _driver->endScene();
  Menuesc->deleteButtonEsc();
  delete(game);
  delete(map);
  delete(Menuesc);
  _sceneManager->clear();
  driveGame(nbPlayers);
  return ;
}

void		MainMenu::quit(Map *map, Game *game, EscMenu *Menuesc, irrklang::ISoundEngine *engine)
{
  APowerUp::clearAllPowerUp();
  if (engine)
    engine->drop();
  _driver->endScene();
  Menuesc->deleteButtonEsc();
  createButtons();
  delete(game);
  delete(map);
  delete(Menuesc);
  _sceneManager->clear();
  return ;
}

void				MainMenu::driveGame(int const &nbPlayers)
{
  Map		*map;
  Game		*game;
  EscMenu	*Menuesc;
  int		i;

  i = 0;
  map = new Map(_device);
  game = new Game(_width, _height, _device, _driver,
		  _receiver, *map, nbPlayers, _sceneManager);  
  Menuesc = new EscMenu(1920, 1080, _gui, _driver, _receiver, _device);
  Menuesc->DisplayMenu();
  game->generateMapAndPlayers();
  irrklang::ISoundEngine	*engine = irrklang::createIrrKlangDevice();
  Music				*music = new Music(engine, "media/sounds/ridaz.mp3");
  irr::gui::IGUIImage		*deathImg = NULL;

  music->playMusic();
  while (_device->run())
    {
      _driver->beginScene(true, true, irr::video::SColor(0, 0, 0, 0));
      if (_receiver.IsKeyDown(irr::KEY_ESCAPE) || game->isPlayerDead(0) || game->isPlayerDead(1))
	{
	  deleteButtons();
	  while (_device->run())
            {
	      if (i != 0  && i != 2)
		{
		  deathImg = _gui->addImage(_allImages[i], irr::core::position2d<irr::s32>{0, 0});
		  i = 2;
		}
	      if (game->isPlayerDead(0))
		{
		  if (i != 2)
		    i = 5;
		  Menuesc->deadOne();
		}
	      else if(game->isPlayerDead(1))
		{
		  if (i != 2)
		    i = 4;
		  Menuesc->deadTwo();
		}
	      _device->getCursorControl()->setVisible(true);
	      _driver->beginScene(true, true, irr::video::SColor(255, 255, 255, 255));
	      if (Menuesc->running() == 1)
		{
		  break ;
		}
              if (Menuesc->running() == 2)
		{
		  if (deathImg)
		    {
		      deathImg->remove();
		      deathImg = NULL;
		    }
		  return(restart(map, game, Menuesc, nbPlayers, engine));
		}
              if (Menuesc->running() == 3)
		{
		  if (deathImg)
		    {
		      deathImg->remove();
		      deathImg = NULL;
		    }
		  return (quit(map, game , Menuesc, engine));
		}
	      _sceneManager->drawAll();
              _gui->drawAll();
              _driver->endScene();
	      _receiver.resetKeyIsPressed();
            }
	}
      else 
	{
	  game->running();
	  _device->getCursorControl()->setVisible(false);
	  _sceneManager->drawAll();
	  _driver->endScene();
	}
      _receiver.resetKeyIsPressed();
    }
  map->clearWall();
}

bool	MainMenu::running()
{
  _driver->draw2DImage(_allImages[3],
		       irr::core::rect<irr::s32>(0, 0, _width, _height),
		       irr::core::rect<irr::s32>(0, 0, 1920, 1080));
  if (_allButtons[0]->isPressed())
    {
      _allButtons[0]->setPressed(false);
      driveGame(1);
    }
  else if (_allButtons[1]->isPressed())
    {
      _allButtons[1]->setPressed(false);
      driveGame(2);
    }
  else if (_allButtons[2]->isPressed())
    {
      _allButtons[2]->setPressed(false);
      return (true);
    }
}

MainMenu::MainMenu(int const &width, int const &height,
		   irr::gui::IGUIEnvironment *gui, irr::video::IVideoDriver *driver,
		   irr::IrrlichtDevice *device, EventManager &receiver,
		   irr::scene::ISceneManager *sceneManager)
  : _height(height), _width(width), _gui(gui), _driver(driver), _device(device),
    _receiver(receiver), _sceneManager(sceneManager)
{
  _allImages.push_back(_driver->getTexture("./media/images/solo.jpg"));
  _allImages.push_back(_driver->getTexture("./media/images/multi.jpg"));
  _allImages.push_back(_driver->getTexture("./media/images/quit.jpg"));
  _allImages.push_back(_driver->getTexture("./media/images/main_menu.jpg"));
  _allImages.push_back(_driver->getTexture("./media/images/player_1_win.png"));
  _allImages.push_back(_driver->getTexture("./media/images/player_2_win.png"));
}

MainMenu::~MainMenu()
{
}
