#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "IGameObject.h"

class Spaceship : public IGameObject
{
public:
	Spaceship();
	virtual ~Spaceship() = default;

	void draw(sf::RenderWindow& window) override;

	sf::Vector2f& getPosition();
	sf::FloatRect& getBounds() override;
	//float getRotation() { return m_sprite.getRotation(); };
	int getHealthPoints() override { return m_healthPoints; };


protected:
	const sf::Vector2f m_size;
	sf::Sprite m_sprite;
	const float m_passiveStriveSpeed;
	int m_healthPoints;

};

#endif //SPACESHIP_H