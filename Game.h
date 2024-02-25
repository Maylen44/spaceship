#ifndef GAME_H
#define GAME_H

#include "GameEngine.h"

class Game : public GameEngine
{
public:
	Game();

	void initialize();
	void run();
	void reset();

private:
	void progressGameLogic();

	bool m_isPlaying;
	int m_score;
};

#endif //GAME_H