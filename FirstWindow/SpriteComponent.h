#pragma once

#include "Components.h"
#include "SDL.h"
#include "SDL_image.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent() = default;
	SpriteComponent(const char* path, SDL_Renderer* pRenderer)
	{
		renderer = pRenderer;

		#pragma warning(suppress : 4996)
		strcpy(curSpritePath, path);

		setTex(path);
	}

	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void setTex(const char* path)
	{
		if (strcmp(curSpritePath, path) != 0 || !texture)
		{
			#pragma warning(suppress : 4996)
			strcpy(curSpritePath, path);			

			SDL_Surface* tempSurface = IMG_Load(path);
			texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
			SDL_FreeSurface(tempSurface);
		}
	}

	void init() override
	{
		if (!entity->hasComponent<PositionComponent>())
			entity->addComponent<PositionComponent>();
		positionComponent = &entity->getComponent<PositionComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = positionComponent->width;
		srcRect.h = positionComponent->height;
	}

	void update() override
	{
		destRect.x = static_cast<int>(positionComponent->position.x);
		destRect.y = static_cast<int>(positionComponent->position.y);
		destRect.w = positionComponent->width * positionComponent->scale;
		destRect.h = positionComponent->height * positionComponent->scale;
	}

	void draw() override
	{
		SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
	}


private:
	PositionComponent* positionComponent;
	SDL_Texture* texture;
	SDL_Renderer* renderer;
	SDL_Rect srcRect;
	SDL_Rect destRect;

	char curSpritePath[128];
};
