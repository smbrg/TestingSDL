#include "Game.h"
#include "Collision.h"
#include <iostream>

#define SAFE_DELETE(ptr) if (ptr) { delete ptr; ptr = nullptr; }

Game::Game()
	:   m_pManager(new Manager()),
		player(m_pManager->addEntity()),
		wall(m_pManager->addEntity())
{
	m_bIsRunning = false;
}

Game::~Game()
{
}

void Game::init(const char* title, int nXpos, int nYpos, int nWidth, int nHeight, bool bFullscreen)
{
	int nFlags = bFullscreen ? SDL_WINDOW_FULLSCREEN : 0;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialized!" << std::endl;

		m_pWindow = SDL_CreateWindow(title, nXpos, nYpos, nWidth, nHeight, nFlags);
		if (m_pWindow)
		{
			std::cout << "Window created!" << std::endl;
		}

		m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
		if (m_pRenderer)
		{
			std::cout << "Renderer created!" << std::endl;
			SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);

			m_pEvent = new SDL_Event();
		}

		m_bIsRunning = true;
	}
	else
	{
		m_bIsRunning = false;
	}

	player.addComponent<PositionComponent>(0.0f, 0.0f);
	player.addComponent<SpriteComponent>("wizard.png", m_pRenderer);
	player.addComponent<KeyboardComponent>(m_pEvent);
	player.addComponent<ColliderComponent>("player", m_vColliders);

	wall.addComponent<TileComponent>(300, 300, 300, 20, grass, m_pRenderer);
	wall.addComponent<ColliderComponent>("wall", m_vColliders);
}

void Game::handleEvents()
{
	SDL_PollEvent(m_pEvent);
	switch (m_pEvent->type)
	{
	case SDL_QUIT:
		m_bIsRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{
	m_pManager->refresh();
	m_pManager->update();

	for (auto CC : m_vColliders)
	{
		Collision::AABB(player.getComponent<ColliderComponent>(), *CC);
	}
}

void Game::render()
{
	SDL_RenderClear(m_pRenderer);

	m_pManager->draw();

	SDL_RenderPresent(m_pRenderer);
}

void Game::clean()
{
	SAFE_DELETE(m_pManager);

	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();

	std::cout << "Game cleaned!" << std::endl;
}