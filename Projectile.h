#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "IGameObject.h"

class Projectile : public IGameObject
{
public:
	Projectile(const sf::Texture& texture, IGameObject* refObject = nullptr);
	virtual ~Projectile() = default;

	void update(const KeyboardEvent& keyPress, const MouseEvent& mousePress) override;
	void handleInterraction(const Interraction& interraction, sf::FloatRect& refObject) override;
	void draw(sf::RenderWindow& window) override;

	GameObjectType getObjectTyp() override { return ProjectileType; };
	sf::FloatRect& getBounds() override;
	virtual int getHealthPoints() override { return m_healthPoints; };

private:
	void updateDuePlayerInputs(const KeyboardEvent& keyPress, const MouseEvent& mousePress);
	void updateMovement();

	int m_healthPoints;
	float m_shotAngle;
	float m_moveSpeed;
	
	const sf::Vector2f m_size;
	sf::Sprite m_sprite;

};

#endif //PROJECTILE_H