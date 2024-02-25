#ifndef SHARED_CONTENT_H
#define SHARED_CONTENT_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <string>
#include <unordered_map>

struct Test
{
	int ini;
};

extern Test* gTest;

const sf::Vector2f WINDOW_RESOLUTION { 800.f, 600.f };

const sf::Time FRAME_RATE { sf::seconds(0.01f) };
const sf::Time RATE_05S { sf::seconds(0.5f) };
const sf::Time RATE_075S{ sf::seconds(0.75f) };
const sf::Time RATE_1S{ sf::seconds(1.0f) };
const sf::Time RATE_3S { sf::seconds(3.0f) };
const sf::Time RATE_7S { sf::seconds(7.0f) };

enum InputEvent
{
	Closed = sf::Event::Closed,
	Up = sf::Keyboard::Up,
	W = sf::Keyboard::W,
	Down = sf::Keyboard::Down,
	S = sf::Keyboard::S,
	Left = sf::Keyboard::Left,
	A = sf::Keyboard::A,
	Right = sf::Keyboard::Right,
	D = sf::Keyboard::D,
	Space = sf::Keyboard::Space,
	MouseLeft = sf::Mouse::Left,
	MouseRight = sf::Mouse::Right,
	ESC = sf::Keyboard::Escape,
	R = sf::Keyboard::R
};

enum ApplicationStatus
{
	Processing,
	ClossingApplication,
	RestartingApplication
};

enum KeyboardEvent
{
	NoKeyboardInput,
	MoveUp,
	MoveDown,
	MoveLeft,
	MoveRight,
	MoveUpLeft,
	MoveUpRight,
	MoveDownLeft,
	MoveDownRight
};

enum MouseEvent
{
	NoMouseInput,
	RightClick,
	LeftClick,
	RightAndLeftClick
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
	EnemyTypAType,
	EnemyTypBType,
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
	DefaultText,
	ScoreText,
	HPText
};

#endif //SHARED_CONTENT_H