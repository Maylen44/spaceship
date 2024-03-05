#include "Projectile.h"

Projectile::Projectile(const float shotAngle, const sf::Vector2f shotStartPosition)
	: m_moveSpeed(4.5f)
{
	AssetsManager* s_AssetManager = AssetsManager::instance();
	s_AssetManager->playSFX(SFX_LaserShotSound);

	m_size = sf::Vector2f(10.0f, 10.0f);
	m_healthPoints = 1;
	m_sprite.setTexture(s_AssetManager->getTexture(Texture::Texture_Projectile));
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_size.x, m_size.y));
	m_sprite.setOrigin(0.25f * m_size.x, -m_size.x - 21.0f);
	m_sprite.setRotation(shotAngle);
	m_sprite.setPosition(shotStartPosition);
}

void Projectile::update(const std::vector<InputEvent>& events)
{
	updateMovement();
	updateDuePlayerInputs(events);
}

sf::FloatRect& Projectile::getBounds()
{
	sf::FloatRect tmp = { m_sprite.getGlobalBounds().left + (m_size.x / 2 / 2),
						m_sprite.getGlobalBounds().top + (m_size.y / 2 / 2),
						m_sprite.getGlobalBounds().width / 2,
						m_sprite.getGlobalBounds().height / 2 };
	return tmp;
}

void Projectile::updateDuePlayerInputs(const std::vector<InputEvent>& events)
{
	float ingameSpeed = 2.0f;
	if (events[2] == InputEvent_MouseRight || events[2] == InputEvent_MouseLeftAndRight)
	{
		ingameSpeed *= 2.0f;
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

void Projectile::updateMovement()
{
	float radians = (m_sprite.getRotation() * (3.14159265359 / 180.0f)) + (90.0f * (3.14159265359 / 180.0f));
	sf::Vector2f moveDirection = { std::cos(radians) * m_moveSpeed , std::sin(radians) * m_moveSpeed };
	m_sprite.move(moveDirection);
}
