#pragma once
#include<raylib.h>
#include<raymath.h>
#include<vector>

class Body
{
public:
	static Body* selected;
	static constexpr float density = 0.03f;
	static constexpr int trailSize = 100;
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
	float mass;
	float radius;
	Color color;
	Vector2 trail[trailSize];
	Vector2 trailOrdered[trailSize];

	void applyForce(Vector2 force, float delta);
	void followMouse(Vector2 mousePos, bool gamePaused);
	void draw();
	float calculateRadius(float mass);
	void changeRadius(float mass);


	Body(const Vector2 position, float mass, Color color) : position(position),mass(mass),radius(calculateRadius(mass)), color(color)
	{
		velocity = { 0.0f,0.0f };
		acceleration = { 0.0f,0.0f };
		for (size_t i = 0; i < trailSize; i++)
		{
			trail[i] = this->position;
			trailOrdered[i] = this->position;
		}
	}

	Body(const Vector2 position, float mass, Color color, const Vector2 velocity) : Body(position,mass,color)
	{
		this->velocity = velocity;
	}

};

