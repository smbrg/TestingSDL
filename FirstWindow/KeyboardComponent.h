#pragma once

#include "Components.h"

class KeyboardComponent : public Component
{
public:
	KeyboardComponent() = default;
	KeyboardComponent(SDL_Event* pEvent)
	{
		m_pEventHandle = pEvent;
	}

	PositionComponent* positionComponent;
	void init() override
	{
		if (!entity->hasComponent<PositionComponent>())
			entity->addComponent<PositionComponent>();
		positionComponent = &entity->getComponent<PositionComponent>();
	}

	void update() override
	{
		if (m_pEventHandle->type == SDL_KEYDOWN)
		{
			switch (m_pEventHandle->key.keysym.sym)
			{
			case SDLK_w:
				positionComponent->velocity.y = -1;
				break;
			case SDLK_a:
				positionComponent->velocity.x = -1;
				break;
			case SDLK_s:
				positionComponent->velocity.y = 1;
				break;
			case SDLK_d:
				positionComponent->velocity.x = 1;
				break;
			default:
				break;
			}
		}

		if (m_pEventHandle->type == SDL_KEYUP)
		{
			switch (m_pEventHandle->key.keysym.sym)
			{
			case SDLK_w:
				positionComponent->velocity.y = 0;
				break;
			case SDLK_a:
				positionComponent->velocity.x = 0;
				break;
			case SDLK_s:
				positionComponent->velocity.y = 0;
				break;
			case SDLK_d:
				positionComponent->velocity.x = 0;
				break;
			default:
				break;
			}
		}
	}

	void draw() override
	{

	}
private:
	SDL_Event* m_pEventHandle;
};