#ifndef ASSETS_MANAGER_H
#define ASSETS_MANAGER_H

#include "SharedContent.h"

class AssetsManager
{
public:
	static AssetsManager* instance();
	void const playSFX(SFX sound);

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
		SFX_RESTART,
		SFX_COLLISION;
	sf::Font FOND_DEFAULT;
	sf::Text TXT_SCORE,
		TXT_HEALTHPOINTS_PLAYER;

	float VOLUME_SFX{ 100.0f };
	float VOLUME_MUSIC{ 100.0f };

private:
	AssetsManager();
};

#endif //ASSETS_MANAGER_H