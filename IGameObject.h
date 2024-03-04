#ifndef I_GAME_OBJECT_H
#define I_GAME_OBJECT_H

#include "SharedContent.h"
#include "AssetsManager.h"

enum GameObjectType
{
	GameObjectType_Background,
	GameObjectType_PlayerShip,
	GameObjectType_EnemyAlpha,
	GameObjectType_EnemyBeta,
	GameObjectType_Projectile,
	GameObjectType_MAX
};

class IGameObject
{
public:
	virtual ~IGameObject() = default;

	virtual void update(const std::vector<InputEvent>& events) {};
	virtual void handleInterraction(sf::FloatRect& refObject) {};
	virtual void draw(sf::RenderWindow& window) {};
	virtual void resetPosition() {};

	virtual bool isActive() { return true; };

	//tmp fields! delete after managing projectiles!!!
	virtual sf::FloatRect& getBounds() { return m_tmp; };

private:
	sf::FloatRect m_tmp;
};

#endif //I_GAME_OBJECT_H