#pragma once

#include "Vector2D.h"
#include "Components.h"

class PositionComponent : public Component
{
public:

	Vector2D position;
	Vector2D velocity;

	int height = 32;
	int width = 32;
	int scale = 1;

	int speed = 3;

	PositionComponent()
	{
		position.Zero();
	}

	PositionComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	PositionComponent(float x, float y, int h, int w, int s)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = s;
	}

	void init() override 
	{
		velocity.Zero();
	}

	void update() override
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
};
