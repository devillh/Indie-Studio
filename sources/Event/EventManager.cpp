//
// EventManager.cpp for Indie Studio in /home/devill_h/back_up/rendu/cpp_indie_studio/sources
// 
// Made by Héloïse de Villepin
// Login   <devill_h@epitech.net>
// 
// Started on  Wed Jun  7 11:39:52 2017 Héloïse de Villepin
// Last update Sat Jun 17 19:30:35 2017 romain1 leroy
//

#include "EventManager.hpp"

bool		EventManager::OnEvent(const irr::SEvent &event)
{
  if (event.EventType == irr::EET_KEY_INPUT_EVENT)
    {
      if (event.KeyInput.PressedDown && !KeyIsDown[event.KeyInput.Key])
	KeyIsPressed[event.KeyInput.Key] = true;
      KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    }
  return (false);
}

bool		EventManager::IsKeyPressed(irr::EKEY_CODE keyCode) const
{
  return (KeyIsPressed[keyCode]);
}

bool		EventManager::IsKeyDown(irr::EKEY_CODE keyCode) const
{
  return (KeyIsDown[keyCode]);
}

void		EventManager::resetKeyIsPressed(void)
{
  for (int i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
    KeyIsPressed[i] = false;
}

EventManager::EventManager()
{
  for(irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
    KeyIsDown[i] = false;
  for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
    KeyIsPressed[i] = false;
  // irr::u32	i;

  // i = 0;
  // while (i < irr::KEY_KEY_CODES_COUNT)
  //   {
  //     KeyIsDown[i] = false;
  //     ++i;
  //   }
}

EventManager::~EventManager()
{}
