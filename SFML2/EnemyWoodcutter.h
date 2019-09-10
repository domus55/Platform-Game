#pragma once
#include "BasicEnemy.h"
#include "Animation.h"

class EnemyWoodcutter : public BasicEnemy
{
public:
	EnemyWoodcutter(float a, float h);

	static void addEnemy(float a, float h);
	void render(sf::RenderWindow *window);
	void update(int deltaTime, int enemyNumber);


private:
	sf::Texture textureLeft;
	sf::Texture textureRight;

	static int leftAnimation;
	static int rightAnimation;

	static int leftAttackAnimation;
	static int rightAttackAnimation;
	bool isAttacking;

	sf::Vector2f attackPosition;	//do ataku 2
	sf::Vector2f attackSize;
};

