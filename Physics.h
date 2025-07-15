#pragma once
#include"Body.h"
#include<vector>
#include<raymath.h>

class Physics
{
private:
	std::vector<Body> bodies;
	const float G = 1.0f;

public:
	void addBody(Vector2& position, float mass, float radius,Color color);
	void addBody(Vector2& position, float mass, float radius, Color color, Vector2 &velocity);
	void update();
	void draw();
	Vector2 computeGravitationalForce(Body& a, Body& b);
};

