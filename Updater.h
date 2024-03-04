#ifndef UPDATER_H
#define UPDATER_H

#include "IGameObject.h"

class Updater
{
public:
	Updater();

	void update(std::vector<IGameObject*>& objects, 
				const std::vector<InputEvent>& events);

	void resetContent(std::vector<IGameObject*>& objects);
	void reserContent(IGameObject* object);

	bool isFrameTime();
	bool isSFXTime();
	bool isSpawnTime3S();
	bool isSpawnTime7S();
	bool isFireTime1S();
	bool isFireTime075S();


private:
	void manageCollisions(IGameObject* firstObject, IGameObject* secondObject);

	sf::Clock m_deltaClock;
};

#endif //UPDATER_H