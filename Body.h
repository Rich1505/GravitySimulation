#pragma once
#include<raylib.h>
#include<raymath.h>

class Body
{
public:
	const float density = 0.03f;
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
	float mass;
	float radius;
	Color color;

	void applyForce(Vector2 &force);
	void draw();
	float calculateRadius(float mass);

	Body(Vector2& position, float mass, Color color)
	{
		this->position = position;
		this->mass = mass;
		this->radius = calculateRadius(mass);
		this->color = color;

		velocity = { 0.0f,0.0f };
		acceleration = { 0.0f,0.0f };
	}

	Body(Vector2& position, float mass, Color color, Vector2 &velocity)
	{
		this->position = position;
		this->mass = mass;
		this->radius = calculateRadius(mass);
		this->color = color;

		this->velocity = velocity;
		acceleration = { 0.0f,0.0f };
	}
};

