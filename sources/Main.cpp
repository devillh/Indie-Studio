//
// main.cpp for irrlicht in /home/leroy_h/rendu/CPP/IndieStudio/home
// 
// Made by romain1 leroy
// Login   <leroy_h@epitech.net>
// 
// Started on  Wed May 24 15:48:24 2017 romain1 leroy
// Last update Sun Jun 18 18:27:47 2017 Héloïse de Villepin
//

#include <irrlicht.h>
#include <iostream>
#include "Window.hpp"

int					main(void)
{
  try
    {
      Window				Win;

      Win.running();
    }
  catch (std::exception e)
    {
      std::cout << e.what() << std::endl;
      return (84);
    }
  return (0);
}
