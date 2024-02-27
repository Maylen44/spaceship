#ifndef ENEMY_SHIP_TYPE_B_H
#define ENEMY_SHIP_TYPE_B_H

#include "Spaceship.h"

class EnemyShipTypeB : public Spaceship
{
public:
	EnemyShipTypeB(const sf::Texture& texture);
	virtual ~EnemyShipTypeB() = default;

	void update(const InputEvent& keyPress, const InputEvent& mousePress) override;
	void handleInterraction(const Interraction& interraction, sf::FloatRect& refObject) override;
	void draw(sf::RenderWindow& window) override;
	void resetPosition() override;

private:
	void updateDuePlayerInputs(const InputEvent& keyPress, const InputEvent& mousePress);
	void updateRotation(sf::Vector2f& directionToMiddle, const float length);
	void updateFollowBehavior(const sf::Vector2f& boundaries, const sf::Vector2f& directionToMiddle, const float length);
	
	GameObjectType getObjectTyp() override { return EnemyTypeBType; };
	sf::FloatRect& getBounds() override;
	sf::Vector2f& getPosition() override;
	float getRotation() override { return m_sprite.getRotation(); };
	virtual int getHealthPoints() override { return m_healthPoints; };

	const float m_baseSpeed;
	const float m_speed;
	const float m_boostMultiplier;
	float m_rotationSpeed;
	const float m_reactionDelay;
	sf::Vector2f m_stopZoneRange;
	const float m_spawnOffset;

};


#endif //ENEMY_SHIP_TYPE_B_H