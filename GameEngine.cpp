#include "GameEngine.h"
#include "Background.h"
#include "PlayerShip.h"
#include "EnemyShipTypeA.h"
#include "EnemyShipTypeB.h"
#include "Projectile.h"

void GameEngine::creatObject(const GameObjectType& type, 
							int numOfObjects, 
							IGameObject* refObject)
{
	for (int i = 0; i < numOfObjects; ++i)
	{
		if (type == ShipType) {}
		else if (type == BackgroundType)
		{
			Background* background = new Background(m_assetsManager.getTexture(type), WINDOW_RESOLUTION);
			m_gameObjects.push_back(background);
		}
		else if (type == PlayerType)
		{
			PlayerShip* player = new PlayerShip(m_assetsManager.getTexture(type));
			m_gameObjects.push_back(player);
			m_updater.reserContent(player);
		}
		else if (type == EnemyTypAType)
		{
			EnemyShipTypeA* enemy1 = new EnemyShipTypeA(m_assetsManager.getTexture(type));
			m_gameObjects.push_back(enemy1);
			m_updater.reserContent(enemy1);
		}
		else if (type == EnemyTypBType)
		{
			EnemyShipTypeB* enemy2 = new EnemyShipTypeB(m_assetsManager.getTexture(type));
			m_gameObjects.push_back(enemy2);
			m_updater.reserContent(enemy2);
		}
		else if (type == ProjectileType && refObject != nullptr)
		{
			Projectile* projectile = new Projectile(m_assetsManager.getTexture(type), refObject);
			m_gameObjects.push_back(projectile);
			m_updater.reserContent(projectile);
		}
		else if (type == NotSpecifiedType) {}
	}
	
}

void GameEngine::clearObject(std::vector<IGameObject*>& objectsList, int index)
{
	if (index >= 0)
	{
		delete objectsList[index];
		objectsList.erase(objectsList.begin() + index);
		objectsList.shrink_to_fit();
	}
	else
	{
		for (auto& object : objectsList)
		{
			delete object;
		}
		objectsList.clear();
	}
}
