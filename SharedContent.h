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
	NoInput,
	Up,
	W,
	Down,
	S,
	Left,
	A,
	Right,
	D,
	UpLeft,
	UpRight,
	DownLeft,
	DownRight,
	ESC,
	Restart,
	MouseLeft,
	MouseRight,
	MouseLeftAndRight
};

enum SFX
{
	LaserShotSound,
	RestartSound,
	CollisionSound
};


#endif //SHARED_CONTENT_H