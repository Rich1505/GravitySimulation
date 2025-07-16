#include "Body.h"

void Body::applyForce(Vector2& force)
{
	Vector2 forceAcc = Vector2Scale(force, 1.0f / mass);
	acceleration = Vector2Add(acceleration, forceAcc);

	velocity = Vector2Add(velocity, Vector2Scale(acceleration, GetFrameTime() * 10));

	position = Vector2Add(position, Vector2Scale(velocity, GetFrameTime() * 10));

	acceleration = { 0.0f,0.0f };
}

void Body::draw()
{
	DrawCircleV(position, radius, color);
}

float Body::calculateRadius(float mass)
{
	return cbrtf((3.0f * mass) / (4.0f * PI * density));
}

void Body::changeRadius(float mass)
{
	radius = calculateRadius(mass);
	this->mass = mass;
}