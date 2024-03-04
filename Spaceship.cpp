#include "Spaceship.h"

Spaceship::Spaceship()
	: m_size(50.f, 50.f)
	, m_sprite()
	, m_passiveStriveSpeed(1.0f)
	, m_healthPoints(0)
{}

sf::FloatRect& Spaceship::getBounds()
{
	sf::FloatRect tmp = { m_sprite.getGlobalBounds().left + (m_size.x / 2 / 2),
						m_sprite.getGlobalBounds().top + (m_size.y / 2 / 2),
						m_sprite.getGlobalBounds().width / 2,
						m_sprite.getGlobalBounds().height / 2 };
	return tmp;
}