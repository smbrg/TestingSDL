#pragma once

#include <string>
#include "Components.h"
#include "Vector2D.h"

class ColliderComponent : public Component
{
public:
	SDL_Rect collider;
	std::string _tag;
	std::vector<ColliderComponent*>& _vColliders;

	ColliderComponent(std::string tag, std::vector<ColliderComponent*>& vColliders)
		: _vColliders(vColliders)
	{
		_tag = tag;
	}

	PositionComponent* positionComponent;

	void init() override
	{
		if (!entity->hasComponent<PositionComponent>())
			entity->addComponent<PositionComponent>();
		positionComponent = &entity->getComponent<PositionComponent>();

		_vColliders.push_back(this);
	}

	void update() override
	{
		collider.x = static_cast<int>(positionComponent->position.x);
		collider.y = static_cast<int>(positionComponent->position.y);
		collider.w = positionComponent->width * positionComponent->scale;
		collider.h = positionComponent->height * positionComponent->scale;
	}

};
