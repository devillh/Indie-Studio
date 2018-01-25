//
// Window.cpp for Indie Studio in /home/devill_h/back_up/rendu/cpp_indie_studio/Sources
// 
// Made by Héloïse de Villepin
// Login   <devill_h@epitech.net>
// 
// Started on  Sun Jun  4 20:49:03 2017 Héloïse de Villepin
// Last update Sun Jun 18 17:09:09 2017 romain1 leroy
//

#include <stdexcept>
#include "MainMenu.hpp"
#include "Game.hpp"
#include "Window.hpp"
#include "Map.hpp"
#include "Clock.hpp"
#include "EscMenu.hpp"
#include "SplashScreen.hpp"

void		Window::running()
{
  SplashScreen	Intro(_width, _height, _gui, _driver, _device, _receiver);
  MainMenu	Menu(_width, _height, _gui, _driver, _device, _receiver, _sceneManager);
  bool		end = false;

  Intro.appear();
  Menu.createButtons();
  while (_device->run() && !end)
    {
      _driver->beginScene(true, true, irr::video::SColor(0, 0, 0, 0));
      end = Menu.running();
      _gui->drawAll();
      _driver->endScene();
      _receiver.resetKeyIsPressed();
    }
}

Window::Window(int const &width, int const &height)
  : _height(height), _width(width), _receiver()
{
  if ((_device = irr::createDevice(irr::video::EDT_OPENGL,
			      irr::core::dimension2d<irr::u32>(_width, _height),
				   32, false, true, false, &_receiver)) == NULL)
    throw std::runtime_error("Device can't be load");
  _device->setWindowCaption(L"BOMBERMAN");
  _device->getCursorControl()->setVisible(true);
  _driver = _device->getVideoDriver();
  _gui = _device->getGUIEnvironment();
  _sceneManager = _device->getSceneManager();
}

Window::~Window()
{
  _device->getSceneManager()->clear();
  _device->drop();
}
