//
// Character.hpp for indie Studio in /home/leroy_h/rendu/CPP/IndieStudio/home/Character
// 
// Made by romain1 leroy
// Login   <leroy_h@epitech.net>
// 
// Started on  Mon Jun  5 13:38:25 2017 romain1 leroy
// Last update Sun Jun 18 18:15:43 2017 Héloïse de Villepin
//

#ifndef					CHARACTER_HPP_
# define				CHARACTER_HPP_
# include				<irrlicht.h>
# include				<memory>
# include				<iostream>
# include				<vector>
# include				<utility>
# include				"EventManager.hpp"
# include				"Bomb.hpp"
# include				"Clock.hpp"
# include				"Map.hpp"
# include				"CrossExplo.hpp"
# include				"APowerUp.hpp"

class					Bomb;

enum					MoveDirection
  {
    NONE,
    LEFT,
    RIGHT,
    UP,
    BACK
  };

class					CharacterControl
{
public:
  CharacterControl();
  CharacterControl(CharacterControl const &obj);
  ~CharacterControl();
  CharacterControl			&operator=(CharacterControl const &obj);
  void					setMoveUp(irr::EKEY_CODE const moveUp);
  void					setMoveDown(irr::EKEY_CODE const moveDown);
  void					setMoveLeft(irr::EKEY_CODE const moveLeft);
  void					setMoveRight(irr::EKEY_CODE const moveRight);
  void					setPlaceBomb(irr::EKEY_CODE const placeBomb);
  irr::EKEY_CODE			getMoveUp(void) const;
  irr::EKEY_CODE			getMoveDown(void) const;
  irr::EKEY_CODE			getMoveLeft(void) const;
  irr::EKEY_CODE			getMoveRight(void) const;
  irr::EKEY_CODE			getPlaceBomb(void) const;
private:
  irr::EKEY_CODE			_moveUp;
  irr::EKEY_CODE			_moveDown;
  irr::EKEY_CODE			_moveLeft;
  irr::EKEY_CODE			_moveRight;
  irr::EKEY_CODE			_placeBomb;
};

class					Character
{
public:
  static Character			*getCharacterFromNode(irr::scene::ISceneNode const *node);
  Character(EventManager const &receiver,
	    irr::IrrlichtDevice *device,
	    irr::core::vector3df const &pos,
	    Map &map,
	    std::string const &pathTexture);
  ~Character();
  void					addBomb(int const nbr);
  void					addSpeed(int const nbr);
  void					addGod(int const nbr);
  void					setEnemy(Character *);
  bool					isDead(void) const;
  void					update(void);
  irr::scene::IAnimatedMeshSceneNode	*getModel(void);
  CharacterControl			&control(void);
  void					assignCollision(irr::scene::IAnimatedMeshSceneNode *node);
private:
  static std::vector<std::pair<Character *, irr::scene::ISceneNode const *>> _allCharacters;
  bool					moveLeft(void);
  bool					moveRight(void);
  bool					moveUp(void);
  bool					moveDown(void);
  void					placeBomb(void);
  bool					checkDeath(int, int, int, int);
  void					checkBombs(void);
  void					checkExplosions(void);
  EventManager const			&_receiver;
  irr::scene::IAnimatedMeshSceneNode	*_model;
  MoveDirection				_moveDirection;
  irr::f32				_speed;
  irr::IrrlichtDevice			*_device;
  irr::u32				_now;
  irr::u32				_then;
  irr::f32				_frameDeltaTime;
  std::vector<std::pair<std::unique_ptr<Bomb>, ir::Clock>> _bombTab;
  std::vector<std::pair<std::unique_ptr<CrossExplo>, ir::Clock>> _exploTab;
  unsigned int				_maxBomb;
  long int				_bombTimer;
  std::string				_pathTexture;
  unsigned int				_bombPower;
  Map					&_map;
  CharacterControl			_control;
  bool					_dead;
  Character				*_enemy;
  bool					_god;
  int					_godTimer;
  ir::Clock				_godClock;
  irr::scene::ITriangleSelector		*_selector;
  std::vector<std::pair<irr::scene::IAnimatedMeshSceneNode *, irr::scene::ISceneNodeAnimator *>> _collisionTab;
};

#endif					// !CHARACTER_HPP_
