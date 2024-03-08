#include "Updater.h"
#include "PlayerShip.h"
#include "EnemyAlpha.h"
#include "EnemyBeta.h"
#include "Projectile.h"

Updater::Updater()
	: m_deltaClock()
{
}

void Updater::update(std::vector<IGameObject*>& objects, 
					const std::vector<InputEvent>& events)
{
	if (isFrameTime())
	{
		for (auto& firstObject : objects)
		{
			firstObject->update(events);

			if(dynamic_cast<PlayerShip*>(firstObject) ||
				dynamic_cast<EnemyAlpha*>(firstObject) ||
				dynamic_cast<EnemyBeta*>(firstObject) ||
				dynamic_cast<Projectile*>(firstObject))
			{
				for (auto& secondObject : objects)
				{
					if (dynamic_cast<PlayerShip*>(secondObject) ||
						dynamic_cast<EnemyAlpha*>(secondObject) ||
						dynamic_cast<EnemyBeta*>(secondObject) ||
						dynamic_cast<Projectile*>(secondObject))
					{
						manageCollisions(firstObject, secondObject);
					}
				}
			}
			
		}
	}

}

void Updater::resetContent(std::vector<IGameObject*>& objects)
{
	for (auto& object : objects)
	{
		object->resetPosition();
	}
}

void Updater::reserContent(IGameObject* object)
{
	object->resetPosition();
}

bool Updater::isFrameTime()
{
	bool result = false;
	static sf::Time lastFrameTime;
	sf::Time elapsedTime = m_deltaClock.getElapsedTime();
	if (elapsedTime - lastFrameTime >= ConfigManager::instance()->TIME_RATE_001S)
	{
		lastFrameTime = elapsedTime;
		result = true;
	}
	return result;
}

bool Updater::isSFXTime()
{
	bool result = false;
	static sf::Time lastFrameTime;
	sf::Time elapsedTime = m_deltaClock.getElapsedTime();
	if (elapsedTime - lastFrameTime >= ConfigManager::instance()->TIME_RATE_05S)
	{
		lastFrameTime = elapsedTime;
		result = true;
	}
	return result;
}

bool Updater::isSpawnTime3S()
{
	bool result = false;
	static sf::Time lastFrameTime;
	sf::Time elapsedTime = m_deltaClock.getElapsedTime();
	if (elapsedTime - lastFrameTime >= ConfigManager::instance()->TIME_RATE_3S)
	{
		lastFrameTime = elapsedTime;
		result = true;
	}
	return result;
}

bool Updater::isSpawnTime7S()
{
	bool result = false;
	static sf::Time lastFrameTime;
	sf::Time elapsedTime = m_deltaClock.getElapsedTime();
	if (elapsedTime - lastFrameTime >= ConfigManager::instance()->TIME_RATE_7S)
	{
		lastFrameTime = elapsedTime;
		result = true;
	}
	return result;
}

bool Updater::isFireTime1S()
{
	bool result = false;
	static sf::Time lastFrameTime;
	sf::Time elapsedTime = m_deltaClock.getElapsedTime();
	if (elapsedTime - lastFrameTime >= ConfigManager::instance()->TIME_RATE_1S)
	{
		lastFrameTime = elapsedTime;
		result = true;
	}
	return result;
}

bool Updater::isFireTime075S()
{
	bool result = false;
	static sf::Time lastFrameTime;
	sf::Time elapsedTime = m_deltaClock.getElapsedTime();
	if (elapsedTime - lastFrameTime >= ConfigManager::instance()->TIME_RATE_075S)
	{
		lastFrameTime = elapsedTime;
		result = true;
	}
	return result;
}

void Updater::manageCollisions(IGameObject* firstObject, IGameObject* secondObject)
{
	AssetsManager* s_AssetManager = AssetsManager::instance();
	sf::FloatRect firstObjectBounds = firstObject->getBounds();
	sf::FloatRect secondObjectBounds = secondObject->getBounds();
	
	if (firstObject != secondObject)
	{
		if (firstObjectBounds.intersects(secondObjectBounds))
		{
			if (isSFXTime())
			{
				s_AssetManager->playSFX(SFX_CollisionSound);
				firstObject->handleInterraction(secondObjectBounds);
				secondObject->handleInterraction(firstObjectBounds);
			}
		}
	}
}
