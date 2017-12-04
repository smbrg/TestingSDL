#pragma once

#include "SDL_image.h"
#include "Game.h"

class GameObject
{
public:
	GameObject(Game* pParent, const char* pTextureSheet, int nXpos, int nYpos);
	~GameObject();

	void update();
	void render();

private:
	int m_nXpos;
	int m_nYpos;

	SDL_Texture* m_pObjectTexture;
	SDL_Rect m_SrcRect, m_DestRect;

	Game* m_pParent;
};

