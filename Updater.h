#ifndef UPDATER_H
#define UPDATER_H

#include "IGameObject.h"

class Updater
{
public:
	Updater();

	void update(const std::vector<IGameObject*>& objects, 
				const InputEvent& keyPress, 
				const InputEvent& mousePress);

	void resetContent(std::vector<IGameObject*>& objects);
	void reserContent(IGameObject* object);

	bool isFrameTime();
	bool isSFXTime();
	bool isSpawnTime3S();
	bool isSpawnTime7S();
	bool isFireTime1S();
	bool isFireTime075S();


private:
	void manageCollisions(const std::vector<IGameObject*>& objects);

	sf::Clock m_deltaClock;
};

#endif //UPDATER_H