#include "Updater.h"

Updater::Updater()
	: m_deltaClock()
{
}

void Updater::update(const std::vector<IGameObject*>& objects, 
					const KeyboardEvent & keyPress, 
					const MouseEvent & mousePress)
{
	if (isFrameTime())
	{
		for (auto& object : objects)
		{
			object->update(keyPress, mousePress);
		}
		manageCollisions(objects);
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
	if (elapsedTime - lastFrameTime >= g_sharedContent->FRAME_RATE)
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
	if (elapsedTime - lastFrameTime >= g_sharedContent->RATE_05S)
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
	if (elapsedTime - lastFrameTime >= g_sharedContent->RATE_3S)
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
	if (elapsedTime - lastFrameTime >= g_sharedContent->RATE_7S)
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
	if (elapsedTime - lastFrameTime >= g_sharedContent->RATE_1S)
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
	if (elapsedTime - lastFrameTime >= g_sharedContent->RATE_075S)
	{
		lastFrameTime = elapsedTime;
		result = true;
	}
	return result;
}

void Updater::manageCollisions(const std::vector<IGameObject*>& objects)
{
	sf::FloatRect firstObjectBounds;
	sf::FloatRect secondObjectBounds;

	for (auto& firstObject : objects)
	{
		if (firstObject->getObjectTyp() != NotSpecifiedType &&
			firstObject->getObjectTyp() != BackgroundType &&
			firstObject->getObjectTyp() != ShipType)
		{
			firstObjectBounds = firstObject->getBounds();

			for (auto& secondObject : objects)
			{
				if (secondObject->getObjectTyp() != NotSpecifiedType &&
					secondObject->getObjectTyp() != BackgroundType &&
					secondObject->getObjectTyp() != ShipType)
				{
					if (firstObject != secondObject)
					{
						secondObjectBounds = secondObject->getBounds();

						if (firstObjectBounds.intersects(secondObjectBounds))
						{
							firstObject->handleInterraction(ObjectsCollision, secondObjectBounds);
							secondObject->handleInterraction(ObjectsCollision, firstObjectBounds);
							break;
						}
					}
				}
			}
		}
	}
}