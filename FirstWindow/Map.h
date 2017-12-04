#pragma once

#include "TextureManager.h"

enum MapTiles
{
	olddirt = 0,
	oldgrass,
	oldwater,
	oldunknown
};

class Map
{
public:
	Map(TextureManager* pTextureManager, SDL_Renderer* pRenderer);
	~Map();

	void load(int arr[20][25]);
	void render();

private:
	SDL_Rect m_SrcRect, m_DestRect;
	SDL_Texture* m_pDirt;
	SDL_Texture* m_pGrass;
	SDL_Texture* m_pWater;
	SDL_Texture* m_pUnknown;

	SDL_Renderer* m_pRenderer;

	int m_Map[20][25];
};

