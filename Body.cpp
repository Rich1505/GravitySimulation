#include "Body.h"
#include<iostream>


Body* Body::selected = nullptr;

void Body::applyForce(Vector2 force, float delta)
{
	if (selected == this)
		return;

	Vector2 forceAcc = Vector2Scale(force, 1.0f / mass);
	acceleration = Vector2Add(acceleration, forceAcc);

	velocity = Vector2Add(velocity, Vector2Scale(acceleration, delta));

	position = Vector2Add(position, Vector2Scale(velocity, delta));

	acceleration = { 0.0f,0.0f };
}

void Body::followMouse(Vector2 mousePos, bool gamePaused)
{
	Vector2 forceMouse = Vector2Subtract(mousePos, this->position);
	forceMouse = Vector2Scale(forceMouse, 1000.0f);
	this->velocity = { 0.0f,0.0f };
	Vector2 forceAcc = Vector2Scale(forceMouse, 1.0f / 20.0f * 0.02f * (float)GetFPS());
	acceleration = Vector2Add(acceleration, forceAcc);

	velocity = Vector2Add(velocity, Vector2Scale(acceleration, GetFrameTime() * 3.0f));
	position = Vector2Add(position, Vector2Scale(velocity, GetFrameTime() * 3.0f));
	
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