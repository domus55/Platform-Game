#include "EnemyDemon.h"

int EnemyDemon::rightAnimation = -1;
int EnemyDemon::leftAnimation = -1;

EnemyDemon::EnemyDemon(float a, float h)
{
	textureRight.loadFromFile("images/enemy/demon/right1.png");
	textureLeft.loadFromFile("images/enemy/demon/left1.png");
	sprite.setTexture(textureRight);
	size = sprite.getTexture()->getSize();
	sprite.setOrigin(static_cast<float>(size.x / 2), static_cast<float>(size.y / 2));
	sprite.setPosition(a, h);
	left = true;

	dmg = 1.5;
	attackSpeed = 500;
	speeding.y = 1.0f;
	speeding.x = 0.25;
	maxHp = 8;
	hp = maxHp;

	static bool firstTimeAniamation = true;
	if (firstTimeAniamation)
	{
		leftAnimation = Animation::addAnimation(5);

		Animation::animation[leftAnimation]->addImage("images/enemy/demon/left1.png");
		Animation::animation[leftAnimation]->addImage("images/enemy/demon/left2.png");
		Animation::animation[leftAnimation]->addImage("images/enemy/demon/left3.png");
		Animation::animation[leftAnimation]->addImage("images/enemy/demon/left4.png");
		Animation::animation[leftAnimation]->addImage("images/enemy/demon/left5.png");
		Animation::animation[leftAnimation]->addImage("images/enemy/demon/left4.png");
		Animation::animation[leftAnimation]->addImage("images/enemy/demon/left3.png");
		Animation::animation[leftAnimation]->addImage("images/enemy/demon/left2.png");
		

		rightAnimation = Animation::addAnimation(5);
		Animation::animation[rightAnimation]->addImage("images/enemy/demon/right1.png");
		Animation::animation[rightAnimation]->addImage("images/enemy/demon/right2.png");
		Animation::animation[rightAnimation]->addImage("images/enemy/demon/right3.png");
		Animation::animation[rightAnimation]->addImage("images/enemy/demon/right4.png");
		Animation::animation[rightAnimation]->addImage("images/enemy/demon/right5.png");
		Animation::animation[rightAnimation]->addImage("images/enemy/demon/right4.png");
		Animation::animation[rightAnimation]->addImage("images/enemy/demon/right3.png");
		Animation::animation[rightAnimation]->addImage("images/enemy/demon/right2.png");

		firstTimeAniamation = false;
	}
	Animation::animation[leftAnimation]->blockAmount++;
	Animation::animation[rightAnimation]->blockAmount++;
}

void EnemyDemon::addEnemy(float a, float h)
{
	BasicEnemy::enemy.push_back(std::make_shared <EnemyDemon>(a * 50 + 25, h * 50 + 25));
}

void EnemyDemon::render(sf::RenderWindow * window)
{
	//if (canJump && speed.x != 0)
	//{
		if (left) Animation::animation[leftAnimation]->render(&sprite, window);
		else Animation::animation[rightAnimation]->render(&sprite, window);
	//}
	//else
	//{
	//	if (left) sprite.setTexture(textureLeft);
	//	else sprite.setTexture(textureRight);

	//	window->draw(sprite);
	//}
}

void EnemyDemon::update(int deltaTime, int enemyNumber)
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
