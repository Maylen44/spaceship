#include "Game.h"
#include "AssetsManager.h"
#include "Background.h"
#include "PlayerShip.h"
#include "EnemyAlpha.h"
#include "EnemyBeta.h"
#include "Projectile.h"

SharedContent* g_sharedContent = nullptr;

Game::Game()
	: m_isPlaying(false)
	, m_score(0)
	, m_numEnemys(0)
	, m_renderer()
	, m_updater()
	, m_eventHandler()
	, m_gameObjects()
{
	if (g_sharedContent == nullptr)
	{
		g_sharedContent = new SharedContent();
	}
}

void Game::run()
{
	initialize();
	AssetsManager* s_AssetManager = AssetsManager::instance();
	std::vector<InputEvent> events(3, InputEvent_NoInput);

	while (m_isPlaying)
	{
		m_eventHandler.setEvents(events, m_renderer.pollWindowEvent());

		switch (events[0])
		{
		case InputEvent_ESC:
			m_isPlaying = false;
			clearObject();
			m_renderer.closeWindow();
			break;
		case InputEvent_Restart:
			if (m_updater.isSFXTime())
			{
				s_AssetManager->playSFX(SFX_RestartSound);
			}
			reset();
			break;
		default:
			break;
		}
		m_updater.update(m_gameObjects, events);
		progressGameLogic(events);

		s_AssetManager->editText(Text::Text_Score, "Score: " + std::to_string(m_score));
		m_renderer.renderContent(m_gameObjects);
		
	}
}

void Game::initialize()
{
	m_isPlaying = true;
	m_score = 0;
	createObject(GameObjectType_Background, 1);
	createObject(GameObjectType_PlayerShip, 1);
	createObject(GameObjectType_EnemyAlpha, 3);
	createObject(GameObjectType_EnemyBeta, 2);
	m_updater.resetContent(m_gameObjects);
}

void Game::reset()
{
	m_numEnemys = 0;
	clearObject();
	initialize();
}

void Game::createObject(GameObjectType type, int numOfObjects, float shotAngle, sf::Vector2f shotPosition)
{
	switch (type)
	{
	case GameObjectType_Background:
		for (int i = 0; i < numOfObjects; ++i)
		{
			Background* newObject = new Background();
			m_gameObjects.push_back(newObject);
		}
		break;
	case GameObjectType_PlayerShip:
		for (int i = 0; i < numOfObjects; ++i)
		{
			PlayerShip* newObject = new PlayerShip();
			m_gameObjects.push_back(newObject);
		}
		break;
	case GameObjectType_EnemyAlpha:
		for (int i = 0; i < numOfObjects; ++i)
		{
			EnemyAlpha* newObject = new EnemyAlpha();
			m_gameObjects.push_back(newObject);
		}
		break;
	case GameObjectType_EnemyBeta:
		for (int i = 0; i < numOfObjects; ++i)
		{
			EnemyBeta* newObject = new EnemyBeta();
			m_gameObjects.push_back(newObject);
		}
		break;
	case GameObjectType_Projectile:
		for (int i = 0; i < numOfObjects; ++i)
		{
			Projectile* newObject = new Projectile(shotAngle, shotPosition);
			m_gameObjects.push_back(newObject);
		}
		break;
	default:
		break;
	}
}

void Game::clearObject(int index)
{
	if (index >= 0)
	{
		delete m_gameObjects[index];
		m_gameObjects.erase(m_gameObjects.begin() + index);
		m_gameObjects.shrink_to_fit();
	}
	else
	{
		for (auto& object : m_gameObjects)
		{
			delete object;
		}
		m_gameObjects.clear();
	}
}

void Game::progressGameLogic(const std::vector<InputEvent>& events)
{
	AssetsManager* s_AssetManager = AssetsManager::instance();

	for (int i = 0; i < m_gameObjects.size(); ++i)
	{
		if (dynamic_cast<PlayerShip*>(m_gameObjects[i]))
		{
			if (!m_gameObjects[i]->isActive())
			{
				reset();
			}
			if ((events[2] == InputEvent_MouseLeftAndRight) ||
				(events[2] == InputEvent_MouseLeft))
			{
				if (m_updater.isSFXTime())
				{
					createObject(GameObjectType_Projectile,
								1,
								dynamic_cast<Spaceship*>(m_gameObjects[i])->getRotation(),
								dynamic_cast<Spaceship*>(m_gameObjects[i])->getPosition());
				}
			}
		}
		else if (dynamic_cast<EnemyAlpha*>(m_gameObjects[i]))
		{
			if (!m_gameObjects[i]->isActive())
			{
				clearObject(i);
				--m_numEnemys;
				--i;
				m_score += 100;
			}
			if (m_updater.isFireTime1S())
			{
				createObject(GameObjectType_Projectile,
					1,
					dynamic_cast<Spaceship*>(m_gameObjects[i])->getRotation(),
					dynamic_cast<Spaceship*>(m_gameObjects[i])->getPosition());
			}
		}
		else if (dynamic_cast<EnemyBeta*>(m_gameObjects[i]))
		{
			if (!m_gameObjects[i]->isActive())
			{
				clearObject(i);
				--m_numEnemys;
				--i;
				m_score += 200;
			}
			if (m_updater.isFireTime075S())
			{
				createObject(GameObjectType_Projectile,
					1,
					dynamic_cast<Spaceship*>(m_gameObjects[i])->getRotation(),
					dynamic_cast<Spaceship*>(m_gameObjects[i])->getPosition());
			}
		}
		else if (dynamic_cast<Projectile*>(m_gameObjects[i]))
		{
			if (!m_gameObjects[i]->isActive())
			{
				clearObject(i);
				--i;
			}
			
			/*
			else if (m_gameObjects[i]->getBounds().getPosition().x > g_sharedContent->WINDOW_RESOLUTION.x ||
				m_gameObjects[i]->getBounds().getPosition().y > g_sharedContent->WINDOW_RESOLUTION.y ||
				m_gameObjects[i]->getBounds().getPosition().x < 0 ||
				m_gameObjects[i]->getBounds().getPosition().y < 0)
			{
				clearObject(i);
				--i;
			}
			*/
		}

		if (m_numEnemys <= 2)
		{
			if (m_updater.isSpawnTime3S())
			{
				createObject(GameObjectType_EnemyAlpha, 1);
				m_numEnemys++;
			}
			if (m_updater.isSpawnTime7S())
			{
				createObject(GameObjectType_EnemyBeta, 1);
				m_numEnemys++;
			}
		}
		else if (m_numEnemys <= 14)
		{
			if (m_updater.isSpawnTime3S())
			{
				createObject(GameObjectType_EnemyAlpha, 1);
				m_numEnemys++;
			}
			if (m_updater.isSpawnTime7S())
			{
				createObject(GameObjectType_EnemyBeta, 1);
				m_numEnemys++;
			}
		}
	}
	
}
