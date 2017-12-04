#include "Map.h"
#include <iostream>


int lvl1[20][25] = {
						{ 0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,1,1,1,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,1,1,1,2,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,1,1,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,1,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					 };

Map::Map(TextureManager* pTextureManager, SDL_Renderer* pRenderer)
{
	m_pDirt = pTextureManager->loadTexture("dirt.png");
	m_pGrass = pTextureManager->loadTexture("grass.png");
	m_pWater = pTextureManager->loadTexture("water.png");
	m_pUnknown = pTextureManager->loadTexture("unknown.png");

	m_pRenderer = pRenderer;

	load(lvl1);
}


Map::~Map()
{
	SDL_DestroyTexture(m_pDirt);
	SDL_DestroyTexture(m_pGrass);
	SDL_DestroyTexture(m_pUnknown);
	SDL_DestroyTexture(m_pWater);
}

void Map::load(int arr[20][25])
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			m_Map[i][j] = arr[i][j];
		}
	}
}

void Map::render()
{
	int nTileType;
	SDL_Texture* pTempTex = m_pUnknown;
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = srcRect.y = destRect.x = destRect.y = 0;
	srcRect.w = srcRect.h = destRect.w = destRect.h = 32;

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			nTileType = m_Map[i][j];
			destRect.x = j * 32;
			destRect.y = i * 32;

			switch (nTileType)
			{
			case olddirt:
				pTempTex = m_pDirt;
				break;
			case oldwater:
				pTempTex = m_pWater;
				break;
			case oldgrass:
				pTempTex = m_pGrass;
				break;
			default:
				std::cout << "Error: Unknown map tile" << std::endl;
				break;
			}
			SDL_RenderCopy(m_pRenderer, pTempTex, &srcRect, &destRect);
		}
	}
}
