//
// Window.hpp for Indie Studio in /home/devill_h/back_up/rendu/cpp_indie_studio/Sources
// 
// Made by Héloïse de Villepin
// Login   <devill_h@epitech.net>
// 
// Started on  Sun Jun  4 20:26:48 2017 Héloïse de Villepin
// Last update Tue Jun 13 16:20:59 2017 Héloïse de Villepin
//

#ifndef				_WINDOW_HPP_
# define			_WINDOW_HPP_
# include			<irrlicht.h>
# include			"EventManager.hpp"

class				Window
{
public:
  int				getWidth() const;
  int				getHeight() const;
  void				running();

  Window(int const &width = 1900, int const &height = 1080);
  ~Window();
private:
  int				_height;
  int				_width;
  irr::gui::IGUIEnvironment	*_gui;
  irr::IrrlichtDevice		*_device;
  irr::video::IVideoDriver	*_driver;
  irr::scene::ISceneManager	*_sceneManager;
  EventManager			_receiver;
};

#endif				// !WINDOW_HPP_
