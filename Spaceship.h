#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "IGameObject.h"

class Spaceship : public IGameObject
{
public:
	Spaceship();
	virtual ~Spaceship() = default;

	void draw(sf::RenderWindow& window) override { window.draw(m_sprite); };
	bool isActive() override { if (m_healthPoints <= 0) { return false; } };

	sf::FloatRect& getBounds() override;
	virtual float getRotation() { return m_sprite.getRotation(); };
	virtual sf::Vector2f getPosition() { return m_sprite.getPosition(); };

protected:
	sf::Vector2f m_size;
	sf::Sprite m_sprite;
	const float m_passiveStriveSpeed;
	int m_healthPoints;
};

#endif //SPACESHIP_H