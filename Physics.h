#pragma once
#include"Body.h"
#include<raymath.h>
#include<vector>

class Physics
{
private:
	static constexpr float G = 1.0f;

public:
	void update(std::vector<Body> &bodies, float delta);
	static Vector2 computeGravitationalForce(const Body& a, const Body& b);
	static Vector2 computeCircularVelocity(const Body& satellite, const Body& center);
};

