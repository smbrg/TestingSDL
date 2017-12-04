#include "TextureManager.h"
#include <iostream>

TextureManager::TextureManager(SDL_Renderer* pRenderer)
{
	m_pRenderer = pRenderer;


	std::cout << "Texture Manager created!" << std::endl;
}

TextureManager::~TextureManager()
{
}

SDL_Texture* TextureManager::loadTexture(const char* fileName)
{
	SDL_Surface* pTempSurface = IMG_Load(fileName);
	SDL_Texture* pRetTex = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);

	SDL_FreeSurface(pTempSurface);

	return pRetTex;
}