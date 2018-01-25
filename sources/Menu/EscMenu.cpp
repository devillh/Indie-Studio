//
// EscMenu.cpp for  in /home/gregory.chouquet/Rendu/Now/cpp_indie_studio/sources/EscMenu
// 
// Made by Claptou Claptou
// Login   <gregory.chouquet@epitech.net>
// 
// Started on  Tue Jun 13 09:45:56 2017 Claptou Claptou
// Last update Sun Jun 18 15:57:51 2017 Héloïse de Villepin
//

#include <irrlicht.h>
#include "EscMenu.hpp"

EscMenu::EscMenu(int width, int height, irr::gui::IGUIEnvironment *gui, irr::video::IVideoDriver *driver, EventManager receiver, irr::IrrlichtDevice *device)
  : _height(height), _width(width), _gui(gui), _driver(driver), _receiver(receiver), _device (device)
{
  _allImages.push_back(_driver->getTexture("./media/images/continue.jpg"));
  _allImages.push_back(_driver->getTexture("./media/images/restart.jpg"));
  _allImages.push_back(_driver->getTexture("./media/images/quit.jpg"));
}

void	EscMenu::deadOne()
{  
  _button[0]->setVisible(false);
}

void	EscMenu::deadTwo()
{
  _button[0]->setVisible(false);
}

void	EscMenu::deleteButtonEsc()
{
  if (!_button.empty())
    {
      for (int i = 0; _button.size() > i; i++)
	_button[i]->remove();
      _button.clear();
    }
}

int	EscMenu::running()
{
  if (_button[0]->isPressed())
    {
      _button[0]->setIsPushButton(false);
      return (1);
    }
  if (_button[1]->isPressed())
    {
      _button[1]->setIsPushButton(false);
      return (2);
    }
  if (_button[2]->isPressed())
    {
      _button[2]->setIsPushButton(false);
      return (3);
    }
  else
    return (-1);
}

void	EscMenu::DisplayMenu()
{
  int   x;
  int   h;
  int   y;

  x = _width / 1.5;
  h = _height;
  y = h / 3;
  _button.push_back(_gui->addButton(irr::core::rect<irr::s32>(x / 2, y - h / 16, x, y += h / 10)));
  _button[0]->setImage(_allImages[0]);
  _button[0]->setScaleImage();
  _button.push_back(_gui->addButton(irr::core::rect<irr::s32>(x / 2, y - h / 16, x, y += h / 10)));
  _button[1]->setImage(_allImages[1]);
  _button[1]->setScaleImage();
  _button.push_back(_gui->addButton(irr::core::rect<irr::s32>(x / 2, y - h / 16, x, y += h / 10)));
  _button[2]->setImage(_allImages[2]);
  _button[2]->setScaleImage();
  _button[0]->setIsPushButton();
  _button[1]->setIsPushButton();
  _button[2]->setIsPushButton();
}

EscMenu::~EscMenu()
{
}
