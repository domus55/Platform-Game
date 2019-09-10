#include "EnemyDroid.h"

int EnemyDroid::animation = -1;


EnemyDroid::EnemyDroid(float a, float h)
{
	texture.loadFromFile("images/enemy/droid/1.png");
	sprite.setTexture(texture);
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
		animation = Animation::addAnimation(6);
		Animation::animation[animation]->addImage("images/enemy/droid/1.png");
		Animation::animation[animation]->addImage("images/enemy/droid/2.png");

		firstTimeAniamation = false;
	}
	Animation::animation[animation]->blockAmount++;

	sprite.setScale(2, 2);
}

void EnemyDroid::addEnemy(float a, float h)
{
	BasicEnemy::enemy.push_back(std::make_shared <EnemyDroid>(a * 50 + 25, h * 50 + 25));
}

void EnemyDroid::render(sf::RenderWindow *window)
{
	Animation::animation[animation]->render(&sprite, window);
}

void EnemyDroid::update(int deltaTime, int enemyNumber)
{
	if (speed.x < 0) left = true;
	if (speed.x > 0) left = false;

	checkDeath(enemyNumber);
	//gravity.gravity(speed);
	speedInWater();
	inWater = true;
	AImove4();
	AIattack1(deltaTime);
	checkHitWall();

	move(deltaTime);
	checkCollision(deltaTime);
}