#include "Gravity.h"


Gravity::Gravity()
{
	gravityForce = 1;
	slowing = 1;
}

void Gravity::gravity(sf::Vector2f & speed, int deltaTime)
{
	speed.y += 0.03f *gravityForce * deltaTime / 16;
	speed.y -= speed.y / 100 * slowing * deltaTime / 16;
}
