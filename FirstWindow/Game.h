#pragma once

#include "SDL.h"
#include "Components.h"

class Game
{
public:
	Game();
	~Game();

	void init(const char* cTitle, int nXpos, int nYpos, int nWidth, int nHeight, bool bFullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() { return m_bIsRunning; }
	SDL_Renderer* getRenderer() { return m_pRenderer; }
	SDL_Event* getEvent() { return m_pEvent; }
private:
	bool m_bIsRunning;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	SDL_Event* m_pEvent;
	Manager* m_pManager;

	Entity& player;
	Entity& wall;
	std::vector<ColliderComponent*> m_vColliders;
};

