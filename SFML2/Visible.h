#pragma once

#include "Block.h"
#include "Collision.h"
#include "GameInfo.h"

class Visible
{
public:
	static void makeAll();
	static void blockSetVisible();

private:
	static bool boolCollision(sf::Vector2f position2, sf::Vector2f size2);
};

