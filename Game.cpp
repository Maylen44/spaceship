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

void Game::initialize()
{
	m_isPlaying = true;
	m_score = 0;
	creatObject(BackgroundType);
	creatObject(PlayerType);
	creatObject(EnemyAlphaType, 3);
	creatObject(EnemyBetaType, 2);
	m_updater.resetContent(m_gameObjects);
}

void Game::run()
{
	initialize();
	AssetsManager* s_AssetManager = AssetsManager::instance();
	std::vector<InputEvent> events(3, NoInput);

	while (m_isPlaying)
	{
		m_eventHandler.setEvents(events, m_renderer.pollWindowEvent());

		switch (events[0])
		{
		case ESC:
			m_isPlaying = false;
			clearObject();
			m_renderer.closeWindow();
			break;
		case Restart:
			if (m_updater.isSFXTime())
			{
				s_AssetManager->playSFX(RestartSound);
			}
			reset();
			break;
		default:
			break;
		}
		m_updater.update(m_gameObjects, events);
		progressGameLogic(events);
		m_renderer.renderContent(m_gameObjects);
		
	}
}

void Game::reset()
{
	m_numEnemys = 0;
	clearObject();
	initialize();
}

void Game::creatObject(const GameObjectType& type, int numOfObjects, IGameObject* refObject)
{
	if (type == BackgroundType)
	{
		for (int i = 0; i < numOfObjects; ++i)
		{
			Background* background = new Background();
			m_gameObjects.push_back(background);
		}
	}
	else if (type == PlayerType)
	{
		for (int i = 0; i < numOfObjects; ++i)
		{ 
			PlayerShip* player = new PlayerShip();
			m_gameObjects.push_back(player);
		}
	}
	else if (type == EnemyAlphaType)
	{
		for (int i = 0; i < numOfObjects; ++i)
		{
			EnemyAlpha* enemy1 = new EnemyAlpha();
			m_gameObjects.push_back(enemy1);
		}
		m_numEnemys += numOfObjects;
	}
	else if (type == EnemyBetaType)
	{
		for (int i = 0; i < numOfObjects; ++i)
		{
			EnemyBeta* enemy2 = new EnemyBeta();
			m_gameObjects.push_back(enemy2);
		}
		m_numEnemys += numOfObjects;
	}
	else if (type == ProjectileType)
	{
		for (int i = 0; i < numOfObjects; ++i)
		{
			Projectile* projectile = new Projectile(refObject);
			m_gameObjects.push_back(projectile);
		}
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

	GameObjectType type;

	for (int i = 0; i < m_gameObjects.size(); ++i)
	{
		type = m_gameObjects[i]->getObjectTyp();

		switch (type)
		{
		case ShipType:
			break;
		case BackgroundType:
			break;
		case PlayerType:
			s_AssetManager->TXT_HEALTHPOINTS_PLAYER.setString("HP: " + std::to_string(m_gameObjects[i]->getHealthPoints()));
			if (m_gameObjects[i]->getHealthPoints() <= 0)
			{
				reset();
			}
			if ((events[2] == MouseLeftAndRight) || (events[2] == MouseLeft))
			{
				if (m_updater.isSFXTime())
				{
					creatObject(ProjectileType, 1, m_gameObjects[i]);
				}
			}
			
			break;
		case EnemyAlphaType:
			if (m_gameObjects[i]->getHealthPoints() <= 0)
			{
				clearObject(i);
				--m_numEnemys;
				--i;
				m_score += 100;
			}
			if (m_updater.isFireTime1S())
			{
				creatObject(ProjectileType, 1, m_gameObjects[i]);
			}
			break;
		case EnemyBetaType:
			if (m_gameObjects[i]->getHealthPoints() <= 0)
			{
				clearObject(i);
				--m_numEnemys;
				--i;
				m_score += 200;
			}
			if (m_updater.isFireTime075S())
			{
				creatObject(ProjectileType, 1, m_gameObjects[i]);
			}
			break;
		case ProjectileType:
			if (m_gameObjects[i]->getHealthPoints() <= 0)
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
			break;
		case NotSpecifiedType:
			break;
		default:
			break;
		}

		if (m_numEnemys <= 2)
		{
			if (m_updater.isSpawnTime3S())
			{
				creatObject(EnemyAlphaType);
			}
			if (m_updater.isSpawnTime7S())
			{
				creatObject(EnemyBetaType);
			}
		}
		else if (m_numEnemys <= 14)
		{
			if (m_updater.isSpawnTime3S())
			{
				creatObject(EnemyAlphaType);
			}
			if (m_updater.isSpawnTime7S())
			{
				creatObject(EnemyBetaType);
			}
		}
	}
	s_AssetManager->TXT_SCORE.setString("Score: " + std::to_string(m_score));
}
