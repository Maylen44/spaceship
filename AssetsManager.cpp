#include "AssetsManager.h"

AssetsManager* AssetsManager::instance()
{
	static AssetsManager* s_Instance = new AssetsManager();
	return s_Instance;
}

const void AssetsManager::playSFX(SFX soundType)
{
	sf::Sound* pSound = nullptr;
	m_SFX[soundType].setBuffer(m_SFXBuffer[soundType]);
	m_SFX[soundType].setVolume(ConfigManager::instance()->getConfig(ConfigField_VolumeValue_SFX));
	pSound = &m_SFX[soundType];
	if (pSound != nullptr)
	{
		pSound->play();
	}
}

AssetsManager::AssetsManager()
	: m_textures()
	, m_SFXBuffer()
	, m_SFX()
	, m_textFonts()
	, m_texts()
{
	loadTextures();
	loadSFX();
	loadTextFonts();
	initTexts();


	//TODO
	m_texts[Text::Text_Score].setFont(m_textFonts[TextFont::TextFont_Default]);
	m_texts[Text::Text_PlayerHP].setFont(m_textFonts[TextFont::TextFont_Default]);
	m_texts[Text::Text_Score].setCharacterSize(24);
	m_texts[Text::Text_PlayerHP].setCharacterSize(24);
	m_texts[Text::Text_Score].setFillColor(sf::Color::Yellow);
	m_texts[Text::Text_PlayerHP].setFillColor(sf::Color::Green);
	m_texts[Text::Text_PlayerHP].setPosition(ConfigManager::instance()->getConfig(ConfigField_WindowResolution_X) - 80, 0);
}

void AssetsManager::loadTextures()
{
	//TODO split directory tree
	const std::string directory = "Assets/sprites/";
	const std::unordered_map<std::string, Texture> texturesMapping
	{
		{"player.png", Texture::Texture_Player},
		{"enemyA.png", Texture::Texture_EnemyA},
		{"enemyB.png", Texture::Texture_EnemyB},
		{"projectile.png", Texture::Texture_Projectile},
		{"bkgd_1.png", Texture::Texture_Background}
	};

	for (const auto& entry : std::filesystem::directory_iterator(directory))
	{
		if (entry.is_regular_file())
		{
			sf::Texture texture;
			std::string filename = entry.path().filename().string();
			auto iterator = texturesMapping.find(filename);

			if (iterator != texturesMapping.end())
			{
				if (texture.loadFromFile(directory + filename))
				{
					m_textures[iterator->second] = texture;
				}
				else
				{
					LOGGER->Log("Failed to load file:" + filename);
				}
			}
		}
	}
}

void AssetsManager::loadSFX()
{
	const std::string directory = "Assets/SFX/";
	const std::unordered_map<std::string, SFX> SFXBufferMapping
	{
		{"laser10.wav", SFX::SFX_LaserShotSound},
		{"restart.wav", SFX::SFX_RestartSound},
		{"tir.mp3", SFX::SFX_CollisionSound},
	};

	for (const auto& entry : std::filesystem::directory_iterator(directory))
	{
		if (entry.is_regular_file())
		{
			sf::SoundBuffer SFXBuffer;
			sf::Sound SFX;
			std::string filename = entry.path().filename().string();
			auto iterator = SFXBufferMapping.find(filename);

			if (iterator != SFXBufferMapping.end())
			{
				if (SFXBuffer.loadFromFile(directory + filename))
				{
					m_SFXBuffer[iterator->second] = SFXBuffer;
					m_SFX[iterator->second] = SFX;
				}
				else
				{
					LOGGER->Log("Failed to load file:" + filename);
				}
			}
		}
	}
}

void AssetsManager::loadTextFonts()
{
	const std::string directory = "Assets/text_fonts/";
	const std::unordered_map<std::string, TextFont> TextFontMapping
	{
		{"GlitchGoblinv.ttf", TextFont::TextFont_Default},
	};

	for (const auto& entry : std::filesystem::directory_iterator(directory))
	{
		if (entry.is_regular_file())
		{
			sf::Font textFont;
			std::string filename = entry.path().filename().string();
			auto iterator = TextFontMapping.find(filename);

			if (iterator != TextFontMapping.end())
			{
				if (textFont.loadFromFile(directory + filename))
				{
					m_textFonts[iterator->second] = textFont;
				}
				else
				{
					LOGGER->Log("Failed to load file:" + filename);
				}
			}
		}
	}
}

void AssetsManager::initTexts()
{
	for (int i = 0; i < Text::Text_MAX; ++i)
	{
		sf::Text text;
		Text enumValue = static_cast<Text>(i);
		m_texts[enumValue] = text;
	}
}