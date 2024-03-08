#include "EnemyShip.h"

EnemyShip::EnemyShip()
	: m_baseSpeed()
	, m_speed()
	, m_boostMultiplier(2.0f)
	, m_rotationSpeed()
	, m_reactionDelay(2.0f)
	, m_stopZoneRange()
	, m_spawnOffset(40.0f)
{}

void EnemyShip::update(const std::vector<InputEvent>& events)
{
	updateDuePlayerInputs(events);
	sf::Vector2f directionToMiddle = sf::Vector2f(ConfigManager::instance()->getConfig(ConfigField_WindowResolution_X) / 2, ConfigManager::instance()->getConfig(ConfigField_WindowResolution_Y) / 2) - m_sprite.getPosition();
	float length = std::sqrt(directionToMiddle.x * directionToMiddle.x + directionToMiddle.y * directionToMiddle.y);
	updateRotation(directionToMiddle, length);
	updateFollowBehavior(sf::Vector2f(ConfigManager::instance()->getConfig(ConfigField_WindowResolution_X), ConfigManager::instance()->getConfig(ConfigField_WindowResolution_Y)), directionToMiddle, length);

	if (getBounds().getPosition().x > ConfigManager::instance()->getConfig(ConfigField_WindowResolution_X) + m_size.x * 2 ||
		getBounds().getPosition().y > ConfigManager::instance()->getConfig(ConfigField_WindowResolution_Y) + m_size.y * 2 ||
		getBounds().getPosition().x < 0 - m_size.x * 2 ||
		getBounds().getPosition().y < 0 - m_size.y * 2)
	{
		resetPosition();
	}
}

void EnemyShip::resetPosition()
{
	sf::Vector2f spawnPosition = { 0.0f, 0.0f };

	if (rand() % 2 == 0)
	{
		spawnPosition.x = (rand() % 2 == 0) ? -m_spawnOffset : ConfigManager::instance()->getConfig(ConfigField_WindowResolution_X) + m_spawnOffset;
		spawnPosition.y = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (ConfigManager::instance()->getConfig(ConfigField_WindowResolution_Y) - m_spawnOffset * 2) + m_spawnOffset;
	}
	else
	{
		spawnPosition.x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (ConfigManager::instance()->getConfig(ConfigField_WindowResolution_X) - m_spawnOffset * 2) + m_spawnOffset;
		spawnPosition.y = (rand() % 2 == 0) ? -m_spawnOffset : ConfigManager::instance()->getConfig(ConfigField_WindowResolution_Y) + m_spawnOffset;
	}
	m_sprite.setPosition(spawnPosition.x, spawnPosition.y);
}

void EnemyShip::updateDuePlayerInputs(const std::vector<InputEvent>& events)
{
	float ingameSpeed = m_speed;
	if (events[2] == InputEvent_MouseRight || events[2] == InputEvent_MouseLeftAndRight)
	{
		ingameSpeed *= m_boostMultiplier;
	}

	switch (events[1])
	{
	case InputEvent_Up:
		m_sprite.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y + ingameSpeed);
		break;
	case InputEvent_Down:
		m_sprite.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y - ingameSpeed);
		break;
	case InputEvent_Left:
		m_sprite.setPosition(m_sprite.getPosition().x + ingameSpeed, m_sprite.getPosition().y);
		break;
	case InputEvent_Right:
		m_sprite.setPosition(m_sprite.getPosition().x - ingameSpeed, m_sprite.getPosition().y);
		break;
	case InputEvent_UpLeft:
		m_sprite.setPosition(m_sprite.getPosition().x + ingameSpeed, m_sprite.getPosition().y + ingameSpeed);
		break;
	case InputEvent_UpRight:
		m_sprite.setPosition(m_sprite.getPosition().x - ingameSpeed, m_sprite.getPosition().y + ingameSpeed);
		break;
	case InputEvent_DownLeft:
		m_sprite.setPosition(m_sprite.getPosition().x + ingameSpeed, m_sprite.getPosition().y - ingameSpeed);
		break;
	case InputEvent_DownRight:
		m_sprite.setPosition(m_sprite.getPosition().x - ingameSpeed, m_sprite.getPosition().y - ingameSpeed);
		break;
	default:
		break;
	}
}

void EnemyShip::updateRotation(sf::Vector2f& directionToMiddle, const float length)
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

void EnemyShip::updateFollowBehavior(const sf::Vector2f& boundaries, const sf::Vector2f& directionToMiddle, const float length)
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
