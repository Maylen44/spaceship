#ifndef ASSETS_MANAGER_H
#define ASSETS_MANAGER_H

#include "SharedContent.h"

enum Texture
{
    Texture_Player,
    Texture_EnemyA,
    Texture_EnemyB,
    Texture_Projectile,
    Texture_Background,
    Texture_MAX
};

enum SFX
{
	SFX_LaserShotSound,
	SFX_RestartSound,
	SFX_CollisionSound,
	SFX_MAX
};

enum TextFont
{
	TextFont_Default,
	TextFont_MAX
};

enum Text
{
	Text_Score,
	Text_PlayerHP,
	Text_MAX
};

class AssetsManager
{
public:
	static AssetsManager* instance();
	const void playSFX(SFX soundType);
	void editText(Text textType, const std::string textContent) { m_texts[textType].setString(textContent); };

	const sf::Texture& getTexture(Texture textureType) { return m_textures[textureType]; };
	const sf::Text& getText(Text textType) { return m_texts[textType]; };

private:
	AssetsManager();
	void loadTextures();
	void loadSFX();
	void loadTextFonts();
	void initTexts(int textsCount);

	std::unordered_map<Texture, sf::Texture> m_textures;
	std::unordered_map<SFX, sf::SoundBuffer> m_SFXBuffer;
	std::unordered_map<SFX, sf::Sound> m_SFX;
	std::unordered_map<TextFont, sf::Font> m_textFonts;
	std::unordered_map<Text, sf::Text> m_texts;
};

#endif //ASSETS_MANAGER_H