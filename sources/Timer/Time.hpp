//
// Time.hpp for Time in /home/leroy_h/Perso/myLib/Time
// 
// Made by romain1 leroy
// Login   <leroy_h@epitech.net>
// 
// Started on  Sat Apr 29 10:40:50 2017 romain1 leroy
// Last update Sat Apr 29 11:15:27 2017 romain1 leroy
//

#ifndef				TIME_HPP_
# define			TIME_HPP_
# include			<chrono>

namespace			ir
{
  class				Time
  {
  public:
    Time();
    Time(std::chrono::nanoseconds const &time);
    Time(std::chrono::microseconds const &time);
    Time(std::chrono::milliseconds const &time);
    Time(std::chrono::seconds const &time);
    Time			&operator=(std::chrono::nanoseconds const &time);
    Time                        &operator=(std::chrono::microseconds const &time);
    Time                        &operator=(std::chrono::milliseconds const &time);
    Time                        &operator=(std::chrono::seconds const &time);
    long int			asNanoseconds(void) const;
    long int			asMicroseconds(void) const;
    long int			asMilliseconds(void) const;
    long int			asSeconds(void) const;
  private:
    std::chrono::nanoseconds	_time;
  };
}

#endif				// !TIME_HPP_
