#include "EnemyWoodcutter.h"

int EnemyWoodcutter::leftAnimation = -1;
int EnemyWoodcutter::rightAnimation = -1;
int EnemyWoodcutter::leftAttackAnimation = -1;
int EnemyWoodcutter::rightAttackAnimation = -1;

EnemyWoodcutter::EnemyWoodcutter(float a, float h)
{
	textureRight.loadFromFile("images/enemy/woodcutter/rightAttack/1.png");
	textureLeft.loadFromFile("images/enemy/woodcutter/leftAttack/1.png");
	sprite.setTexture(textureRight);
	size = sprite.getTexture()->getSize();
	sprite.setOrigin(static_cast<float>(size.x / 2), static_cast<float>(size.y / 2));
	sprite.setPosition(a, h);
	left = true;
	isAttacking = false;

	dmg = 2.0;
	attackSpeed = 1000;
	speeding.x = 0.15;
	speeding.y = 1.0f;
	maxHp = 15;
	hp = maxHp;
	//21, -16), sf::Vector2f(7, 1));
	attackPosition.x = 21;
	attackPosition.y = -16;
	attackSize.x = 20;
	attackSize.y = 1;

	static bool firstTimeAniamation = true;
	if (firstTimeAniamation)
	{
		rightAttackAnimation = Animation::addAnimation(15);

		Animation::animation[rightAttackAnimation]->addImage("images/enemy/woodcutter/rightAttack/1.png");
		Animation::animation[rightAttackAnimation]->addImage("images/enemy/woodcutter/rightAttack/2.png");
		Animation::animation[rightAttackAnimation]->addImage("images/enemy/woodcutter/rightAttack/3.png");
		Animation::animation[rightAttackAnimation]->addImage("images/enemy/woodcutter/rightAttack/4.png");

		leftAttackAnimation = Animation::addAnimation(15);

		Animation::animation[leftAttackAnimation]->addImage("images/enemy/woodcutter/leftAttack/1.png");
		Animation::animation[leftAttackAnimation]->addImage("images/enemy/woodcutter/leftAttack/2.png");
		Animation::animation[leftAttackAnimation]->addImage("images/enemy/woodcutter/leftAttack/3.png");
		Animation::animation[leftAttackAnimation]->addImage("images/enemy/woodcutter/leftAttack/4.png");

		leftAnimation = Animation::addAnimation(20);
		Animation::animation[leftAnimation]->addImage("images/enemy/woodcutter/leftAttack/1.png");
		Animation::animation[leftAnimation]->addImage("images/enemy/woodcutter/leftAttack/2.png");

		rightAnimation = Animation::addAnimation(20);
		Animation::animation[rightAnimation]->addImage("images/enemy/woodcutter/rightAttack/1.png");
		Animation::animation[rightAnimation]->addImage("images/enemy/woodcutter/rightAttack/2.png");

		firstTimeAniamation = false;
	}
	Animation::animation[rightAttackAnimation]->blockAmount++;
	Animation::animation[leftAttackAnimation]->blockAmount++;
	Animation::animation[rightAnimation]->blockAmount++;
	Animation::animation[leftAnimation]->blockAmount++;
}

void EnemyWoodcutter::addEnemy(float a, float h)
{
	BasicEnemy::enemy.push_back(std::make_shared <EnemyWoodcutter>(a * 50 + 25, h * 50 + 25));
}

void EnemyWoodcutter::render(sf::RenderWindow * window)
{
	if (isAttacking)
	{
		if (left) Animation::animation[leftAttackAnimation]->render(&sprite, window);
		else Animation::animation[rightAttackAnimation]->render(&sprite, window);
	}
	else
	{
		if (left) Animation::animation[leftAnimation]->render(&sprite, window);
		else Animation::animation[rightAnimation]->render(&sprite, window);
	}
	

	window->draw(sprite);
}

void EnemyWoodcutter::update(int deltaTime, int enemyNumber)
{
	if (speed.x < 0) left = true;
	if (speed.x > 0) left = false;

	checkDeath(enemyNumber);
	gravity.gravity(speed, deltaTime);
	speedInWater();
	AImove2();

	if (checkAttack2(attackPosition, attackSize)) 
	{
		isAttacking = true;
		//AIattack2(deltaTime, attackPosition, attackSize);

		if(left && Animation::animation[leftAttackAnimation]->licznik2 == 0 )AIattack2(deltaTime, attackPosition, attackSize);	//dodaæ to
		if (!left && Animation::animation[rightAttackAnimation]->licznik2 == 0)AIattack2(deltaTime, attackPosition, attackSize);
	}
	else 
	{
		isAttacking = false; Animation::animation[leftAttackAnimation]->licznik2 = 0;
		isAttacking = false; Animation::animation[rightAttackAnimation]->licznik2 = 0;
	}
	
	checkHitWall();
	move(deltaTime);
	checkCollision(deltaTime);
}
