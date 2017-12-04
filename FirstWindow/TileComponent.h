#pragma once

#include "Components.h"
#include "SDL.h"

enum TileType
{
	dirt = 0,
	grass,
	water,
	unknown
};

class TileComponent : public Component
{
public:
	PositionComponent* positionComponent;
	SpriteComponent* spriteComponent;
	SDL_Renderer* m_pRenderer;
	SDL_Rect tileRect;
	TileType tileType;
	char *path;

	TileComponent(SDL_Renderer* pRenderer)
	{
		tileType = unknown;
		path = "unknown.png";
		m_pRenderer = pRenderer;
	}
	TileComponent(int x, int y, int w, int h, TileType type, SDL_Renderer* pRenderer)
	{
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
		tileType = type;
		m_pRenderer = pRenderer;

		switch (tileType)
		{
		case dirt:
			path = "dirt.png";
			break;
		case grass:
			path = "grass.png";
			break;
		case water:
			path = "water.png";
			break;
		default:
			path = "unknown.png";
			break;
		}
	}

	void init() override
	{
		if (!entity->hasComponent<PositionComponent>())
			entity->addComponent<PositionComponent>(static_cast<float>(tileRect.x), static_cast<float>(tileRect.y), tileRect.w, tileRect.h, 1);
		positionComponent = &entity->getComponent<PositionComponent>();

		if (!entity->hasComponent<SpriteComponent>())
			entity->addComponent<SpriteComponent>(path, m_pRenderer);
		spriteComponent = &entity->getComponent<SpriteComponent>();
	}

};
