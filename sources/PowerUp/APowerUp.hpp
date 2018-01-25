//
// APowerUp.hpp for IndieStudio in /home/leroy_h/rendu/CPP/IndieStudio/cpp_indie_studio/sources/PowerUp
// 
// Made by romain1 leroy
// Login   <leroy_h@epitech.net>
// 
// Started on  Sat Jun 17 14:41:59 2017 romain1 leroy
// Last update Sun Jun 18 21:40:19 2017 romain1 leroy
//

#ifndef					POWERUP_HPP_
# define				POWERUP_HPP_
# include				<irrlicht.h>
# include				<string>
# include				<memory>
# include				<vector>
# include				<utility>

class					APowerUp : public irr::scene::ICollisionCallback
{
public:
  static void				clearAllPowerUp(void);
  static APowerUp			*createPowerUp(irr::scene::ISceneManager *sceneManager,
						       irr::core::vector3df const &pos);
  static void				checkPowerUp(void);
  APowerUp(std::string const &name, std::string const &model,
	   irr::scene::ISceneManager *sceneManager, irr::core::vector3df const &pos);
  ~APowerUp();
  irr::scene::IAnimatedMeshSceneNode	*getModel(void);
  virtual bool				onCollision(const irr::scene::ISceneNodeAnimatorCollisionResponse &animator) = 0;
  void					assignCollision(irr::scene::IAnimatedMeshSceneNode *model);
protected:
  bool					_end;
  irr::scene::IAnimatedMeshSceneNode	*_model;
private:
  static std::vector<std::unique_ptr<APowerUp>> _allPowerUps;
  std::string				_name;
  irr::scene::ISceneManager		*_sceneManager;
  irr::scene::ITriangleSelector		*_selector;
  std::vector<std::pair<irr::scene::IAnimatedMeshSceneNode *, irr::scene::ISceneNodeAnimator *>> _collisionTab;
};

#endif					// !POWERUP_HPP_
