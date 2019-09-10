#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "BasicEnemy.h"
#include "Animation.h"


class EnemyGhost : public BasicEnemy
{
public:
	EnemyGhost(float a, float h);
	static void addEnemy(float a, float h);
	void render(sf::RenderWindow *window);
	void update(int deltaTime, int enemyNumber);


private:
	sf::Texture textureLeft;
	sf::Texture textureRight;

	static int animation;

	bool left;
};

