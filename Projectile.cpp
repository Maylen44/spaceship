#include "Projectile.h"

Projectile::Projectile(const sf::Texture& texture, IGameObject* refObject)
	: m_healthPoints(1)
	, m_shotAngle(0.0f)
	, m_moveSpeed(4.5f)
	, m_size(10.0f, 10.0f)
	, m_sprite()
{
	if (refObject != nullptr)
	{
		m_shotAngle = refObject->getRotation();
		m_sprite.setTexture(texture);
		m_sprite.setTextureRect(sf::IntRect(0, 0, m_size.x, m_size.y));
		m_sprite.setOrigin(0.25f * m_size.x, -m_size.x - 21.0f);
		m_sprite.setPosition(refObject->getPosition());
		m_sprite.setRotation(m_shotAngle);
	}
}

void Projectile::update(const InputEvent& keyPress, const InputEvent& mousePress)
{
	updateMovement();
	updateDuePlayerInputs(keyPress, mousePress);
}

void Projectile::handleInterraction(const Interraction& interraction, sf::FloatRect& refObject)
{
	switch (interraction)
	{
	case ObjectsCollision:
		break;
	case ShotCollision:
		m_healthPoints--;
		break;
	default:
		break;
	}
}

void Projectile::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

sf::FloatRect& Projectile::getBounds()
{
	sf::FloatRect tmp = { m_sprite.getGlobalBounds().left + (m_size.x / 2 / 2),
						m_sprite.getGlobalBounds().top + (m_size.y / 2 / 2),
						m_sprite.getGlobalBounds().width / 2,
						m_sprite.getGlobalBounds().height / 2 };
	return tmp;
}

void Projectile::updateDuePlayerInputs(const InputEvent& keyPress, const InputEvent& mousePress)
{
	float ingameSpeed = 2.0f;
	if (mousePress == MouseRight || mousePress == MouseLeftAndRight)
	{
		ingameSpeed *= 2.0f;
	}

	switch (keyPress)
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

void Projectile::updateMovement()
{
	float radians = (m_shotAngle * (3.14159265359 / 180.0f)) + (90.0f * (3.14159265359 / 180.0f));
	sf::Vector2f moveDirection = { std::cos(radians) * m_moveSpeed , std::sin(radians) * m_moveSpeed };
	m_sprite.move(moveDirection);
}
