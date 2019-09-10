#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.h"
#include "Block.h"
#include "Player.h"
#include "EnemyAlien.h"
#include "EnemyDemon.h"
#include "EnemyBoss.h"
#include "EnemyWoodcutter.h"
#include "EnemyZombie.h"
#include "EnemyFlyingDemon.h"
#include "EnemyDroid.h"
#include "EnemyGhost.h"
#include "LevelEvent.h"
#include "Bonus.h"
#include "Shoot.h"
#include "Splinter.h"
#include "Loading.h"

class LevelMenager
{
public:
	static void makeAll(sf::RenderWindow *window, bool nextLevel, int deltaTime);
	static void restartLevel(sf::RenderWindow *window);
	static void makeLevel(sf::RenderWindow *window, sf::Image image, int up = 0);
	static int level;	//max iloœæ bloków - 3000
private:
	static void level1(sf::RenderWindow *window);
	static void level2(sf::RenderWindow *window);
	static void level3(sf::RenderWindow *window);
	static void level4(sf::RenderWindow *window);
	static void level5(sf::RenderWindow *window);
	static void level6(sf::RenderWindow *window);
	static void level7(sf::RenderWindow *window);
	static void level8(sf::RenderWindow *window);
	static void level9(sf::RenderWindow *window);
	static void level10(sf::RenderWindow *window);
	static void level11(sf::RenderWindow *window);
	static void level12(sf::RenderWindow *window);
	static void level13(sf::RenderWindow *window);
	static void level14(sf::RenderWindow *window);
	static void level15(sf::RenderWindow *window);

};

