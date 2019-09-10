#include "BasicEnemy.h"
#include "Player.h"

std::vector < std::shared_ptr <BasicEnemy> > BasicEnemy::enemy;
sf::SoundBuffer BasicEnemy::bufferHit;
sf::SoundBuffer BasicEnemy::bufferDead;
sf::Sound BasicEnemy::soundHit;
sf::Sound BasicEnemy::soundDead;

BasicEnemy::BasicEnemy()
{
	deltaTime2 = 0;
	goLeft = false;
	goRight = false;
	goUp = false;
	goDown = false;
	firstTime = true;
	hitWall = false;
	hitWall2 = false;
	hitFloor = false;
	hitFloor2 = false;
	check = true;
	right = false;
	canJump = false;
	inWater = false;

	attackSpeed = 500;
	speeding.x = 0.2;
	speeding.y = 1.0f;
	maxHp = 3;
	hp = maxHp;
	dmg = 1;

	static bool firsttTime = true;
	if (firsttTime)
	{
		bufferHit.loadFromFile("music/hitEnemy.wav");
		bufferDead.loadFromFile("music/deadEnemy.wav");
		soundHit.setBuffer(bufferHit);
		soundDead.setBuffer(bufferDead);
		firsttTime = false;
	}
}

void BasicEnemy::renderAll(sf::RenderWindow *window)
{
	for (int i = BasicEnemy::enemy.size() - 1; i >= 0; i--)
	{
		BasicEnemy::enemy[i]->render(window);
	}
}

void BasicEnemy::renderAllHp(sf::RenderWindow * window)
{
	for (int i = BasicEnemy::enemy.size() - 1; i >= 0; i--)
	{
		BasicEnemy::enemy[i]->renderHp2(window);
	}
}

void BasicEnemy::updateAll(int deltaTime)
{
	for (int i = BasicEnemy::enemy.size() - 1; i >= 0; i--)
	{
		BasicEnemy::enemy[i]->update(deltaTime, i);
	}
}

void BasicEnemy::renderHp2(sf::RenderWindow * window)
{
	renderHp.render(window, sprite, hp, maxHp);
}

void BasicEnemy::hited(float dmg)
{
	sf::Vector2f v = sprite.getPosition();
	hp -= dmg;

	if (hp <= 0)
	{	
		Sound::setVolume(soundDead, sprite.getPosition());
		soundDead.play();
	}
	else
	{
		Sound::setVolume(soundHit, sprite.getPosition());
		soundHit.play();
	}
	

	if(hp <= 0) Splinter::addSplinter(v.x, v.y, "blood", 50, false);
	else Splinter::addSplinter(v.x, v.y, "blood", 10, false);
}

sf::Vector2f BasicEnemy::getPosition()
{
	return sprite.getPosition();
}

sf::Vector2f BasicEnemy::getSize()
{
	sf::Vector2f size;
	size.x = sprite.getScale().x * this->size.x;
	size.y = sprite.getScale().y * this->size.y;

	return size;
}

void BasicEnemy::checkDeath(int enemyNumber)
{
	if (hp <= 0)
	{
		enemy.erase(enemy.begin() + enemyNumber);
	}
}

bool BasicEnemy::collision(sf::Vector2f position2, sf::Vector2f size2)
{
	sf::Vector2f position;
	sf::Vector2f size;

	position = sprite.getPosition();
	size.x = sprite.getScale().x * this->size.x;
	size.y = sprite.getScale().y * this->size.y;

	Collision collision(position, size);
	sf::Vector2f changePosition = collision.checkCollision(position2, size2);

	/*if (changePosition.y < 0.0f) canJump = true;
	if (changePosition.y != 0.0f) speed.y = 0;
	if (changePosition.x != 0.0f && hitWall2) { hitWall = true; hitWall2 = false; }
	if (changePosition.x != 0.0f) hitWall2 = true;
	if (speed.y != 0) canJump = false;*/

	if (hitWall) speed.x = 0;	//naprawiæ
	if (hitFloor) speed.y = 0;
	if (changePosition.y < 0.0f) canJump = true;

	if (changePosition.x != 0.0f && hitWall2) { hitWall = true; hitWall2 = false; }
	if (changePosition.x != 0.0f) hitWall2 = true;
	if (changePosition.y != 0.0f && hitFloor2) { hitFloor = true; hitFloor2 = false; }
	if (changePosition.y != 0.0f) hitFloor2 = true;

	sprite.move(changePosition);

	if (changePosition.x == 0 && changePosition.y == 0) return false;
	return true;
}

bool BasicEnemy::boolCollision(sf::Vector2f position2, sf::Vector2f size2)
{
	sf::Vector2f position;
	sf::Vector2f size;

	position = sprite.getPosition();
	size.x = sprite.getScale().x * this->size.x;
	size.y = sprite.getScale().y * this->size.y;

	Collision collision(position, size);

	return collision.boolCheckCollision(position2, size2);
}

void BasicEnemy::checkHitWall()
{
	check = !check;
	hitWall = false;
	hitFloor = false;
	if (check) { hitWall2 = false; hitFloor2 = false; }
}

void BasicEnemy::jump()
{
	if (canJump)
	{
		speed.y -= speeding.y;
		canJump = false;
	}
	
}

void BasicEnemy::speedInWater()
{
	if (inWater)
	{
		gravity.slowing = 10;
		gravity.gravityForce = 0.5;
		canJump = false;
	}
	else
	{
		gravity.slowing = 1;
		gravity.gravityForce = 1;
	}
}

void BasicEnemy::AImove1()
{
	if (hitWall) right = !right;

	if (right) goRight = true;
	else goLeft = true;
}

void BasicEnemy::AImove2()
{
	float minDistance = 99999;
	float distance = 99999;
	unsigned int nearestPlayer = 0;
	for (unsigned int i = 0; i < Player::player.size(); i++)
	{
		distance = Collision::distance(Player::player[i]->getPosition(), sprite.getPosition());
		if (distance < minDistance) minDistance = distance;
	}

	for (unsigned int i = 0; i < Player::player.size(); i++)
	{
		distance = Collision::distance(Player::player[i]->getPosition(), sprite.getPosition());
		if (minDistance == distance) nearestPlayer = i;
	}

	sf::Vector2f v = sprite.getPosition();
	float y = v.y;
	float x = v.x;

	if (inWater)
	{
		if (Player::player[nearestPlayer]->getPositionY() - y < -5) goUp = true;
		if (abs(Player::player[nearestPlayer]->getPositionX() - x) > 10)
		{
			if (Player::player[nearestPlayer]->getPositionX() > x) goRight = true;
			else goLeft = true;
		}
		else speed.x = 0;
	}
	else
	{
		if (Player::player[nearestPlayer]->getPositionY() - y < -50) goUp = true;
		if (abs(Player::player[nearestPlayer]->getPositionX() - x) > 10)
		{
			if (Player::player[nearestPlayer]->getPositionX() > x) goRight = true;
			else goLeft = true;
		}
		else speed.x = 0;
	}
	
}

void BasicEnemy::AImove3(int distance)
{
	sf::Vector2f v = sprite.getPosition();
	if (firstTime)
	{
		startPosition = v.x;
		right = true;
		firstTime = false;

	}
	if (right) goRight = true;
	else goLeft = true;

	if (v.x >= startPosition + distance) right = false;
	if (v.x <= startPosition) right = true;

}

void BasicEnemy::AImove4()
{
	float minDistance = 99999;
	float distance = 99999;
	unsigned int nearestPlayer = 0;
	for (unsigned int i = 0; i < Player::player.size(); i++)
	{
		distance = Collision::distance(Player::player[i]->getPosition(), sprite.getPosition());
		if (distance < minDistance) minDistance = distance;
	}

	for (unsigned int i = 0; i < Player::player.size(); i++)
	{
		distance = Collision::distance(Player::player[i]->getPosition(), sprite.getPosition());
		if (minDistance == distance) nearestPlayer = i;
	}

	sf::Vector2f v = sprite.getPosition();
	float y = v.y;
	float x = v.x;

	if (Player::player.size() != 0)
	{
		if (Player::player[nearestPlayer]->getPositionY() - y < -5) goUp = true;
		if (Player::player[nearestPlayer]->getPositionY() - y > 5) goDown = true;

		if (abs(Player::player[nearestPlayer]->getPositionX() - x) > 10)
		{
			if (Player::player[nearestPlayer]->getPositionX() > x) goRight = true;
			else goLeft = true;
		}
		else speed.x = 0;
	}
}

void BasicEnemy::AIattack1(int deltaTime)
{
	deltaTime2 += deltaTime;
	if (deltaTime2 >= attackSpeed)
	{
		for (unsigned int i = 0; i < Player::player.size(); i++)
		{
			if (boolCollision(Player::player[i]->getPosition(), Player::player[i]->getSize()))
			{
				Player::player[i]->hited(dmg);
				deltaTime2 = 0;
			}
		}
	}
}

void BasicEnemy::AIattack2(int deltaTime, sf::Vector2f attackPosition, sf::Vector2f attackSize)
{
	deltaTime2 += deltaTime;
	if (deltaTime2 >= attackSpeed)
	{
		sf::Vector2f v = sprite.getPosition();

		if (left) attackPosition.x = -attackPosition.x;

		Collision collisio(sf::Vector2f(v.x + attackPosition.x, v.y + attackPosition.y), attackSize);

		for (unsigned int i = 0; i < Player::player.size(); i++)
		{
			if (collisio.boolCheckCollision(Player::player[i]->getPosition(), Player::player[i]->getSize()))
			{
				Player::player[i]->hited(dmg);
				deltaTime2 = 0;
			}
		}
	}
}

bool BasicEnemy::checkAttack2(sf::Vector2f attackPosition, sf::Vector2f attackSize)
{
	sf::Vector2f v = sprite.getPosition();

	attackSize.x *= 10;

	if (left) attackPosition.x = -attackPosition.x;

	Collision collisio(sf::Vector2f(v.x + attackPosition.x, v.y + attackPosition.y), attackSize);	

	for (unsigned int i = 0; i < Player::player.size(); i++)
	{
		if (collisio.boolCheckCollision(Player::player[i]->getPosition(), Player::player[i]->getSize()))
		{
			return true;
		}
	}
	return false;
}

void BasicEnemy::move(int deltaTime)
{
	if (inWater)
	{
		if (goUp)  speed.y = -speeding.x / 2;
		if (goDown)  speed.y = speeding.x / 2;
		if (goLeft) speed.x = -speeding.x / 1.4;
		if (goRight) speed.x = speeding.x / 1.4;
		speed.x *= 0.9f;
	}
	else
	{
		if (goUp) jump();
		if (goDown)  speed.y = -speeding.x;
		if (goLeft) speed.x = -speeding.x;
		if (goRight) speed.x = speeding.x;
	}

	sprite.move(speed.x*deltaTime, speed.y*deltaTime);

	goLeft = false;
	goRight = false;
	goUp = false;
	goDown = false;
}

void BasicEnemy::checkCollision(int deltaTime)
{
	inWater = false;

	for (int j = Block::block.size() - 1; j >= 0; j--)
	{
		if (Block::block[j]->haveHitbox)
		{
			if (Block::block[j]->water)
			{
				static sf::Vector2f v;
				v = Block::block[j]->getSize();
				v.x -= 2;
				v.y -= 2;
				if (boolCollision(Block::block[j]->getPosition(), v))
				{
					inWater = true;
				}
			}
			else
			{
				collision(Block::block[j]->getPosition(), Block::block[j]->getSize());
			}
		}
	}

	for (int j = Block::dmgBlock.size() - 1; j >= 0; j--)
	{
		if (Block::dmgBlock[j]->water)
		{
			static sf::Vector2f v;
			v = Block::dmgBlock[j]->getSize();
			v.x -= 2;
			v.y -= 2;

			if (boolCollision(Block::dmgBlock[j]->getPosition(), v))
			{
				if (Block::dmgBlock[j]->attack(deltaTime)) hited(Block::dmgBlock[j]->dmg);
				inWater = true;
			}
		}
		else
		{
			if (collision(Block::dmgBlock[j]->getPosition(), Block::dmgBlock[j]->getSize())) //blok atakuje gracza, jesli moze
			{
				if (Block::dmgBlock[j]->attack(deltaTime)) hited(Block::dmgBlock[j]->dmg);
			}
		}
	}

	if (hitWall) sprite.move(0, 0.2);	//jest po to, ¿eby nie bugowa³ siê przy œcianach
}