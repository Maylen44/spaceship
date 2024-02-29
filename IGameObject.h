#ifndef I_GAME_OBJECT_H
#define I_GAME_OBJECT_H

#include "SharedContent.h"
#include "AssetsManager.h"

class IGameObject
{
public:
	virtual ~IGameObject() = default;

	virtual void update(const InputEvent& keyPress, 
						const InputEvent& mousePress) {};
	virtual void handleInterraction(sf::FloatRect& refObject) {};
	virtual void draw(sf::RenderWindow& window) {};
	virtual void resetPosition() {};
	
	virtual GameObjectType getObjectTyp() { return NotSpecifiedType; };
	virtual sf::FloatRect& getBounds() { return m_tmp; };
	virtual sf::Vector2f& getPosition() { return m_tmp2; };
	virtual float getRotation() { return 0; };
	virtual int getHealthPoints() { return 0; };

private:
	sf::FloatRect m_tmp;
	sf::Vector2f m_tmp2;
};

#endif //I_GAME_OBJECT_H