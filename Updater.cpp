#include "Updater.h"

Updater::Updater()
	: m_deltaClock()
{
}

void Updater::update(const std::vector<IGameObject*>& objects, 
					const std::vector<InputEvent>& events)
{
	if (isFrameTime())
	{
		for (auto& firstObject : objects)
		{
			firstObject->update(events);

			if (firstObject->getObjectTyp() != NotSpecifiedType &&
				firstObject->getObjectTyp() != BackgroundType &&
				firstObject->getObjectTyp() != ShipType)
			{
				for (auto& secondObject : objects)
				{
					if (secondObject->getObjectTyp() != NotSpecifiedType &&
						secondObject->getObjectTyp() != BackgroundType &&
						secondObject->getObjectTyp() != ShipType)
					{
						manageCollisions(firstObject, secondObject);
					}
				}
			}
			
		}
	}

	/*
	if (isFireTimeA())
	{
		//fire command to ships
	}

	if (isFireTimeB())
	{
		//fire command to ships
	}
	*/
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
	if (elapsedTime - lastFrameTime >= g_sharedContent->TIME_RATE_001S)
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
	if (elapsedTime - lastFrameTime >= g_sharedContent->TIME_RATE_05S)
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
	if (elapsedTime - lastFrameTime >= g_sharedContent->TIME_RATE_3S)
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
	if (elapsedTime - lastFrameTime >= g_sharedContent->TIME_RATE_7S)
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
	if (elapsedTime - lastFrameTime >= g_sharedContent->TIME_RATE_1S)
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
	if (elapsedTime - lastFrameTime >= g_sharedContent->TIME_RATE_075S)
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
				s_AssetManager->playSFX(CollisionSound);
				firstObject->handleInterraction(secondObjectBounds);
				secondObject->handleInterraction(firstObjectBounds);
			}
		}
	}
}
