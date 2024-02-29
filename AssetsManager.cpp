#include "AssetsManager.h"

AssetsManager* AssetsManager::instance()
{
	static AssetsManager* s_Instance = new AssetsManager();
	return s_Instance;
}

void const AssetsManager::playSFX(SFX sound)
{
	sf::Sound* pSound = nullptr;

	switch (sound)
	{
	case LaserShotSound:
		SFX_LASER_SHOT.setBuffer(SFX_BUFFER_LASER_SHOT);
		SFX_LASER_SHOT.setVolume(VOLUME_SFX);
		pSound = &SFX_LASER_SHOT;
		break;
	case RestartSound:
		SFX_RESTART.setBuffer(SFX_BUFFER_RESTART);
		SFX_RESTART.setVolume(VOLUME_SFX);
		pSound = &SFX_RESTART;
		break;
	case CollisionSound:
		SFX_COLLISION.setBuffer(SFX_BUFFER_COLLISION);
		SFX_COLLISION.setVolume(VOLUME_SFX);
		pSound = &SFX_COLLISION;
	default:
		break;
	}

	if (pSound != nullptr)
	{
		pSound->play();
	}
}

AssetsManager::AssetsManager()
{
	//Texture initialization
	TX_BACKGROUND.loadFromFile("sprites/bkgd_1.png");
	TX_PLAYER_SHIP.loadFromFile("sprites/player.png");
	TX_ENEMY_SHIP_VAR_1.loadFromFile("sprites/enemyA.png");
	TX_ENEMY_SHIP_VAR_2.loadFromFile("sprites/enemyB.png");
	TX_PROJECTILE.loadFromFile("sprites/projectile.png");

	//SFX initialization
	SFX_BUFFER_LASER_SHOT.loadFromFile("SFX/laser10.wav");
	SFX_BUFFER_RESTART.loadFromFile("SFX/restart.wav");
	SFX_BUFFER_COLLISION.loadFromFile("SFX/tir.mp3");

	//Font and Text initialization
	FOND_DEFAULT.loadFromFile("font/GlitchGoblinv.ttf");
	TXT_SCORE.setFont(FOND_DEFAULT);
	TXT_HEALTHPOINTS_PLAYER.setFont(FOND_DEFAULT);
	TXT_SCORE.setCharacterSize(24);
	TXT_HEALTHPOINTS_PLAYER.setCharacterSize(24);
	TXT_SCORE.setFillColor(sf::Color::Yellow);
	TXT_HEALTHPOINTS_PLAYER.setFillColor(sf::Color::Green);
}