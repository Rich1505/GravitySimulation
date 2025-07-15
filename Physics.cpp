#include "Physics.h"

void Physics::update()
{
	for (size_t i = 0; i < bodies.size(); i++)
	{
		Vector2 totalForce = { 0,0 };
		for (size_t j = 0; j < bodies.size(); j++)
		{
			if (i == j) continue;

			Vector2 force = computeGravitationalForce(bodies[i], bodies[j]);
			totalForce = Vector2Add(totalForce, force);
		}

		bodies[i].applyForce(totalForce);
	}

	draw();
}

void Physics::draw()
{
	for (int i = 0; i < bodies.size(); i++)
	{
		bodies[i].draw();
	}
}

Vector2 Physics::computeGravitationalForce(Body& a, Body& b)
{
	Vector2 direction = Vector2Subtract(b.position, a.position);
	float distance = Vector2Length(direction);
	distance = fmaxf(distance, 5.0f);
	direction = Vector2Normalize(direction);

	float forceMagnitude = G * (a.mass * b.mass) / (distance * distance);

	return Vector2Scale(direction, forceMagnitude);
}

void Physics::addBody(Vector2& position, float mass, float radius, Color color)
{
	bodies.push_back(Body{ position,mass,radius,color });
}

void Physics::addBody(Vector2& position, float mass, float radius, Color color, Vector2 &velocity)
{
	bodies.push_back(Body{ position,mass,radius,color,velocity});
}