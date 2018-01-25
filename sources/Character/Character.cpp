//
// Character.cpp for indie studio in /home/leroy_h/rendu/CPP/IndieStudio/home/Character
// 
// Made by romain1 leroy
// Login   <leroy_h@epitech.net>
// 
// Started on  Mon Jun  5 13:42:46 2017 romain1 leroy
// Last update Sun Jun 18 21:42:48 2017 romain1 leroy
//

#include <irrlicht.h>
#include <stdexcept>
#include <algorithm>
#include "Character.hpp"

std::vector<std::pair<Character *, irr::scene::ISceneNode const *>> Character::_allCharacters;

CharacterControl::CharacterControl()
  : _moveUp(irr::KEY_KEY_Z), _moveDown(irr::KEY_KEY_S),
    _moveLeft(irr::KEY_KEY_Q), _moveRight(irr::KEY_KEY_D),
    _placeBomb(irr::KEY_SPACE)
{
}

CharacterControl::CharacterControl(CharacterControl const &obj)
  : _moveUp(obj._moveUp), _moveDown(obj._moveDown),
    _moveLeft(obj._moveLeft), _moveRight(obj._moveRight),
    _placeBomb(obj._placeBomb)
{
}

CharacterControl::~CharacterControl()
{
}

CharacterControl	&CharacterControl::operator=(CharacterControl const &obj)
{
  _moveUp = obj._moveUp;
  _moveDown = obj._moveDown;
  _moveLeft = obj._moveLeft;
  _moveRight = obj._moveRight;
  _placeBomb = obj._placeBomb;
}

void	CharacterControl::setMoveUp(irr::EKEY_CODE const moveUp)
{
  _moveUp = moveUp;
}

void	CharacterControl::setMoveDown(irr::EKEY_CODE const moveDown)
{
  _moveDown = moveDown;
}

void	CharacterControl::setMoveLeft(irr::EKEY_CODE const moveLeft)
{
  _moveLeft = moveLeft;
}

void	CharacterControl::setMoveRight(irr::EKEY_CODE const moveRight)
{
  _moveRight = moveRight;
}

void	CharacterControl::setPlaceBomb(irr::EKEY_CODE const placeBomb)
{
  _placeBomb = placeBomb;
}

irr::EKEY_CODE	CharacterControl::getMoveUp(void) const
{
  return (_moveUp);
}

irr::EKEY_CODE	CharacterControl::getMoveDown(void) const
{
  return (_moveDown);
}

irr::EKEY_CODE	CharacterControl::getMoveLeft(void) const
{
  return (_moveLeft);
}

irr::EKEY_CODE	CharacterControl::getMoveRight(void) const
{
  return (_moveRight);
}

irr::EKEY_CODE	CharacterControl::getPlaceBomb(void) const
{
  return (_placeBomb);
}

Character	*Character::getCharacterFromNode(irr::scene::ISceneNode const *node)
{
  auto it = std::find_if(_allCharacters.begin(), _allCharacters.end(),
			 [node](auto &val) {
			   return (val.second == node);
			 });
  if (it == _allCharacters.end())
    return (NULL);
  return (it->first);
}

Character::Character(EventManager const &receiver,
		     irr::IrrlichtDevice *device,
		     irr::core::vector3df const &pos,
		     Map &map,
		     std::string const &pathTexture)
  : _receiver(receiver), _device(device), _map(map), _dead(false), _enemy(NULL), _pathTexture(pathTexture)
{
  _model = _device->getSceneManager()->addAnimatedMeshSceneNode(_device->getSceneManager()->getMesh("media/models/player.md2"));
  if (!_model)
    throw std::runtime_error("Failed to create a new character.");
  _model->setMaterialTexture(0, device->getVideoDriver()->getTexture(_pathTexture.c_str()));
  _model->setMD2Animation(irr::scene::EMAT_STAND);
  _model->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  _model->setPosition(pos);
  _model->setName("Player");
  _speed = 15.f;
  _then = _device->getTimer()->getTime();
  _maxBomb = 1;
  _bombTimer = 2000;
  _bombPower = 1;
  _selector = _device->getSceneManager()->createOctreeTriangleSelector(_model->getMesh(),
								       _model, 128);
  _model->setTriangleSelector(_selector);
  _allCharacters.push_back({this, _model});
}

Character::~Character()
{
  auto it = std::find_if(_allCharacters.begin(), _allCharacters.end(),
			 [this](auto &val) {
			   return (val.first == this);
			 });
  if (it != _allCharacters.end())
    _allCharacters.erase(it);
  _selector->drop();
  _model->removeAnimators();
  _device->getSceneManager()->addToDeletionQueue(_model);
}

void					Character::assignCollision(irr::scene::IAnimatedMeshSceneNode *model)
{
  irr::scene::ISceneNodeAnimator	*anim;

  anim = _device->getSceneManager()->createCollisionResponseAnimator(_selector, model,
									   irr::core::vector3df(10, 10, 10),
									   irr::core::vector3df(0, 0, 0),
									   irr::core::vector3df(0, 0, 0));
  model->addAnimator(anim);
  anim->drop();
  _collisionTab.push_back({model, anim});
}

void	Character::addBomb(int const nbr)
{
  _maxBomb += nbr;
}

void	Character::addSpeed(int const nbr)
{
  _speed += nbr;
}

void	Character::addGod(int const nbr)
{
  _god = true;
  _godTimer = nbr;
  _godClock.restart();
}

bool	Character::isDead(void) const
{
  return (_dead);
}

void	Character::setEnemy(Character *obj)
{
  _enemy = obj;
}

void	Character::update(void)
{
  if (_godClock.getElapsedTime().asSeconds() > _godTimer)
    _god = false;
  _now = _device->getTimer()->getTime();
  _frameDeltaTime = static_cast<irr::f32>(_now - _then) / 100.f;
  _then = _now;
  if (!(moveLeft() || moveRight() || moveUp() || moveDown()) &&
      _moveDirection != NONE)
    {
      _model->setMD2Animation(irr::scene::EMAT_STAND);
      _moveDirection = NONE;
    }
  placeBomb();
  checkBombs();
  checkExplosions();
}

bool			Character::moveLeft(void)
{
  irr::core::vector3df	pos;

  if (_receiver.IsKeyDown(_control.getMoveLeft()))
    {
      pos = _model->getPosition();
      if (_moveDirection != LEFT)
	{
	  _model->setMD2Animation(irr::scene::EMAT_RUN);
	  _model->setRotation(irr::core::vector3df(0.0, 180.0, 0.0));
	  _moveDirection = LEFT;
	}
      pos.X -= _speed * _frameDeltaTime;
      _model->setPosition(pos);
      return (true);
    }
  return (false);
}

bool			Character::moveRight(void)
{
  irr::core::vector3df  pos;

  if (_receiver.IsKeyDown(_control.getMoveRight()))
    {
      pos = _model->getPosition();
      if (_moveDirection != RIGHT)
	{
	  _model->setMD2Animation(irr::scene::EMAT_RUN);
	  _model->setRotation(irr::core::vector3df(0.0, 0.0, 0.0));
	  _moveDirection = RIGHT;
	}
      pos.X += _speed *_frameDeltaTime;
      _model->setPosition(pos);
      return (true);
    }
  return (false);
}

bool			Character::moveUp(void)
{
  irr::core::vector3df  pos;

  if (_receiver.IsKeyDown(_control.getMoveUp()))
    {
      pos = _model->getPosition();
      if (_moveDirection != UP)
	{
	  _model->setMD2Animation(irr::scene::EMAT_RUN);
	  _model->setRotation(irr::core::vector3df(0.0, 270.0, 0.0));
	  _moveDirection = UP;
	}
      pos.Z += _speed *_frameDeltaTime;
      _model->setPosition(pos);
      return (true);
    }
  return (false);
}

bool			Character::moveDown(void)
{
  irr::core::vector3df  pos;
  
  if (_receiver.IsKeyDown(_control.getMoveDown()))
    {
      pos = _model->getPosition();
      if (_moveDirection != BACK)
	{
	  _model->setMD2Animation(irr::scene::EMAT_RUN);
	  _model->setRotation(irr::core::vector3df(0.0, 90.0, 0.0));
	  _moveDirection = BACK;
	}
      pos.Z -= _speed *_frameDeltaTime;
      _model->setPosition(pos);
      return (true);
    }
  return (false);
}

void		Character::placeBomb()
{
  if (_receiver.IsKeyPressed(_control.getPlaceBomb()) && _bombTab.size() < _maxBomb)
    {
      _bombTab.push_back({std::unique_ptr<Bomb>(new Bomb(_model, _device->getSceneManager(), _device->getVideoDriver())),
	    ir::Clock()});
      if (_enemy)
	_bombTab[_bombTab.size() - 1].first->assignCollision(_enemy->getModel());
    }
}

bool		Character::checkDeath(int char_x, int char_z, int bom_x, int bom_z)
{
  if (((char_x <= bom_x && char_x >= bom_x - 75) && (char_z >= bom_z && char_z <= bom_z + 25)) ||
      ((char_x <= bom_x && char_x >= bom_x - 75) && (char_z <= bom_z && char_z >= bom_z - 25)) ||
      ((char_x >= bom_x && char_x <= bom_x + 75) && (char_z >= bom_z && char_z <= bom_z + 25)) ||
      ((char_x >= bom_x && char_x <= bom_x + 75) && (char_z <= bom_z && char_z >= bom_z - 25)) ||
      ((char_x <= bom_x && char_x >= bom_x - 25) && (char_z >= bom_z && char_z <= bom_z + 75)) ||
      ((char_x <= bom_x && char_x >= bom_x - 25) && (char_z <= bom_z && char_z >= bom_z - 75)) ||
      ((char_x >= bom_x && char_x <= bom_x + 25) && (char_z >= bom_z && char_z <= bom_z + 75)) ||
      ((char_x >= bom_x && char_x <= bom_x + 25) && (char_z <= bom_z && char_z >= bom_z - 75)))
    return (true);
  return (false);
}

void		Character::checkBombs()
{
  unsigned int	i;

  i = 0;
  while (i < _bombTab.size())
    {
      if (_bombTab[i].second.getElapsedTime().asMilliseconds() >= _bombTimer)
	{
	  _bombTab[i].first->blowUp(_map, _bombPower, this, _enemy);
	  _exploTab.push_back({std::unique_ptr<CrossExplo>(new CrossExplo(_device,
									  _bombTab[i].first->getPos(),
									  _bombPower)),
		ir::Clock()});
	  if (checkDeath(_model->getPosition().X, _model->getPosition().Z,
			 _bombTab[i].first->getPos().X, _bombTab[i].first->getPos().Z) && !_god)
	    _dead = true;
	  if (_enemy && checkDeath(_enemy->_model->getPosition().X, _enemy->_model->getPosition().Z,
				   _bombTab[i].first->getPos().X, _bombTab[i].first->getPos().Z) && !_enemy->_god)
	    _enemy->_dead = true;
	  _bombTab.erase(_bombTab.begin() + i);
	}
      ++i;
    }
}

void		Character::checkExplosions()
{
  unsigned int	i;

  i = 0;
  while (i < _exploTab.size())
    {
      if (_exploTab[i].second.getElapsedTime().asMilliseconds() >= 200)
	_exploTab.erase(_exploTab.begin() + i);
      ++i;
    }
}

irr::scene::IAnimatedMeshSceneNode	*Character::getModel(void)
{
  return (_model);
}

CharacterControl	&Character::control(void)
{
  return (_control);
}
