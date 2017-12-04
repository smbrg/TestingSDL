#include "Game.h"

int main(int argc, char *argv[])
{
	const int nFPS = 60;
	const int nFrameDelay = 1000 / nFPS;

	Uint32 nFrameStart;
	int nFrameTime;

	Game* pGame = new Game();

	pGame->init("My first game!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

	int nTemp;

	while (pGame->running())
	{
		nFrameStart = SDL_GetTicks();

		pGame->handleEvents();
		pGame->update();
		pGame->render();

		nFrameTime = SDL_GetTicks() - nFrameStart;

		nTemp = nFrameDelay - nFrameTime;
		if (nTemp > 0)
		{
			SDL_Delay(nTemp);
		}
	}

	pGame->clean();

	return 0;
}