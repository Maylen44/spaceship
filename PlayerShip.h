#ifndef PLAYER_SHIP_H
#define PLAYER_SHIP_H

#include "Spaceship.h"

class PlayerShip : public Spaceship
{
public:
	PlayerShip();
	virtual ~PlayerShip() = default;

	void update(const InputEvent& keyPress, const InputEvent& mousePress) override;
	void handleInterraction(sf::FloatRect& refObject) override;
	void draw(sf::RenderWindow& window) override;
	void resetPosition() override;

	GameObjectType getObjectTyp() override { return PlayerType; };
	sf::FloatRect& getBounds() override;
	sf::Vector2f& getPosition() override;
	float getRotation() override { return m_sprite.getRotation(); };
	virtual int getHealthPoints() override { return m_healthPoints; };

private:
	void handleRotation(sf::RenderWindow& window);

	float m_rotationAngle;

};

#endif //PLAYER_SHIP_H