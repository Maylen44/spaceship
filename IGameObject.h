#ifndef I_GAME_OBJECT_H
#define I_GAME_OBJECT_H

#include "SharedContent.h"
#include "AssetsManager.h"

enum GameObjectType
{
	NotSpecifiedType,
	BackgroundType,
	ShipType,
	PlayerType,
	EnemyType,
	EnemyAlphaType,
	EnemyBetaType,
	ProjectileType
};

class IGameObject
{
public:
	virtual ~IGameObject() = default;

	virtual void update(const std::vector<InputEvent>& events) {};
	virtual void handleInterraction(sf::FloatRect& refObject) {};
	virtual void draw(sf::RenderWindow& window) {};
	virtual void resetPosition() {};
	
	virtual GameObjectType getObjectTyp() { return NotSpecifiedType; };

	//tmp fields! delete after managing projectiles!!!
	virtual sf::FloatRect& getBounds() { return m_tmp; };
	virtual int getHealthPoints() { return 0; };

private:
	sf::FloatRect m_tmp;
};

#endif //I_GAME_OBJECT_H