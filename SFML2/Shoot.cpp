#include "Shoot.h"

std::vector < std::shared_ptr <Shoot> > Shoot::shoot;
bool Shoot::deleteShoot = true;
int Shoot::borderUp = -1000;
int Shoot::borderBottom = 1000;
int Shoot::borderLeft = -1000;
int Shoot::borderRight = 1000;

Shoot::Shoot(float x, float y, bool right, sf::Vector2f speed, float dmg)
{
	this->right = right;
	this->dmg = dmg;

	this->speed.x = 0.5;
	this->speed.y = 0;
	this->speed = speed;
	gravity.gravityForce = 0.01;

	if (LevelMenager::level > 5 && LevelMenager::level <= 10)  texture.loadFromFile("images/shoot/shoot2.png");
	else texture.loadFromFile("images/shoot/shoot.png");
	sprite.setTexture(texture);
	size = sprite.getTexture()->getSize();
	sprite.setOrigin(static_cast<float>(size.x / 2), static_cast<float>(size.y / 2));
	sprite.setPosition(x, y);

	inWater = false;
}

void Shoot::addShoot(float x, float y, bool right, sf::Vector2f speed, float dmg)
{
	Shoot::shoot.push_back(std::make_shared <Shoot>(x, y, right, speed, dmg));
}

void Shoot::renderAll(sf::RenderWindow *window)
{
	for (unsigned int i = 0; i < shoot.size(); i++)
	{
		shoot[i]->render(window);
	}
}

void Shoot::updateAll(int deltaTime)
{
	for (int i = shoot.size() - 1; i >= 0; i--)
	{
		shoot[i]->update(deltaTime, i);
	}
}

void Shoot::setBorderMap(sf::Vector2f RightDownCorner)
{
	borderUp = -2000;
	borderLeft = -2000;
	borderBottom = RightDownCorner.y;
	borderRight = RightDownCorner.x;
}

void Shoot::render(sf::RenderWindow *window)
{
	window->draw(sprite);
}

void Shoot::update(int deltaTime, int shootNumber)
{
	inWater = false;
	outsideMap(shootNumber);
	collision(shootNumber);
	if (inWater)
	{
		gravity.gravity(speed, deltaTime);

		if (right) sprite.move(speed.x * deltaTime, 0);
		else       sprite.move(-1 * (speed.x * deltaTime), 0);
		sprite.move(0, speed.y*deltaTime);

		float z = 1;
		z = z * deltaTime / 1600;
		speed.x *= 1.0 - z;
	}
	else
	{
		if (right) sprite.move(speed.x * deltaTime, 0);
		else       sprite.move(-1 * (speed.x * deltaTime), 0);
		sprite.move(0, speed.y*deltaTime);
	}
}

void Shoot::outsideMap(int shootNumber)
{
	if (deleteShoot)
	{
		static sf::Vector2f v;
		v = sprite.getPosition();

		if (v.x < borderLeft || v.x > borderRight) shoot.erase(shoot.begin() + shootNumber);
		else
		{
			if (v.y > borderBottom || v.y < borderUp) shoot.erase(shoot.begin() + shootNumber);
		}
	}

}

bool Shoot::boolCollision(sf::Vector2f position2, sf::Vector2f size2)
{
	sf::Vector2f position;
	sf::Vector2f size;

	position = sprite.getPosition();
	size.x = sprite.getScale().x * this->size.x;
	size.y = sprite.getScale().y * this->size.y;

	Collision collision(position, size);

	return collision.boolCheckCollision(position2, size2);
}

bool Shoot::ColisionLeft(sf::Vector2f position2, sf::Vector2f size2)
{
	sf::Vector2f position;
	sf::Vector2f size;

	position = sprite.getPosition();
	size.x = sprite.getScale().x * this->size.x;
	size.y = sprite.getScale().y * this->size.y;

	Collision collision(position, size);
	sf::Vector2f changePosition = collision.checkCollision(position2, size2);

	if (changePosition.x > 0) return false;
	return true;
}

void Shoot::collision(int shootNumber)
{
	sf::Vector2f position = sprite.getPosition();

	if (Menu::friendlyFire)
	{
		for (int i = Player::player.size() - 1; i >= 0; i--)
		{
			static sf::Vector2f v;
			v = Player::player[i]->getSize();
			v.x -= 10;
			v.y -= 10;
			if (boolCollision(Player::player[i]->getPosition(), v))
			{
				Player::player[i]->hited();
				shoot.erase(shoot.begin() + shootNumber);
				goto end;
			}
		}
	}

	for (int i = Block::block.size() - 1; i >= 0; i--)
	{
		if (Block::block[i]->haveHitbox)
		{
			static sf::Vector2f v;
			v = Block::block[i]->getSize();
			if (boolCollision(Block::block[i]->getPosition(), v))
			{
				if (Block::block[i]->water) inWater = true;
				else
				{
					bool left = ColisionLeft(Block::block[i]->getPosition(), v);
					Block::block[i]->hited(left, position.y);
					shoot.erase(shoot.begin() + shootNumber);
					goto end;
				}
			}
		}
	}

	for (int i = Block::dmgBlock.size() - 1; i >= 0; i--)
	{
		if (Block::block[i]->haveHitbox)
		{
			static sf::Vector2f v;
			v = Block::dmgBlock[i]->getSize();
			if (boolCollision(Block::dmgBlock[i]->getPosition(), v))
			{
				if (Block::dmgBlock[i]->water) inWater = true;
				else
				{
					bool left = ColisionLeft(Block::dmgBlock[i]->getPosition(), v);
					Block::dmgBlock[i]->hited(left, position.y);
					shoot.erase(shoot.begin() + shootNumber);
					goto end;
				}
			}
		}
	}

	for (int i = BasicEnemy::enemy.size() - 1; i >= 0; i--)
	{
		static sf::Vector2f v;
		v = BasicEnemy::enemy[i]->getSize();
		v.x -= 5;
		v.y -= 5;
		if (boolCollision(BasicEnemy::enemy[i]->getPosition(), v))
		{
			BasicEnemy::enemy[i]->hited(dmg);
			shoot.erase(shoot.begin() + shootNumber);
			goto end;
		}
	}


end:;
}
