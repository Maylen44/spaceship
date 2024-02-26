#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "IGameObject.h"

class Spaceship : public IGameObject
{
public:
	Spaceship();
	virtual ~Spaceship() = default;

	GameObjectType getObjectTyp() override { return ShipType; };

protected:
	const sf::Vector2f m_size;
	sf::Sprite m_sprite;
	const float m_passiveStriveSpeed;
	int m_healthPoints;

};

#endif //SPACESHIP_H