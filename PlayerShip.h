#ifndef PLAYER_SHIP_H
#define PLAYER_SHIP_H

#include "Spaceship.h"
#include "IObserver.h"

class PlayerShip : public Spaceship, public IObserver
{
public:
	PlayerShip();
	virtual ~PlayerShip() = default;

	void update(const std::vector<InputEvent>& events) override;
	void handleInterraction(sf::FloatRect& refObject) override;
	void draw(sf::RenderWindow& window) override;
	void resetPosition() override;

private:
	void handleRotation(sf::RenderWindow& window);

	float m_rotationAngle;

};

#endif //PLAYER_SHIP_H