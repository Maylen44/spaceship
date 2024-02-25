#include "AssetsManager.h"

AssetsManager::AssetsManager()
	: m_volumeSFX(100.0f)
	, m_textures()
	, m_texts()
	, m_font()
{

	//Texture initialization
	sf::Texture background, playerShip, enemyShipA, enemyShipB, projectile;

	background.loadFromFile("sprites/bkgd_1.png");
	playerShip.loadFromFile("sprites/player.png");
	enemyShipA.loadFromFile("sprites/enemyA.png");
	enemyShipB.loadFromFile("sprites/enemyB.png");
	projectile.loadFromFile("sprites/projectile.png");

	m_textures[BackgroundType] = background;
	m_textures[PlayerType] = playerShip;
	m_textures[EnemyTypAType] = enemyShipA;
	m_textures[EnemyTypBType] = enemyShipB;
	m_textures[ProjectileType] = projectile;

	//SFX initialization
	laserSFXBuffer.loadFromFile("SFX/laser10.wav");
	laserHitSFXBuffer.loadFromFile("SFX/impactshort78.wav");
	restartSFXBuffer.loadFromFile("SFX/restart.wav");
	impactSFXBuffer.loadFromFile("SFX/tir.mp3");
	
	//Font and Text initialization
	m_font.loadFromFile("font/GlitchGoblinv.ttf");

	sf::Text defaultText;
	sf::Text scoreText;
	sf::Text healthPointsText;

	defaultText.setFont(m_font);
	scoreText.setFont(m_font);
	healthPointsText.setFont(m_font);

	defaultText.setCharacterSize(24);
	scoreText.setCharacterSize(24);
	healthPointsText.setCharacterSize(24);

	defaultText.setFillColor(sf::Color::Magenta);
	scoreText.setFillColor(sf::Color::Yellow);
	healthPointsText.setFillColor(sf::Color::Green);

	m_texts[DefaultText] = defaultText;
	m_texts[ScoreText] = scoreText;
	m_texts[HPText] = healthPointsText;

}

void const AssetsManager::playSFX(SFX sound)
{
	sf::Sound* pSound = nullptr;

	switch (sound)
	{
	case LaserShotSound:
		laserSFX.setBuffer(laserSFXBuffer);
		laserSFX.setVolume(m_volumeSFX * 0.5f);
		pSound = &laserSFX;
		break;
	case LaserHitSound:
		laserHitSFX.setBuffer(laserHitSFXBuffer);
		laserHitSFX.setVolume(m_volumeSFX * 0.5f);
		pSound = &laserHitSFX;
		break;
	case RestartSound:
		restartSFX.setBuffer(restartSFXBuffer);
		restartSFX.setVolume(m_volumeSFX);
		pSound = &restartSFX;
		break;
	case CollisionSound:
		impactSFX.setBuffer(impactSFXBuffer);
		impactSFX.setVolume(m_volumeSFX * 0.3f);
		pSound = &impactSFX;
	default:
		break;
	}

	if (pSound != nullptr)
	{
		pSound->play();
	}
}
