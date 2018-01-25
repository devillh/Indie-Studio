//
// SplashScreen.hpp for Indie Studio in /home/devill_h/back_up/rendu/cpp_indie_studio/sources/SplashScreen
// 
// Made by Héloïse de Villepin
// Login   <devill_h@epitech.net>
// 
// Started on  Wed Jun  7 11:03:30 2017 Héloïse de Villepin
// Last update Sun Jun 18 13:27:44 2017 Alfonsi Hugo
//

#ifndef				_SPLASHSCREEN_HPP_
# define			_SPLASHSCREEN_HPP_
# include			<irrlicht.h>
# include			<irrKlang.h>
# include			<vector>
# include			"Clock.hpp"
# include			"EventManager.hpp"
# include			"Music.hpp"

class				SplashScreen
{
public:
  void				appear();
  bool				flashing(irr::gui::IGUIInOutFader *);
  
  SplashScreen(int const &, int const &, irr::gui::IGUIEnvironment *,
	       irr::video::IVideoDriver *, irr::IrrlichtDevice *, EventManager &);
  ~SplashScreen();
private:
  int				_height;
  int				_width;
  irr::gui::IGUIEnvironment	*_gui;
  irr::video::IVideoDriver	*_driver;
  irr::IrrlichtDevice		*_device;
  EventManager			&_receiver;
  std::vector<irr::video::ITexture *>	_listImgs;
  ir::Clock				_clock;
  irrklang::ISoundEngine		*_engine;
};

#endif				// !SPLASHSCREEN_HPP_
