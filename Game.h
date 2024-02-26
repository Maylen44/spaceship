#ifndef GAME_H
#define GAME_H

#include "SharedContent.h"
#include "Renderer.h"
#include "Updater.h"
#include "EventHandler.h"
#include "AssetsManager.h"
#include "IGameObject.h"

class Game
{
public:
	Game();

	void initialize();
	void run();
	void reset();

	void creatObject(const GameObjectType& type,
		int numOfObjects = 1,
		IGameObject* refObject = nullptr);
	void clearObject(int index = -1);

private:
	void progressGameLogic();

	bool m_isPlaying;
	int m_score;

	Renderer m_renderer;
	Updater m_updater;
	EventHandler m_eventHandler;
	AssetsManager m_assetsManager;
	std::vector<IGameObject*> m_gameObjects;
};

#endif //GAME_H