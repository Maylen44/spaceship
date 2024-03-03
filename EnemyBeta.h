#ifndef ENEMY_BETA_H
#define ENEMY_BETA_H

#include "EnemyShip.h"

class EnemyBeta : public EnemyShip
{
public:
	EnemyBeta();
	virtual ~EnemyBeta() = default;
	void handleInterraction(sf::FloatRect& refObject) override;

private:
	GameObjectType getObjectTyp() override { return EnemyBetaType; };
};

#endif //ENEMY_BETA_H