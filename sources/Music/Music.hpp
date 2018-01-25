//
// Music.hpp for Music in /home/hugo.alfonsi/Tek2/cpp_indie_studio/sources/Music
// 
// Made by Alfonsi Hugo
// Login   <hugo.alfonsi@epitech.net>
// 
// Started on  Mon Jun 12 13:54:50 2017 Alfonsi Hugo
// Last update Tue Jun 13 13:53:19 2017 Alfonsi Hugo
//

#ifndef __MUSIC_HPP__
# define __MUSIC_HPP__

# include <irrKlang.h>
# include <string>

class	Music
{
private:
  irrklang::ISoundEngine	*_engine;
  irrklang::ISound		*_music;
  const char			*_path;

public:
  Music(irrklang::ISoundEngine *, const char *);
  Music(Music const &);
  ~Music();
  Music				&operator=(Music const &);

  void				playMusic();

  irrklang::ISound		*getSound() const;
};

#endif /* !__MUSIC_HPP__ */
