#pragma once
#include "BasicEnemy.h"
#include "Animation.h"

class EnemyBoss : public BasicEnemy
{
public:
	EnemyBoss(float a, float h);
	static void addEnemy(float a, float h);
	void render(sf::RenderWindow *window);
	void update(int deltaTime, int enemyNumber);


private:
	sf::Texture texture;

	static int animation;

	bool left;
};

