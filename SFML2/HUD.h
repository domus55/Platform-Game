#pragma once

#include "GameInfo.h"
#include "BasicEnemy.h"
#include "Player.h"

class HUD
{
public:
	static void renderHp(sf::RenderWindow *window);
	static void renderDeadScreen(sf::RenderWindow *window);
	static bool deadScreen;
};

