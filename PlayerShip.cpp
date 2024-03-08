#include "PlayerShip.h"

static float getAngle(float x1, float y1, float x2, float y2)
{
	sf::Vector2f up(0, 1);
	sf::Vector2f p0(x1, y1);
	sf::Vector2f p1(x2, y2);
	sf::Vector2f q = p1 - p0;
	float q_length = sqrtf(q.x * q.x + q.y * q.y);
	q.x /= q_length;
	q.y /= q_length;
	float scalar_product = q.y;
	float angle = acos(scalar_product) * 180.0f / 3.1415f;
	if (x2 - x1 < 0.0f){}
	else
	{
		angle *= -1;
	}
	return angle;
}


PlayerShip::PlayerShip()
	: m_rotationAngle(m_sprite.getRotation())
{
	AssetsManager* s_AssetManager = AssetsManager::instance();

	m_healthPoints = 10;
	m_sprite.setTexture(s_AssetManager->getTexture(Texture::Texture_Player));
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_size.x, m_size.y));
	m_sprite.setOrigin(m_size.x / 2, m_size.x / 2);
	resetPosition();
}

void PlayerShip::update(const std::vector<InputEvent>& events)
{
	AssetsManager* s_AssetManager = AssetsManager::instance();
	s_AssetManager->editText(Text::Text_PlayerHP, "HP: " + std::to_string(m_healthPoints));
	m_sprite.setRotation(m_rotationAngle);
}

void PlayerShip::handleInterraction(sf::FloatRect& refObject)
{
	m_healthPoints--;
}

void PlayerShip::draw(sf::RenderWindow& window)
{
	handleRotation(window);
	window.draw(m_sprite);
}

void PlayerShip::resetPosition()
{
	sf::Vector2f tmp = { ConfigManager::instance()->getConfig(ConfigField_WindowResolution_X) / 2 - m_size.x / 2,
						ConfigManager::instance()->getConfig(ConfigField_WindowResolution_Y) / 2 - m_size.y / 2};
	m_sprite.setPosition(tmp);
}


void PlayerShip::handleRotation(sf::RenderWindow& window)
{
	sf::Vector2i cursorPosition = sf::Mouse::getPosition(window);
	m_rotationAngle = getAngle(m_sprite.getPosition().x, m_sprite.getPosition().y, cursorPosition.x, cursorPosition.y);
}