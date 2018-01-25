//
// SplashScreen.cpp for Indie Studio in /home/devill_h/back_up/rendu/cpp_indie_studio/sources/SplashScreen
// 
// Made by Héloïse de Villepin
// Login   <devill_h@epitech.net>
// 
// Started on  Wed Jun  7 11:06:55 2017 Héloïse de Villepin
// Last update Sun Jun 18 18:51:38 2017 Héloïse de Villepin
//

#include <irrlicht.h>
#include "Clock.hpp"
#include "SplashScreen.hpp"


void				SplashScreen::appear()
{
  Music				*music = new Music(_engine, "media/sounds/panferov.mp3");
  irr::gui::IGUIInOutFader	*fader;

  fader = _gui->addInOutFader();
  fader->setColor(irr::video::SColor(0, 0, 0, 0));
  fader->fadeIn(2000);
  fader->isReady();
  music->playMusic();
  while (_device->run())
    {
      _driver->beginScene(true, true, irr::video::SColor(0, 0, 0, 0));
      _driver->draw2DImage(_listImgs[0],
			   irr::core::rect<irr::s32>(0, 0, _width, _height),
			   irr::core::rect<irr::s32>(0, 0, 1920, 1080));
      _gui->drawAll();
      _driver->endScene();
      if (_clock.getElapsedTime().asSeconds() == 2)
	if (flashing(fader))
	  {
	    fader->isReady();
	    fader->fadeIn(1000);
	    _engine->drop();
	    return ;
	  }
    }
}

bool				SplashScreen::flashing(irr::gui::IGUIInOutFader *fader)
{
while (_device->run())
    {
      _driver->beginScene(true, true, irr::video::SColor(0, 0, 0, 0));  
      _driver->draw2DImage(_listImgs[2],
			   irr::core::rect<irr::s32>(0, 0, _width, _height),
			   irr::core::rect<irr::s32>(0, 0, 1920, 1080));
      if (_clock.getElapsedTime().asSeconds() % 2 == 0)
	_driver->draw2DImage(_listImgs[1],
			     irr::core::rect<irr::s32>(0, 0, _width, _height),
			     irr::core::rect<irr::s32>(0, 0, 1920, 1080));
      if (_receiver.IsKeyDown(irr::KEY_SPACE))
	return true;
      _gui->drawAll();
      _driver->endScene();
    }
}

SplashScreen::SplashScreen(int const &width, int const &height,
			   irr::gui::IGUIEnvironment *gui, irr::video::IVideoDriver *driver,
			   irr::IrrlichtDevice *device, EventManager &receiver)
  : _height(height), _width(width), _gui(gui), _driver(driver), _device(device), _receiver(receiver)
{
  _engine = irrklang::createIrrKlangDevice();
  _listImgs.push_back(_driver->getTexture("./media/images/indie_studio_logo_1.jpg"));
  _listImgs.push_back(_driver->getTexture("./media/images/indie_studio_logo_2.jpg"));
  _listImgs.push_back(_driver->getTexture("./media/images/indie_studio_logo_3.jpg"));
}

SplashScreen::~SplashScreen()
{
}
