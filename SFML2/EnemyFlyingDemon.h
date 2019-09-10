#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "BasicEnemy.h"
#include "Animation.h"


class EnemyFlyingDemon : public BasicEnemy
{
public:
	EnemyFlyingDemon(float a, float h);

	static void addEnemy(float a, float h);
	void render(sf::RenderWindow *window);
	void update(int deltaTime, int enemyNumber);


private:
	sf::Texture textureLeft;
	sf::Texture textureRight;

	static int leftAnimation;
	static int rightAnimation;

	bool left;
};
