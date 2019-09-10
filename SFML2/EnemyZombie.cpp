#include "EnemyZombie.h"

int EnemyZombie::leftAnimation = -1;
int EnemyZombie::rightAnimation = -1;

EnemyZombie::EnemyZombie(float a, float h, float distance)
	: BasicEnemy()
{
	textureRight.loadFromFile("images/enemy/zombie/right1.png");
	textureLeft.loadFromFile("images/enemy/zombie/left1.png");
	sprite.setTexture(textureRight);
	size = sprite.getTexture()->getSize();
	sprite.setOrigin(static_cast<float>(size.x / 2), static_cast<float>(size.y / 2));
	sprite.setPosition(a, h);
	left = true;
	this -> distance = distance;

	dmg = 1;
	attackSpeed = 500;
	speeding.x = 0.2;
	speeding.y = 1.0f;
	maxHp = 5;
	hp = maxHp;

	static bool firstTimeAniamation = true;
	if (firstTimeAniamation)
	{
		leftAnimation = Animation::addAnimation(15);

		Animation::animation[leftAnimation]->addImage("images/enemy/zombie/left1.png");
		Animation::animation[leftAnimation]->addImage("images/enemy/zombie/left2.png");

		rightAnimation = Animation::addAnimation(15);
		Animation::animation[rightAnimation]->addImage("images/enemy/zombie/right1.png");
		Animation::animation[rightAnimation]->addImage("images/enemy/zombie/right2.png");

		firstTimeAniamation = false;
	}
	Animation::animation[leftAnimation]->blockAmount++;
	Animation::animation[rightAnimation]->blockAmount++;
}

void EnemyZombie::addEnemy(float a, float h, float distance)
{
	BasicEnemy::enemy.push_back(std::make_shared <EnemyZombie>(a * 50 + 25, h * 50 + 25, distance));
}

void EnemyZombie::render(sf::RenderWindow *window)
{
	if (canJump && speed.x != 0)
	{
		if (left) Animation::animation[leftAnimation]->render(&sprite, window);
		else Animation::animation[rightAnimation]->render(&sprite, window);
	}
	else
	{
		if (left) sprite.setTexture(textureLeft);
		else sprite.setTexture(textureRight);

		window->draw(sprite);
	}
}

void EnemyZombie::update(int deltaTime, int enemyNumber)
{
	if (speed.x < 0) left = true;
	if (speed.x > 0) left = false;

	checkDeath(enemyNumber);
	gravity.gravity(speed, deltaTime);
	speedInWater();
	AImove3(distance);
	AIattack1(deltaTime);
	checkHitWall();

	move(deltaTime);
	checkCollision(deltaTime);
}