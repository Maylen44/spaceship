#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "SharedContent.h"
#include "Renderer.h"
#include "EventHandler.h"
#include "Updater.h"
#include "AssetsManager.h"
#include "IGameObject.h"

class GameEngine
{
public:
	void creatObject(const GameObjectType& type, 
					int numOfObjects = 1, 
					IGameObject* refObject = nullptr);
	void clearObject(std::vector<IGameObject*>& objectsList, 
					int index = -1);

	Renderer m_renderer;
	EventHandler m_eventHandler;
	Updater m_updater;
	AssetsManager m_assetsManager;
	std::vector<IGameObject*> m_gameObjects;
};

#endif //GAME_ENGINE_H