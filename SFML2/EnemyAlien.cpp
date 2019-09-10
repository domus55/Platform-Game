#include "EnemyAlien.h"

int EnemyAlien::leftAnimation = -1;
int EnemyAlien::rightAnimation = -1;

EnemyAlien::EnemyAlien(float a, float h)
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
		leftAnimation = Animation::addAnimation(6);

		Animation::animation[leftAnimation]->addImage("images/enemy/alien/left1.png");
		Animation::animation[leftAnimation]->addImage("images/enemy/alien/left2.png");
		Animation::animation[leftAnimation]->addImage("images/enemy/alien/left3.png");

		rightAnimation = Animation::addAnimation(6);
		Animation::animation[rightAnimation]->addImage("images/enemy/alien/right1.png");
		Animation::animation[rightAnimation]->addImage("images/enemy/alien/right2.png");
		Animation::animation[rightAnimation]->addImage("images/enemy/alien/right3.png");

		firstTimeAniamation = false;
	}
	Animation::animation[leftAnimation]->blockAmount++;
	Animation::animation[rightAnimation]->blockAmount++;
}

void EnemyAlien::addEnemy(float a, float h)
{
	BasicEnemy::enemy.push_back(std::make_shared <EnemyAlien>(a * 50 + 25, h * 50 + 25));
}

void EnemyAlien::render(sf::RenderWindow *window)
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

void EnemyAlien::update(int deltaTime, int enemyNumber)
{
	if (speed.x < 0) left = true;
	if (speed.x > 0) left = false;

	checkDeath(enemyNumber);
	gravity.gravity(speed, deltaTime);
	speedInWater();
	AImove2();
	AIattack1(deltaTime);
	checkHitWall();
	
	move(deltaTime);
	checkCollision(deltaTime);
}