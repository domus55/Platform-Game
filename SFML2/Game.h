#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <windows.h>
#include <iostream>
#include "HUD.h"
#include "Background.h"
#include "Player.h"
#include "Block.h"
#include "LevelMenager.h"
#include "MenuMenager.h"
#include "GameInfo.h"
#include "BasicEnemy.h"
#include "Bonus.h"
#include "Shoot.h"
#include "Splinter.h"
#include "Visible.h"
#include "Camera.h"

class Game
{
public:
	sf::RenderWindow window;
	sf::View view;
	sf::Music music;
	bool isRunning;
	int maxFPS = 140;
	int deltaTime;

	Game();
	void exit();
	void update();
	void output();
	void wait();
	~Game();
};

