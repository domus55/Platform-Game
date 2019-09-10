#include "EnemyFlyingDemon.h"

int EnemyFlyingDemon::leftAnimation = -1;
int EnemyFlyingDemon::rightAnimation = -1;


EnemyFlyingDemon::EnemyFlyingDemon(float a, float h)
{
	textureRight.loadFromFile("images/enemy/flyingDemon/right1.png");
	textureLeft.loadFromFile("images/enemy/flyingDemon/left1.png");
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

		Animation::animation[leftAnimation]->addImage("images/enemy/flyingDemon/left1.png");
		Animation::animation[leftAnimation]->addImage("images/enemy/flyingDemon/left2.png");
		Animation::animation[leftAnimation]->addImage("images/enemy/flyingDemon/left3.png");
		Animation::animation[leftAnimation]->addImage("images/enemy/flyingDemon/left4.png");
		Animation::animation[leftAnimation]->addImage("images/enemy/flyingDemon/left5.png");
		Animation::animation[leftAnimation]->addImage("images/enemy/flyingDemon/left6.png");

		rightAnimation = Animation::addAnimation(6);
		Animation::animation[rightAnimation]->addImage("images/enemy/flyingDemon/right1.png");
		Animation::animation[rightAnimation]->addImage("images/enemy/flyingDemon/right2.png");
		Animation::animation[rightAnimation]->addImage("images/enemy/flyingDemon/right3.png");
		Animation::animation[rightAnimation]->addImage("images/enemy/flyingDemon/right4.png");
		Animation::animation[rightAnimation]->addImage("images/enemy/flyingDemon/right5.png");
		Animation::animation[rightAnimation]->addImage("images/enemy/flyingDemon/right6.png");

		firstTimeAniamation = false;
	}
	Animation::animation[leftAnimation]->blockAmount++;
	Animation::animation[rightAnimation]->blockAmount++;
}

void EnemyFlyingDemon::addEnemy(float a, float h)
{
	BasicEnemy::enemy.push_back(std::make_shared <EnemyFlyingDemon>(a * 50 + 25, h * 50 + 25));
}

void EnemyFlyingDemon::render(sf::RenderWindow *window)
{
	if (left) Animation::animation[leftAnimation]->render(&sprite, window);
		 else Animation::animation[rightAnimation]->render(&sprite, window);
}

void EnemyFlyingDemon::update(int deltaTime, int enemyNumber)
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