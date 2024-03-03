#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "IGameObject.h"

class Background : public IGameObject
{
public:
	Background();
	virtual ~Background() = default;

	void update(const std::vector<InputEvent>& events) override;
	void draw(sf::RenderWindow& window) override;

private:
	void resetBackground(sf::Sprite& sprite);
	sf::Vector2f rotateVector(const sf::Vector2f& vector, float angle);

	std::vector <sf::Sprite> m_backgroundSprites;
	const sf::Vector2f m_size;
	const float m_scrollSpeed;
	sf::Vector2f m_passiveStriveDirection;
	const float m_passiveStriveSpeed;
	const float m_boostMultiplier;

	
	

};

#endif //BACKGROUND_H