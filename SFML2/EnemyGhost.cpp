#include "EnemyGhost.h"

int EnemyGhost::animation = -1;

EnemyGhost::EnemyGhost(float a, float h)
	: BasicEnemy()
{
	textureRight.loadFromFile("images/enemy/alien/right1.png");
	textureLeft.loadFromFile("images/enemy/alien/left1.png");
	sprite.setTexture(textureRight);
	size = sprite.getTexture()->getSize();
	sprite.setOrigin(static_cast<float>(size.x / 2), static_cast<float>(size.y / 2));
	sprite.setPosition(a, h);
	left = true;

	dmg = 1;
	attackSpeed = 500;
	speeding.x = 0.2;
	speeding.y = 1.0f;
	maxHp = 5;
	hp = maxHp;

	static bool firstTimeAniamation = true;
	if (firstTimeAniamation)
	{
		animation = Animation::addAnimation(8);

		Animation::animation[animation]->addImage("images/enemy/ghost/1.png");
		Animation::animation[animation]->addImage("images/enemy/ghost/2.png");
		Animation::animation[animation]->addImage("images/enemy/ghost/3.png");
		Animation::animation[animation]->addImage("images/enemy/ghost/4.png");

		firstTimeAniamation = false;
	}
	Animation::animation[animation]->blockAmount++;
}

void EnemyGhost::addEnemy(float a, float h)
{
	BasicEnemy::enemy.push_back(std::make_shared <EnemyGhost>(a * 50 + 25, h * 50 + 25));
}

void EnemyGhost::render(sf::RenderWindow *window)
{

	Animation::animation[animation]->render(&sprite, window);
}

void EnemyGhost::update(int deltaTime, int enemyNumber)
{
	if (speed.x < 0) left = true;
	if (speed.x > 0) left = false;

	checkDeath(enemyNumber);
	speedInWater();
	inWater = true;
	AImove4();
	AIattack1(deltaTime);
	checkHitWall();

	move(deltaTime);
	//checkCollision(deltaTime);
}
