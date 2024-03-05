#include "EnemyAlpha.h"

EnemyAlpha::EnemyAlpha()
{
	AssetsManager* s_AssetManager = AssetsManager::instance();

	m_baseSpeed = 1.0f;
	m_speed = m_passiveStriveSpeed + m_baseSpeed;
	m_rotationSpeed = 0.01f;
	m_stopZoneRange = sf::Vector2f{ 100.0f, 150.0f };
	m_healthPoints = 1;
	
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	m_sprite.setTexture(s_AssetManager->getTexture(Texture::Texture_EnemyA));
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_size.x, m_size.y));
	m_sprite.setOrigin(m_size.x / 2, m_size.x / 2);
	resetPosition();
}

void EnemyAlpha::handleInterraction(sf::FloatRect& refObject)
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
