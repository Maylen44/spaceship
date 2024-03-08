#ifndef SHARED_CONTENT_H
#define SHARED_CONTENT_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <pugixml.hpp>
#include <vector>
#include <cmath>
#include <string>
#include <unordered_map>
#include <filesystem>
#include <iostream>

enum ConfigField
{
	ConfigField_WindowResolution_X,
	ConfigField_WindowResolution_Y,
	ConfigField_TimeRate_001,
	ConfigField_TimeRate_05,
	ConfigField_TimeRate_075,
	ConfigField_TimeRate_1,
	ConfigField_TimeRate_3,
	ConfigField_TimeRate_7,
	ConfigField_VolumeValue_SFX,
	ConfigField_VolumeValue_Music,
	ConfigField_MAX
};

class ConfigManager
{
public:
	static ConfigManager* instance();

	int getConfig(ConfigField argToGet);
	void setConfig(ConfigField argToSet, int value);

	//sf::Vector2f WINDOW_RESOLUTION{ 800.f, 600.f };
	sf::Time TIME_RATE_001S{ sf::seconds(0.01f) };
	sf::Time TIME_RATE_05S{ sf::seconds(0.5f) };
	sf::Time TIME_RATE_075S{ sf::seconds(0.75f) };
	sf::Time TIME_RATE_1S{ sf::seconds(1.0f) };
	sf::Time TIME_RATE_3S{ sf::seconds(3.0f) };
	sf::Time TIME_RATE_7S{ sf::seconds(7.0f) };
	float VOLUME_SFX{ 100.0f };
	float VOLUME_MUSIC{ 100.0f };
	

private:
	ConfigManager();
	const char* m_filePath;
};

enum InputEvent
{
	InputEvent_NoInput,
	InputEvent_Up,
	InputEvent_W,
	InputEvent_Down,
	InputEvent_S,
	InputEvent_Left,
	InputEvent_A,
	InputEvent_Right,
	InputEvent_D,
	InputEvent_UpLeft,
	InputEvent_UpRight,
	InputEvent_DownLeft,
	InputEvent_DownRight,
	InputEvent_ESC,
	InputEvent_Restart,
	InputEvent_MouseLeft,
	InputEvent_MouseRight,
	InputEvent_MouseLeftAndRight,
	InputEvent_MAX
};


#endif //SHARED_CONTENT_H