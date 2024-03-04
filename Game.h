#ifndef GAME_H
#define GAME_H

#include "SharedContent.h"
#include "Renderer.h"
#include "Updater.h"
#include "EventHandler.h"
#include "IGameObject.h"
#include "Projectile.h"

class Game
{
public:
	Game();

	void run();

private:
	void initialize();
	void reset();

	void createObject(GameObjectType type, 
					int numOfObjects = 1,
					float shotAngle = 0.0f,
					sf::Vector2f shotPosition = sf::Vector2f());
	
	void clearObject(int index = -1);

	void progressGameLogic(const std::vector<InputEvent>& events);

	bool m_isPlaying;
	int m_score;
	int m_numEnemys;
	Renderer m_renderer;
	Updater m_updater;
	EventHandler m_eventHandler;
	std::vector<IGameObject*> m_gameObjects;
};


#endif //GAME_H