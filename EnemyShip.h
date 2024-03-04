#ifndef ENEMYSHIP_H
#define ENEMYSHIP_H

#include "Spaceship.h"

class EnemyShip : public Spaceship
{
public:
	EnemyShip();
	virtual ~EnemyShip() = default;

protected:
	void update(const std::vector<InputEvent>& events) override;
	void resetPosition() override;

	void updateDuePlayerInputs(const std::vector<InputEvent>& events);
	void updateRotation(sf::Vector2f& directionToMiddle, const float length);
	void updateFollowBehavior(const sf::Vector2f& boundaries, const sf::Vector2f& directionToMiddle, const float length);

	float m_baseSpeed;
	float m_speed;
	const float m_boostMultiplier;
	float m_rotationSpeed;
	const float m_reactionDelay;
	sf::Vector2f m_stopZoneRange;
	const float m_spawnOffset;
};

#endif //ENEMYSHIP_H