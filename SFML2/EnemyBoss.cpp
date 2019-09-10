#include "EnemyBoss.h"

int EnemyBoss::animation = -1;

EnemyBoss::EnemyBoss(float a, float h)
{
	texture.loadFromFile("images/enemy/boss/Tofeles1.png");
	sprite.setTexture(texture);
	size = sprite.getTexture()->getSize();
	sprite.setOrigin(static_cast<float>(size.x / 2), static_cast<float>(size.y / 2));
	sprite.setPosition(a, h);
	left = true;

	dmg = 1;	//zmieniæ
	attackSpeed = 500;
	speeding.x = 0.0f;
	speeding.y = 0.0;
	maxHp = 100;
	hp = maxHp;

	static bool firstTimeAniamation = true;
	if (firstTimeAniamation)
	{
		animation = Animation::addAnimation(15);

		Animation::animation[animation]->addImage("images/enemy/boss/Tofeles1.png");
		Animation::animation[animation]->addImage("images/enemy/boss/Tofeles2.png");
		Animation::animation[animation]->addImage("images/enemy/boss/Tofeles3.png");
		Animation::animation[animation]->addImage("images/enemy/boss/Tofeles4.png");
		Animation::animation[animation]->addImage("images/enemy/boss/Tofeles5.png");
		Animation::animation[animation]->addImage("images/enemy/boss/Tofeles6.png");
		Animation::animation[animation]->addImage("images/enemy/boss/Tofeles7.png");
		Animation::animation[animation]->addImage("images/enemy/boss/Tofeles8.png");
		/*Animation::animation[animation]->addImage("images/enemy/boss/Tofeles7.png");
		Animation::animation[animation]->addImage("images/enemy/boss/Tofeles6.png");
		Animation::animation[animation]->addImage("images/enemy/boss/Tofeles5.png");
		Animation::animation[animation]->addImage("images/enemy/boss/Tofeles4.png");
		Animation::animation[animation]->addImage("images/enemy/boss/Tofeles3.png");
		Animation::animation[animation]->addImage("images/enemy/boss/Tofeles2.png");*/

		firstTimeAniamation = false;
	}
	Animation::animation[animation]->blockAmount++;;
}

void EnemyBoss::addEnemy(float a, float h)
{
	BasicEnemy::enemy.push_back(std::make_shared <EnemyBoss>(a * 50 + 25, h * 50 + 25));
}

void EnemyBoss::render(sf::RenderWindow * window)
{
	Animation::animation[animation]->render(&sprite, window);
}

void EnemyBoss::update(int deltaTime, int enemyNumber)
{
	checkDeath(enemyNumber);
	gravity.gravity(speed, deltaTime);
	speedInWater();
	//AImove2();
	AIattack1(deltaTime);
	checkHitWall();

	move(deltaTime);
	checkCollision(deltaTime);
}

