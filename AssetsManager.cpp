#include "AssetsManager.h"

AssetsManager::AssetsManager()
	: m_textures()
	, m_texts()
{
	//Texture initialization
	g_sharedContent->TX_BACKGROUND.loadFromFile("sprites/bkgd_1.png");
	g_sharedContent->TX_PLAYER_SHIP.loadFromFile("sprites/player.png");
	g_sharedContent->TX_ENEMY_SHIP_VAR_1.loadFromFile("sprites/enemyA.png");
	g_sharedContent->TX_ENEMY_SHIP_VAR_2.loadFromFile("sprites/enemyB.png");
	g_sharedContent->TX_PROJECTILE.loadFromFile("sprites/projectile.png");

	m_textures[BackgroundType] = g_sharedContent->TX_BACKGROUND;
	m_textures[PlayerType] = g_sharedContent->TX_PLAYER_SHIP;
	m_textures[EnemyTypeAType] = g_sharedContent->TX_ENEMY_SHIP_VAR_1;
	m_textures[EnemyTypeBType] = g_sharedContent->TX_ENEMY_SHIP_VAR_2;
	m_textures[ProjectileType] = g_sharedContent->TX_PROJECTILE;

	//SFX initialization
	g_sharedContent->SFX_BUFFER_LASER_SHOT.loadFromFile("SFX/laser10.wav");
	g_sharedContent->SFX_BUFFER_LASER_HIT.loadFromFile("SFX/impactshort78.wav");
	g_sharedContent->SFX_BUFFER_RESTART.loadFromFile("SFX/restart.wav");
	g_sharedContent->SFX_BUFFER_COLLISION.loadFromFile("SFX/tir.mp3");
	
	//Font and Text initialization
	g_sharedContent->FOND_DEFAULT.loadFromFile("font/GlitchGoblinv.ttf");

	g_sharedContent->TXT_DEFAULT.setFont(g_sharedContent->FOND_DEFAULT);
	g_sharedContent->TXT_SCORE.setFont(g_sharedContent->FOND_DEFAULT);
	g_sharedContent->TXT_HEALTHPOINTS_PLAYER.setFont(g_sharedContent->FOND_DEFAULT);

	g_sharedContent->TXT_DEFAULT.setCharacterSize(24);
	g_sharedContent->TXT_SCORE.setCharacterSize(24);
	g_sharedContent->TXT_HEALTHPOINTS_PLAYER.setCharacterSize(24);

	g_sharedContent->TXT_DEFAULT.setFillColor(sf::Color::Magenta);
	g_sharedContent->TXT_SCORE.setFillColor(sf::Color::Yellow);
	g_sharedContent->TXT_HEALTHPOINTS_PLAYER.setFillColor(sf::Color::Green);

	m_texts[ScoreText] = g_sharedContent->TXT_SCORE;
	m_texts[HPText] = g_sharedContent->TXT_HEALTHPOINTS_PLAYER;

}

void const AssetsManager::playSFX(SFX sound)
{
	sf::Sound* pSound = nullptr;

	switch (sound)
	{
	case LaserShotSound:
		g_sharedContent->SFX_LASER_SHOT.setBuffer(g_sharedContent->SFX_BUFFER_LASER_SHOT);
		g_sharedContent->SFX_LASER_SHOT.setVolume(g_sharedContent->VOLUME_SFX);
		pSound = &g_sharedContent->SFX_LASER_SHOT;
		break;
	case LaserHitSound:
		g_sharedContent->SFX_LASER_HIT.setBuffer(g_sharedContent->SFX_BUFFER_LASER_HIT);
		g_sharedContent->SFX_LASER_HIT.setVolume(g_sharedContent->VOLUME_SFX);
		pSound = &g_sharedContent->SFX_LASER_HIT;
		break;
	case RestartSound:
		g_sharedContent->SFX_RESTART.setBuffer(g_sharedContent->SFX_BUFFER_RESTART);
		g_sharedContent->SFX_RESTART.setVolume(g_sharedContent->VOLUME_SFX);
		pSound = &g_sharedContent->SFX_RESTART;
		break;
	case CollisionSound:
		g_sharedContent->SFX_COLLISION.setBuffer(g_sharedContent->SFX_BUFFER_COLLISION);
		g_sharedContent->SFX_COLLISION.setVolume(g_sharedContent->VOLUME_SFX);
		pSound = &g_sharedContent->SFX_COLLISION;
	default:
		break;
	}

	if (pSound != nullptr)
	{
		pSound->play();
	}
}