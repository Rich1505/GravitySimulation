#include "Body.h"

void Body::applyForce(Vector2& force)
{
	Vector2 forceAcc = Vector2Scale(force, 1.0f / mass);
	acceleration = Vector2Add(acceleration, forceAcc);

	velocity = Vector2Add(velocity, Vector2Scale(acceleration, GetFrameTime() * 100));

	position = Vector2Add(position, Vector2Scale(velocity, GetFrameTime() * 100));

	acceleration = { 0.0f,0.0f };
}

void Body::draw()
{
	DrawCircleV(position, radius, color);
}