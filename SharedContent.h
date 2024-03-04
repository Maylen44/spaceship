#ifndef SHARED_CONTENT_H
#define SHARED_CONTENT_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cmath>
#include <string>
#include <unordered_map>

struct SharedContent
{
	sf::Vector2f WINDOW_RESOLUTION{ 800.f, 600.f };

	sf::Time TIME_RATE_001S{ sf::seconds(0.01f) };
	sf::Time TIME_RATE_05S{ sf::seconds(0.5f) };
	sf::Time TIME_RATE_075S{ sf::seconds(0.75f) };
	sf::Time TIME_RATE_1S{ sf::seconds(1.0f) };
	sf::Time TIME_RATE_3S{ sf::seconds(3.0f) };
	sf::Time TIME_RATE_7S{ sf::seconds(7.0f) };
};

extern SharedContent* g_sharedContent;

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

enum SFX
{
	SFX_LaserShotSound,
	SFX_RestartSound,
	SFX_CollisionSound,
	SFX_MAX
};


#endif //SHARED_CONTENT_H