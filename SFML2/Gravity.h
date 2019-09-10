#pragma once

#include <SFML/Graphics.hpp>

class Gravity
{
public:
	Gravity();
	void gravity(sf::Vector2f &speed, int deltaTime);

	float gravityForce;
	float slowing;
};

