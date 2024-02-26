#include "Game.h"
#include "Background.h"
#include "PlayerShip.h"
#include "EnemyShipTypeA.h"
#include "EnemyShipTypeB.h"
#include "Projectile.h"

SharedContent* g_sharedContent = nullptr;

Game::Game()
	: m_isPlaying(false)
	, m_score(0)
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
	creatObject(EnemyTypAType, 3);
	creatObject(EnemyTypBType, 2);
	m_updater.resetContent(m_gameObjects);
}

void Game::run()
{
	initialize();
	
	while (m_isPlaying)
	{
		ApplicationStatus status = m_eventHandler.fetchApplicationStatus(m_renderer.pollWindowEvent());
		KeyboardEvent keyboardEvent = m_eventHandler.fetchKeyboardEvent();
		MouseEvent mouseEvent = m_eventHandler.fetchMouseEvent();

		if (status == ClossingApplication)
		{
			m_isPlaying = false;
			clearObject();
			m_renderer.closeWindow();
		}
		else if (status == RestartingApplication)
		{
			if (m_updater.isSFXTime())
			{
				m_assetsManager.playSFX(RestartSound);
			}
			reset();
		}
		m_updater.update(m_gameObjects, keyboardEvent, mouseEvent);
		progressGameLogic();
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
			Background* background = new Background(m_assetsManager.getTexture(type), g_sharedContent->WINDOW_RESOLUTION);
			m_gameObjects.push_back(background);
		}
		else if (type == PlayerType)
		{
			PlayerShip* player = new PlayerShip(m_assetsManager.getTexture(type));
			m_gameObjects.push_back(player);
			m_updater.reserContent(player);
		}
		else if (type == EnemyTypAType)
		{
			EnemyShipTypeA* enemy1 = new EnemyShipTypeA(m_assetsManager.getTexture(type));
			m_gameObjects.push_back(enemy1);
			m_updater.reserContent(enemy1);
		}
		else if (type == EnemyTypBType)
		{
			EnemyShipTypeB* enemy2 = new EnemyShipTypeB(m_assetsManager.getTexture(type));
			m_gameObjects.push_back(enemy2);
			m_updater.reserContent(enemy2);
		}
		else if (type == ProjectileType && refObject != nullptr)
		{
			Projectile* projectile = new Projectile(m_assetsManager.getTexture(type), refObject);
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
			if (m_eventHandler.fetchMouseEvent() == RightAndLeftClick || m_eventHandler.fetchMouseEvent() == LeftClick)
			{
				if (m_updater.isSFXTime())
				{
					creatObject(ProjectileType, 1, m_gameObjects[i]);
					m_assetsManager.playSFX(LaserShotSound);
				}
			}
			break;
		case EnemyTypAType:
			if (m_gameObjects[i]->getHealthPoints() <= 0)
			{
				clearObject(i);
				--i;
				m_score += 100;
				m_assetsManager.playSFX(CollisionSound);
			}
			if (m_updater.isFireTime1S())
			{
				creatObject(ProjectileType, 1, m_gameObjects[i]);
				m_assetsManager.playSFX(LaserShotSound);
			}
			break;
		case EnemyTypBType:
			if (m_gameObjects[i]->getHealthPoints() <= 0)
			{
				clearObject(i);
				--i;
				m_score += 200;
				m_assetsManager.playSFX(CollisionSound);
			}
			if (m_updater.isFireTime075S())
			{
				creatObject(ProjectileType, 1, m_gameObjects[i]);
				m_assetsManager.playSFX(LaserShotSound);
			}
			break;
		case ProjectileType:
			if (m_gameObjects[i]->getHealthPoints() <= 0)
			{
				clearObject(i);
				--i;
				m_assetsManager.playSFX(LaserHitSound);
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
			if (object->getObjectTyp() == EnemyTypAType || object->getObjectTyp() == EnemyTypBType)
			{
				++numEnemys;
			}
		}
		if (numEnemys <= 2)
		{
			if (m_updater.isSpawnTime3S())
			{
				creatObject(EnemyTypAType);
			}
			if (m_updater.isSpawnTime7S())
			{
				creatObject(EnemyTypBType);
			}
		}
		else if (numEnemys <= 14)
		{
			if (m_updater.isSpawnTime3S())
			{
				creatObject(EnemyTypAType);
			}
			if (m_updater.isSpawnTime7S())
			{
				creatObject(EnemyTypBType);
			}
		}
	}

	sf::Text tmpScore = m_assetsManager.getFormatedText(ScoreText);
	sf::Text tmp_HP = m_assetsManager.getFormatedText(HPText);
	tmpScore.setString("Score: " + std::to_string(m_score));
	tmp_HP.setString("HP: " + std::to_string(tmpHP));
	tmp_HP.setPosition(g_sharedContent->WINDOW_RESOLUTION.x - 80, 0);


	m_renderer.renderContent(m_gameObjects, tmpScore, tmp_HP);

}
