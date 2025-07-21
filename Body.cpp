#include "Body.h"
#include<iostream>

//check if a body is being dragged
Body* Body::selected = nullptr;

void Body::applyForce(Vector2 force, float delta)
{
	//not apply force on a dragged body
	if (selected == this)
		return;

	//2nd Newton Law {a = F/m}
	Vector2 forceAcc = Vector2Scale(force, 1.0f / mass);
	acceleration = Vector2Add(acceleration, forceAcc);

	velocity = Vector2Add(velocity, Vector2Scale(acceleration, delta));

	position = Vector2Add(position, Vector2Scale(velocity, delta));

	acceleration = { 0.0f,0.0f };
}

void Body::followMouse(Vector2 mousePos)
{
	Vector2 forceMouse = Vector2Subtract(mousePos, this->position);

	//apply the same force to every dragged body
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