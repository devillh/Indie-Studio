//
// Clock.cpp for Clock in /home/leroy_h/Perso/myLib/Clock
// 
// Made by romain1 leroy
// Login   <leroy_h@epitech.net>
// 
// Started on  Fri Apr 28 17:37:48 2017 romain1 leroy
// Last update Sat Apr 29 11:27:27 2017 romain1 leroy
//

#include "Clock.hpp"

namespace	ir
{
  Clock::Clock()
    : _start(std::chrono::steady_clock::now())
  {
  }

  Clock::~Clock()
  {
  }

  Time			Clock::getElapsedTime(void) const
  {
    auto		end(std::chrono::steady_clock::now());
    Time		t(end - _start);

    return (t);
  }

  Time			Clock::restart(void)
  {
    auto		end(std::chrono::steady_clock::now());
    Time		t(end - _start);

    _start = std::chrono::steady_clock::now();
    return (t);
  }
}
