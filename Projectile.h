#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Spaceship.h"

class Projectile : public Spaceship
{
public:
	Projectile(const float shotAngle, const sf::Vector2f shotStartPosition);
	
	void update(const std::vector<InputEvent>& events) override;
	sf::FloatRect& getBounds() override;

private:
	void updateDuePlayerInputs(const std::vector<InputEvent>& events);
	void updateMovement();

	float m_moveSpeed;

};

#endif //PROJECTILE_H