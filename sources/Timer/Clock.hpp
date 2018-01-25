//
// Clock.hpp for Clock in /home/leroy_h/Perso/myLib/Clock
// 
// Made by romain1 leroy
// Login   <leroy_h@epitech.net>
// 
// Started on  Fri Apr 28 17:31:15 2017 romain1 leroy
// Last update Wed Jun  7 13:07:34 2017 Héloïse de Villepin
//

#ifndef							CLOCK_HPP_
# define						CLOCK_HPP_
# include						"Time.hpp"

namespace						ir
{
  class							Clock
  {
  public:
    Clock();
    ~Clock();
    Time						getElapsedTime(void) const;
    Time						restart(void);
  private:
    std::chrono::time_point<std::chrono::steady_clock>	_start;
  };
}

#endif							// !CLOCK_HPP_
