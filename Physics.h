#pragma once
#include"Body.h"
#include<raymath.h>
#include<vector>

class Physics
{
private:
	const float G = 1.0f;

public:
	void update(std::vector<Body> &bodies);
	Vector2 computeGravitationalForce(const Body& a, const Body& b);
	Vector2 computeCircularVelocity(const Body& satellite, const Body& center);
};

