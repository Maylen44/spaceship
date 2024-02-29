#include "Game.h"
#include "AssetsManager.h"
#include "Background.h"
#include "PlayerShip.h"
#include "EnemyShipTypeA.h"
#include "EnemyShipTypeB.h"
#include "Projectile.h"

SharedContent* g_sharedContent = nullptr;


Game::Game()
	: m_isPlaying(false)
	, m_score(0)
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
	creatObject(EnemyTypeAType, 3);
	creatObject(EnemyTypeBType, 2);
	m_updater.resetContent(m_gameObjects);
}

void Game::run()
{
	initialize();
	AssetsManager* s_AssetManager = AssetsManager::instance();

	
	while (m_isPlaying)
	{
		InputEvent status = m_eventHandler.fetchApplicationStatus(m_renderer.pollWindowEvent());
		InputEvent keyboardEvent = m_eventHandler.fetchKeyboardEvent();
		InputEvent mouseEvent = m_eventHandler.fetchMouseEvent();

		if (status == ESC)
		{
			m_isPlaying = false;
			clearObject();
			m_renderer.closeWindow();
		}
		else if (status == Restart)
		{
			if (m_updater.isSFXTime())
			{
				s_AssetManager->playSFX(RestartSound);
			}
			reset();
		}
		m_updater.update(m_gameObjects, keyboardEvent, mouseEvent);
		progressGameLogic();
		m_renderer.renderContent(m_gameObjects);
	}
}

void Game::reset()
{
	clearObject();
	initialize();
}

void Game::creatObject(const GameObjectType& type, int numOfObjects, IGameObject* refObject)
{
	for (int i = 0; i < numOfObjects; ++i)
	{
		if (type == ShipType) {}
		else if (type == BackgroundType)
		{
			Background* background = new Background(g_sharedContent->WINDOW_RESOLUTION);
			m_gameObjects.push_back(background);
		}
		else if (type == PlayerType)
		{
			PlayerShip* player = new PlayerShip();
			m_gameObjects.push_back(player);
			m_updater.reserContent(player);
		}
		else if (type == EnemyTypeAType)
		{
			EnemyShipTypeA* enemy1 = new EnemyShipTypeA();
			m_gameObjects.push_back(enemy1);
			m_updater.reserContent(enemy1);
		}
		else if (type == EnemyTypeBType)
		{
			EnemyShipTypeB* enemy2 = new EnemyShipTypeB();
			m_gameObjects.push_back(enemy2);
			m_updater.reserContent(enemy2);
		}
		else if (type == ProjectileType && refObject != nullptr)
		{
			Projectile* projectile = new Projectile(refObject);
			m_gameObjects.push_back(projectile);
			m_updater.reserContent(projectile);
		}
		else if (type == NotSpecifiedType) {}
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

void Game::progressGameLogic()
{
	AssetsManager* s_AssetManager = AssetsManager::instance();

	int numEnemys = 0;
	int tmpHP = 0;
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
			tmpHP = m_gameObjects[i]->getHealthPoints();
			if (tmpHP <= 0)
			{
				reset();
			}

			if ((m_eventHandler.fetchMouseEvent() == MouseLeftAndRight) || (m_eventHandler.fetchMouseEvent() == MouseLeft))
			{
				if (m_updater.isSFXTime())
				{
					creatObject(ProjectileType, 1, m_gameObjects[i]);
				}
			}
			
			break;
		case EnemyTypeAType:
			if (m_gameObjects[i]->getHealthPoints() <= 0)
			{
				clearObject(i);
				--i;
				m_score += 100;
			}
			if (m_updater.isFireTime1S())
			{
				creatObject(ProjectileType, 1, m_gameObjects[i]);
			}
			break;
		case EnemyTypeBType:
			if (m_gameObjects[i]->getHealthPoints() <= 0)
			{
				clearObject(i);
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
			else if (m_gameObjects[i]->getBounds().getPosition().x > g_sharedContent->WINDOW_RESOLUTION.x ||
				m_gameObjects[i]->getBounds().getPosition().y > g_sharedContent->WINDOW_RESOLUTION.y ||
				m_gameObjects[i]->getBounds().getPosition().x < 0 ||
				m_gameObjects[i]->getBounds().getPosition().y < 0)
			{
				clearObject(i);
				--i;
			}
			break;
		case NotSpecifiedType:
			break;
		default:
			break;
		}


		for (auto& object : m_gameObjects)
		{
			if (object->getObjectTyp() == EnemyTypeAType || object->getObjectTyp() == EnemyTypeBType)
			{
				++numEnemys;
			}
		}
		if (numEnemys <= 2)
		{
			if (m_updater.isSpawnTime3S())
			{
				creatObject(EnemyTypeAType);
			}
			if (m_updater.isSpawnTime7S())
			{
				creatObject(EnemyTypeBType);
			}
		}
		else if (numEnemys <= 14)
		{
			if (m_updater.isSpawnTime3S())
			{
				creatObject(EnemyTypeAType);
			}
			if (m_updater.isSpawnTime7S())
			{
				creatObject(EnemyTypeBType);
			}
		}
	}
	
	s_AssetManager->TXT_SCORE.setString("Score: " + std::to_string(m_score));
	s_AssetManager->TXT_HEALTHPOINTS_PLAYER.setString("HP: " + std::to_string(tmpHP));
	s_AssetManager->TXT_HEALTHPOINTS_PLAYER.setPosition(g_sharedContent->WINDOW_RESOLUTION.x - 80, 0);

}
