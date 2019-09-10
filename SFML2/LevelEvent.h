#pragma once

#include <iostream>
#include <ctime>
#include "player.h"
#include "Menu.h"
#include "Background.h"

class LevelEvent
{
public:
	static void levelEvent(int level, int deltaTime);
	static bool restart;
	static int deltaTime;
private:
	static void level1();
	static void level2();
	static void level3();
	static void level4();
	static void level5();
	static void level6();
};

