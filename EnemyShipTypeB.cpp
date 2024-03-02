#include "EnemyShipTypeB.h"

EnemyShipTypeB::EnemyShipTypeB()
	: m_baseSpeed(0.7f)
	, m_speed(m_passiveStriveSpeed + m_baseSpeed)
	, m_boostMultiplier(2.0f)
	, m_rotationSpeed(0.015f)
	, m_reactionDelay(2.0f)
	, m_stopZoneRange(150.0f, 200.0f)
	, m_spawnOffset(40.0f)
{
	AssetsManager* s_AssetManager = AssetsManager::instance();

	m_healthPoints = 3;
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	m_sprite.setTexture(s_AssetManager->TX_ENEMY_SHIP_VAR_2);
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_size.x, m_size.y));
	m_sprite.setOrigin(m_size.x / 2, m_size.x / 2);
	resetPosition();
}

void EnemyShipTypeB::update(const std::vector<InputEvent>& events)
{
	updateDuePlayerInputs(events);
	sf::Vector2f directionToMiddle = sf::Vector2f(g_sharedContent->WINDOW_RESOLUTION.x / 2, g_sharedContent->WINDOW_RESOLUTION.y / 2) - m_sprite.getPosition();
	float length = std::sqrt(directionToMiddle.x * directionToMiddle.x + directionToMiddle.y * directionToMiddle.y);
	updateRotation(directionToMiddle, length);
	updateFollowBehavior(g_sharedContent->WINDOW_RESOLUTION, directionToMiddle, length);

	if (getBounds().getPosition().x > g_sharedContent->WINDOW_RESOLUTION.x + m_size.x * 2 ||
		getBounds().getPosition().y > g_sharedContent->WINDOW_RESOLUTION.y + m_size.y * 2 ||
		getBounds().getPosition().x < 0 - m_size.x * 2 ||
		getBounds().getPosition().y < 0 - m_size.y * 2)
	{
		resetPosition();
	}
}

void EnemyShipTypeB::handleInterraction(sf::FloatRect& refObject)
{
	sf::Vector2f mainPosition = m_sprite.getPosition();
	sf::Vector2f refPosition = refObject.getPosition();
	sf::Vector2f movePosition = mainPosition;

	if (mainPosition.x >= refPosition.x && mainPosition.y >= refPosition.y)
	{
		movePosition.x = mainPosition.x + 1.0f / (m_speed * m_reactionDelay / 2);
		movePosition.y = mainPosition.y + 1.0f / (m_speed * m_reactionDelay / 2);
	}
	else if (mainPosition.x >= refPosition.x && mainPosition.y < refPosition.y)
	{
		movePosition.x = mainPosition.x + 1.0f / (m_speed * m_reactionDelay / 2);
		movePosition.y = mainPosition.y - 1.0f / (m_speed * m_reactionDelay / 2);
	}
	else if (mainPosition.x < refPosition.x && mainPosition.y >= refPosition.y)
	{
		movePosition.x = mainPosition.x - 1.0f / (m_speed * m_reactionDelay / 2);
		movePosition.y = mainPosition.y + 1.0f / (m_speed * m_reactionDelay / 2);
	}
	else
	{
		movePosition.x = mainPosition.x - 1.0f / (m_speed * m_reactionDelay / 2);
		movePosition.y = mainPosition.y - 1.0f / (m_speed * m_reactionDelay / 2);
	}
	m_sprite.setPosition(movePosition);
	m_healthPoints--;
}

void EnemyShipTypeB::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

void EnemyShipTypeB::resetPosition()
{
	sf::Vector2f spawnPosition = { 0.0f, 0.0f };

	if (rand() % 2 == 0)
	{
		spawnPosition.x = (rand() % 2 == 0) ? -m_spawnOffset : g_sharedContent->WINDOW_RESOLUTION.x + m_spawnOffset;
		spawnPosition.y = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (g_sharedContent->WINDOW_RESOLUTION.y - m_spawnOffset * 2) + m_spawnOffset;
	}
	else
	{
		spawnPosition.x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (g_sharedContent->WINDOW_RESOLUTION.x - m_spawnOffset * 2) + m_spawnOffset;
		spawnPosition.y = (rand() % 2 == 0) ? -m_spawnOffset : g_sharedContent->WINDOW_RESOLUTION.y + m_spawnOffset;
	}
	m_sprite.setPosition(spawnPosition.x, spawnPosition.y);
}

void EnemyShipTypeB::updateDuePlayerInputs(const std::vector<InputEvent>& events)
{
	float ingameSpeed = m_speed;
	if (events[2] == MouseRight || events[2] == MouseLeftAndRight)
	{
		ingameSpeed *= m_boostMultiplier;
	}

	switch (events[1])
	{
	case Up:
		m_sprite.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y + ingameSpeed);
		break;
	case Down:
		m_sprite.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y - ingameSpeed);
		break;
	case Left:
		m_sprite.setPosition(m_sprite.getPosition().x + ingameSpeed, m_sprite.getPosition().y);
		break;
	case Right:
		m_sprite.setPosition(m_sprite.getPosition().x - ingameSpeed, m_sprite.getPosition().y);
		break;
	case UpLeft:
		m_sprite.setPosition(m_sprite.getPosition().x + ingameSpeed, m_sprite.getPosition().y + ingameSpeed);
		break;
	case UpRight:
		m_sprite.setPosition(m_sprite.getPosition().x - ingameSpeed, m_sprite.getPosition().y + ingameSpeed);
		break;
	case DownLeft:
		m_sprite.setPosition(m_sprite.getPosition().x + ingameSpeed, m_sprite.getPosition().y - ingameSpeed);
		break;
	case DownRight:
		m_sprite.setPosition(m_sprite.getPosition().x - ingameSpeed, m_sprite.getPosition().y - ingameSpeed);
		break;
	default:
		break;
	}
}

void EnemyShipTypeB::updateRotation(sf::Vector2f& directionToMiddle, const float length)
{
	if (length != 0)
	{
		directionToMiddle /= length;
	}
	float targetAngle = std::atan2(directionToMiddle.y, directionToMiddle.x) * 180.0f / static_cast<float>(3.14f);
	float currentRotation = m_sprite.getRotation();
	float rotationDiff = targetAngle - currentRotation - 90.0f;
	if (rotationDiff > 180.0f)
	{
		rotationDiff -= 360.0f;
	}
	else if (rotationDiff < -180.0f)
	{
		rotationDiff += 360.0f;
	}
	m_sprite.setRotation(currentRotation + m_rotationSpeed * rotationDiff);
}

void EnemyShipTypeB::updateFollowBehavior(const sf::Vector2f& boundaries, 
										const sf::Vector2f& directionToMiddle, 
										const float length)
{
	//retreate back to safezone
	if (length < m_stopZoneRange.x)
	{
		m_sprite.setPosition(m_sprite.getPosition() - directionToMiddle / (m_speed * m_reactionDelay / 2));
	}
	//rotate clockwise or anti clockwise in safe zone
	else if (length < m_stopZoneRange.y)
	{
		float angle = std::atan2(directionToMiddle.y, directionToMiddle.x);
		if (m_sprite.getPosition().x > boundaries.x / 2)
		{
			angle += m_baseSpeed;
		}
		else
		{
			angle -= m_baseSpeed;
		}
		sf::Vector2f circularMotion(std::cos(angle), std::sin(angle));
		m_sprite.setPosition(m_sprite.getPosition() + circularMotion / (m_speed * m_reactionDelay));
	}
	//move towards middle
	else
	{
		m_sprite.setPosition(m_sprite.getPosition() + directionToMiddle / (m_speed * m_reactionDelay));
	}
}

sf::FloatRect& EnemyShipTypeB::getBounds()
{
	sf::FloatRect tmp = { m_sprite.getGlobalBounds().left + (m_size.x / 2 / 2),
						m_sprite.getGlobalBounds().top + (m_size.y / 2 / 2),
						m_sprite.getGlobalBounds().width / 2,
						m_sprite.getGlobalBounds().height / 2 };
	return tmp;
}

sf::Vector2f& EnemyShipTypeB::getPosition()
{
	sf::Vector2f tmp = m_sprite.getPosition();
	return tmp;
}
