#ifndef ENEMY_ALPHA_H
#define ENEMY_ALPHA_H

#include "EnemyShip.h"

class EnemyAlpha : public EnemyShip
{
public:
	EnemyAlpha();
	virtual ~EnemyAlpha() = default;
	void handleInterraction(sf::FloatRect& refObject) override;

private:
	GameObjectType getObjectTyp() override { return EnemyAlphaType; };
};

#endif //ENEMY_ALPHA_H