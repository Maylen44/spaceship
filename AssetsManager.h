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
	const sf::Text& getFormatedText(TextTemplate text) 
								{ return m_texts[text]; };


private:
	float m_volumeSFX;
	std::unordered_map<GameObjectType, sf::Texture> m_textures;

	std::unordered_map<TextTemplate, sf::Text> m_texts;
	

	sf::SoundBuffer laserSFXBuffer, laserHitSFXBuffer, restartSFXBuffer, impactSFXBuffer;
	sf::Sound laserSFX, laserHitSFX, restartSFX, impactSFX;
	sf::Font m_font;
	
};

#endif //ASSETS_MANAGER_H