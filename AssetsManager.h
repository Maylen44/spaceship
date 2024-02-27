#ifndef ASSETS_MANAGER_H
#define ASSETS_MANAGER_H

#include "SharedContent.h"

class AssetsManager
{
public:
	AssetsManager();

	void const playSFX(SFX sound);
	const sf::Texture& getTexture(const GameObjectType& type) 
								{ return m_textures[type]; };

private:
	std::unordered_map<GameObjectType, sf::Texture> m_textures;
	std::unordered_map<TextTemplate, sf::Text> m_texts;
};

#endif //ASSETS_MANAGER_H