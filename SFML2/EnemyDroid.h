#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "BasicEnemy.h"
#include "Animation.h"


class EnemyDroid : public BasicEnemy
{
public:
	EnemyDroid(float a, float h);

	static void addEnemy(float a, float h);
	void render(sf::RenderWindow *window);
	void update(int deltaTime, int enemyNumber);


private:
	sf::Texture texture;

	static int animation;

	bool left;
};
