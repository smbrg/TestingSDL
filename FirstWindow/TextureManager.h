#pragma once

#include "SDL.h"
#include "SDL_image.h"

class TextureManager
{
public:
	TextureManager(SDL_Renderer* pRenderer);
	~TextureManager();

	SDL_Texture* loadTexture(const char* fileName);

private:
	SDL_Renderer* m_pRenderer;
};

