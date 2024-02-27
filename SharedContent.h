#ifndef SHARED_CONTENT_H
#define SHARED_CONTENT_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <string>
#include <unordered_map>

struct SharedContent
{
	sf::Vector2f WINDOW_RESOLUTION{ 800.f, 600.f };
	float VOLUME_SFX{100.0f};
	float VOLUME_MUSIC{100.0f};

	sf::Time TIME_RATE_001S{ sf::seconds(0.01f) };
	sf::Time TIME_RATE_05S{ sf::seconds(0.5f) };
	sf::Time TIME_RATE_075S{ sf::seconds(0.75f) };
	sf::Time TIME_RATE_1S{ sf::seconds(1.0f) };
	sf::Time TIME_RATE_3S{ sf::seconds(3.0f) };
	sf::Time TIME_RATE_7S{ sf::seconds(7.0f) };

	sf::Texture TX_BACKGROUND, 
				TX_PLAYER_SHIP, 
				TX_ENEMY_SHIP_VAR_1, 
				TX_ENEMY_SHIP_VAR_2, 
				TX_PROJECTILE;

	sf::SoundBuffer SFX_BUFFER_LASER_SHOT, 
					SFX_BUFFER_LASER_HIT, 
					SFX_BUFFER_RESTART, 
					SFX_BUFFER_COLLISION;
	sf::Sound SFX_LASER_SHOT, 
				SFX_LASER_HIT, 
				SFX_RESTART, 
				SFX_COLLISION;
	sf::Font FOND_DEFAULT;
	sf::Text TXT_DEFAULT, 
			TXT_SCORE,
			TXT_HEALTHPOINTS_PLAYER;

};

extern SharedContent* g_sharedContent;

enum InputEvent
{
	NoInput,
	Up = sf::Keyboard::Up,
	W = sf::Keyboard::W,
	Down = sf::Keyboard::Down,
	S = sf::Keyboard::S,
	Left = sf::Keyboard::Left,
	A = sf::Keyboard::A,
	Right = sf::Keyboard::Right,
	D = sf::Keyboard::D,

	UpLeft,
	UpRight,
	DownLeft,
	DownRight,

	ESC = sf::Keyboard::Escape,
	Restart = sf::Keyboard::R,
	
	MouseLeft = sf::Mouse::Left,
	MouseRight = sf::Mouse::Right,
	MouseLeftAndRight
	
};

enum Interraction
{
	ObjectsCollision,
	ShotCollision
};

enum GameObjectType
{
	BackgroundType,
	ShipType,
	PlayerType,
	EnemyTypeAType,
	EnemyTypeBType,
	ProjectileType,
	NotSpecifiedType
};

enum SFX
{
	LaserShotSound,
	LaserHitSound,
	RestartSound,
	CollisionSound
};

enum TextTemplate
{
	ScoreText,
	HPText
};

#endif //SHARED_CONTENT_H