#include "Physics.h"

void Physics::update(std::vector<Body> &bodies)
{
	for (size_t i = 0; i < bodies.size(); i++)
	{
		Vector2 totalForce = { 0,0 };
		for (size_t j = 0; j < bodies.size(); j++)
		{
			if (i == j) continue;

			if (CheckCollisionCircles(bodies[i].position, bodies[i].radius, bodies[j].position, bodies[j].radius))
			{
				float totalMass = bodies[i].mass + bodies[j].mass;

				if (bodies[i].mass >= bodies[j].mass)
				{
					bodies[i].changeRadius(totalMass);
					bodies.erase(bodies.begin() + j);
				}
				else
				{
					bodies[j].changeRadius(totalMass);
					bodies.erase(bodies.begin() + i);
				}
				return;
			}

			
			Vector2 force = computeGravitationalForce(bodies[i], bodies[j]);
			totalForce = Vector2Add(totalForce, force);
		}

		bodies[i].applyForce(totalForce);
	}

}

Vector2 Physics::computeGravitationalForce(const Body& a, const Body& b)
{
	Vector2 direction = Vector2Subtract(b.position, a.position);
	float distance = Vector2Length(direction);
	distance = fmaxf(distance, 5.0f);
	direction = Vector2Normalize(direction);

	float forceMagnitude = G * (a.mass * b.mass) / (distance * distance);

	return Vector2Scale(direction, forceMagnitude);
}

Vector2 Physics::computeCircularVelocity(const Body& satellite, const Body& center)
{
	Vector2 direction = Vector2Subtract(satellite.position, center.position);

	float r = Vector2Length(direction);
	float v = sqrtf(G * center.mass / r);

	Vector2 orbitalVelocity = { -direction.y,direction.x };
	orbitalVelocity = Vector2Normalize(orbitalVelocity);
	orbitalVelocity = Vector2Scale(orbitalVelocity, v);

	return orbitalVelocity;
}