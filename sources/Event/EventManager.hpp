//
// EventManager.hpp for indie studio in /home/leroy_h/rendu/CPP/IndieStudio/home
// 
// Made by romain1 leroy
// Login   <leroy_h@epitech.net>
// 
// Started on  Mon Jun  5 14:25:03 2017 romain1 leroy
// Last update Sun Jun 18 16:27:27 2017 romain1 leroy
//

#ifndef			EVENTMANAGER_HPP_
# define		EVENTMANAGER_HPP_
# include		<irrlicht.h>

class			EventManager : public irr::IEventReceiver
{
public:
  bool			OnEvent(const irr::SEvent &event);
  bool			IsKeyDown(irr::EKEY_CODE const keyCode) const;
  bool			IsKeyPressed(irr::EKEY_CODE const keyCode) const;
  void			resetKeyIsPressed(void);
  EventManager();
  ~EventManager();
private:
  bool			KeyIsDown[irr::KEY_KEY_CODES_COUNT];
  bool			KeyIsPressed[irr::KEY_KEY_CODES_COUNT];
};

#endif			// !EVENTMANAGER_HPP_
