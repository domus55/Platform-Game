#pragma once
#include "BasicEnemy.h"
#include "Animation.h"

class EnemyDemon : public BasicEnemy
{
public:
	EnemyDemon(float a, float h);
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

