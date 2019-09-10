#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "BasicEnemy.h"
#include "Animation.h"


class EnemyZombie : public BasicEnemy
{
public:
	EnemyZombie(float a, float h, float distance);
	static void addEnemy(float a, float h, float distance);
	void render(sf::RenderWindow *window);
	void update(int deltaTime, int enemyNumber);


private:
	sf::Texture textureLeft;
	sf::Texture textureRight;

	static int leftAnimation;
	static int rightAnimation;

	bool left;
	float distance;
};

