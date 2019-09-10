#include "Player.h"

std::vector < std::shared_ptr <Player> > Player::player;
sf::SoundBuffer Player::bufferHit;
sf::SoundBuffer Player::bufferDead;
sf::SoundBuffer Player::bufferJump;
sf::Sound Player::soundHit;
sf::Sound Player::soundDead;
sf::Sound Player::soundJump;

Player::Player()
{
	size.x = 50;
	size.y = 100;
	maxHp = 10;
	this->hp = maxHp;
	//this->hp = hp;

	sprite.setScale(1, 1);
	sprite.setOrigin( static_cast<float>(size.x/2), static_cast<float>(size.y / 2) );
	sprite.setPosition(0, 650);
	tekstureLeft.loadFromFile("images/player/playerLeft2.png");
	tekstureRight.loadFromFile("images/player/playerRight2.png");
	sprite.setTexture(tekstureRight);

	speed.x = 0.0f;
	speed.y = 0.0f;
	blockSpeed.x = 0;
	blockSpeed.y = 0;

	shootSpeed = 500;
	speeding.x = 0.06f;	//0.045
	speeding.y = 1.0f;
	dmg = 1;

	hitWall = false;
	hitWall2 = false;
	hitFloor = false;
	hitFloor2 = false;
	canJump = false;
	inWater = false;
	shootLeft = false;
	deltaTime2 = 0;
	numer = player.size();

	//aniamcje

	pistolLeft = Animation::addAnimation(40);
	Animation::animation[pistolLeft]->addImage("images/player/pistol/left1.png");
	Animation::animation[pistolLeft]->addImage("images/player/pistol/left2.png");
	Animation::animation[pistolLeft]->blockAmount++;

	pistolRight = Animation::addAnimation(40);
	Animation::animation[pistolRight]->addImage("images/player/pistol/right1.png");
	Animation::animation[pistolRight]->addImage("images/player/pistol/right2.png");
	Animation::animation[pistolRight]->blockAmount++;

	goPistolLeft = Animation::addAnimation(3);
	Animation::animation[goPistolLeft]->addImage("images/player/goPistol/left1.png");
	Animation::animation[goPistolLeft]->addImage("images/player/goPistol/left2.png");
	Animation::animation[goPistolLeft]->addImage("images/player/goPistol/left3.png");
	Animation::animation[goPistolLeft]->addImage("images/player/goPistol/left4.png");
	Animation::animation[goPistolLeft]->blockAmount++;

	goPistolRight = Animation::addAnimation(3);
	Animation::animation[goPistolRight]->addImage("images/player/goPistol/right1.png");
	Animation::animation[goPistolRight]->addImage("images/player/goPistol/right2.png");
	Animation::animation[goPistolRight]->addImage("images/player/goPistol/right3.png");
	Animation::animation[goPistolRight]->addImage("images/player/goPistol/right4.png");
	Animation::animation[goPistolRight]->blockAmount++;


	shotgunLeft = Animation::addAnimation(40);
	Animation::animation[shotgunLeft]->addImage("images/player/shotgun/left1.png");
	Animation::animation[shotgunLeft]->addImage("images/player/shotgun/left2.png");
	Animation::animation[shotgunLeft]->blockAmount++;

	shotgunRight = Animation::addAnimation(40);
	Animation::animation[shotgunRight]->addImage("images/player/shotgun/right1.png");
	Animation::animation[shotgunRight]->addImage("images/player/shotgun/right2.png");
	Animation::animation[shotgunRight]->blockAmount++;

	goShotgunLeft = Animation::addAnimation(3);
	Animation::animation[goShotgunLeft]->addImage("images/player/goShotgun/left1.png");
	Animation::animation[goShotgunLeft]->addImage("images/player/goShotgun/left2.png");
	Animation::animation[goShotgunLeft]->addImage("images/player/goShotgun/left3.png");
	Animation::animation[goShotgunLeft]->addImage("images/player/goShotgun/left4.png");
	Animation::animation[goShotgunLeft]->blockAmount++;

	goShotgunRight = Animation::addAnimation(3);
	Animation::animation[goShotgunRight]->addImage("images/player/goShotgun/right1.png");
	Animation::animation[goShotgunRight]->addImage("images/player/goShotgun/right2.png");
	Animation::animation[goShotgunRight]->addImage("images/player/goShotgun/right3.png");
	Animation::animation[goShotgunRight]->addImage("images/player/goShotgun/right4.png");
	Animation::animation[goShotgunRight]->blockAmount++;


	ak47Left = Animation::addAnimation(40);
	Animation::animation[ak47Left]->addImage("images/player/ak47/left1.png");
	Animation::animation[ak47Left]->addImage("images/player/ak47/left2.png");
	Animation::animation[ak47Left]->blockAmount++;

	ak47Right = Animation::addAnimation(40);
	Animation::animation[ak47Right]->addImage("images/player/ak47/right1.png");
	Animation::animation[ak47Right]->addImage("images/player/ak47/right2.png");
	Animation::animation[ak47Right]->blockAmount++;

	goAk47Left = Animation::addAnimation(3);
	Animation::animation[goAk47Left]->addImage("images/player/goAk47/left1.png");
	Animation::animation[goAk47Left]->addImage("images/player/goAk47/left2.png");
	Animation::animation[goAk47Left]->addImage("images/player/goAk47/left3.png");
	Animation::animation[goAk47Left]->addImage("images/player/goAk47/left4.png");
	Animation::animation[goAk47Left]->blockAmount++;

	goAk47Right = Animation::addAnimation(3);
	Animation::animation[goAk47Right]->addImage("images/player/goAk47/right1.png");
	Animation::animation[goAk47Right]->addImage("images/player/goAk47/right2.png");
	Animation::animation[goAk47Right]->addImage("images/player/goAk47/right3.png");
	Animation::animation[goAk47Right]->addImage("images/player/goAk47/right4.png");
	Animation::animation[goAk47Right]->blockAmount++;


	p90Left = Animation::addAnimation(40);
	Animation::animation[p90Left]->addImage("images/player/p90/left1.png");
	Animation::animation[p90Left]->addImage("images/player/p90/left2.png");
	Animation::animation[p90Left]->blockAmount++;

	p90Right = Animation::addAnimation(40);
	Animation::animation[p90Right]->addImage("images/player/p90/right1.png");
	Animation::animation[p90Right]->addImage("images/player/p90/right2.png");
	Animation::animation[p90Right]->blockAmount++;

	goP90Left = Animation::addAnimation(3);
	Animation::animation[goP90Left]->addImage("images/player/goP90/left1.png");
	Animation::animation[goP90Left]->addImage("images/player/goP90/left2.png");
	Animation::animation[goP90Left]->addImage("images/player/goP90/left3.png");
	Animation::animation[goP90Left]->addImage("images/player/goP90/left4.png");
	Animation::animation[goP90Left]->blockAmount++;

	goP90Right = Animation::addAnimation(3);
	Animation::animation[goP90Right]->addImage("images/player/goP90/right1.png");
	Animation::animation[goP90Right]->addImage("images/player/goP90/right2.png");
	Animation::animation[goP90Right]->addImage("images/player/goP90/right3.png");
	Animation::animation[goP90Right]->addImage("images/player/goP90/right4.png");
	Animation::animation[goP90Right]->blockAmount++;

	// dŸwiêki
	static bool firsttTime = true;
	if (firsttTime)
	{
		bufferHit.loadFromFile("music/hitEnemy.wav");	//dodaæ dobre dŸwiêki
		bufferDead.loadFromFile("music/deadEnemy.wav");
		bufferJump.loadFromFile("music/player/jump.wav");
		soundHit.setBuffer(bufferHit);
		soundDead.setBuffer(bufferDead);
		soundJump.setBuffer(bufferJump);
		firsttTime = false;
	}
}

void Player::renderAll(sf::RenderWindow * window)
{
	for (unsigned int i = 0; i < player.size(); i++)
	{
		player[i]->render(window);
	}
}

void Player::renderAllHp(sf::RenderWindow * window, sf::Vector2f view)
{
	for (unsigned int i = 0; i < player.size(); i++)
	{
		player[i]->renderHp2(window, view);
	}
}

void Player::renderHp2(sf::RenderWindow * window, sf::Vector2f view)
{
	if (numer == 0) renderHp.render(window, view, 0, hp, maxHp);
	if (numer == 1) renderHp.render(window, view, 1, hp, maxHp);
}

void Player::updateAll(sf::RenderWindow *window, int deltaTime)
{
	for (int i = player.size() - 1; i >= 0; i--)
	{
		player[i]->update(window, deltaTime, i);
	}
}

void Player::update(sf::RenderWindow *window, int deltaTime, int playerNumber)
{
	chechHitWall();
	move(deltaTime);
	if (checkCollision(window, deltaTime)) goto end;	//je¿eli restartuje poziom
	weapon.update(deltaTime);
	shoot(deltaTime);
	if (hp > maxHp) hp = maxHp;
	checkDeath(window, playerNumber);	//musi byæ na koñcu, bo usuwa gracza
end:;
}

void Player::render(sf::RenderWindow *window)
{
	if (shootLeft)
	{
		if ((canJump && sf::Keyboard::isKeyPressed(sf::Keyboard::A) && numer == 0) || (canJump && sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && numer == 1))
		{
			if (weapon.name == "pistol") Animation::animation[goPistolLeft]->render(&sprite, window);
			if (weapon.name == "shotgun") Animation::animation[goShotgunLeft]->render(&sprite, window);	//animacje chodzenia
			if (weapon.name == "ak47") Animation::animation[goAk47Left]->render(&sprite, window);
			if (weapon.name == "p90") Animation::animation[goP90Left]->render(&sprite, window);
		}
		else
		{
			if (weapon.name == "pistol") Animation::animation[pistolLeft]->render(&sprite, window);
			if (weapon.name == "shotgun") Animation::animation[shotgunLeft]->render(&sprite, window);
			if (weapon.name == "ak47") Animation::animation[ak47Left]->render(&sprite, window);
			if (weapon.name == "p90") Animation::animation[p90Left]->render(&sprite, window);
		}
		
		
		//if (weapon.name == "shotgun") Animation::animation[shotgunLeft]->render(&sprite, window);	//jak dodam reszte animacji chodzenia, to to usun¹æ
		//if (weapon.name == "ak47") Animation::animation[ak47Left]->render(&sprite, window);
		//if (weapon.name == "p90") Animation::animation[p90Left]->render(&sprite, window);
	}
	else
	{
		if ((canJump && sf::Keyboard::isKeyPressed(sf::Keyboard::D) && numer == 0) || (canJump && sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && numer == 1))
		{
			if (weapon.name == "pistol") Animation::animation[goPistolRight]->render(&sprite, window);
			if (weapon.name == "shotgun") Animation::animation[goShotgunRight]->render(&sprite, window);	//animacje chodzenia
			if (weapon.name == "ak47") Animation::animation[goAk47Right]->render(&sprite, window);
			if (weapon.name == "p90") Animation::animation[goP90Right]->render(&sprite, window);
		}
		else
		{
			if (weapon.name == "pistol") Animation::animation[pistolRight]->render(&sprite, window);
			if (weapon.name == "shotgun") Animation::animation[shotgunRight]->render(&sprite, window);
			if (weapon.name == "ak47") Animation::animation[ak47Right]->render(&sprite, window);
			if (weapon.name == "p90") Animation::animation[p90Right]->render(&sprite, window);
		}
		//if (weapon.name == "shotgun") Animation::animation[shotgunRight]->render(&sprite, window);
		//if (weapon.name == "ak47") Animation::animation[ak47Right]->render(&sprite, window);
		//if (weapon.name == "p90") Animation::animation[p90Right]->render(&sprite, window);
		}
	
}

void Player::move(int deltaTime)
{
	if (inWater) canJump = false;

	if (speed.y != 0) canJump = false;

	if (numer == 0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ) up = true;
		else up = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) left = true;
		else left = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) right = true;
		else right = false;	
	}

	if (numer == 1)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))  up = true;
		else up = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) left = true;
		else left = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) right = true;
		else right = false;
	}

	if (inWater)
	{
		gravity.slowing = 10;
		if (up) { speed.y -= speeding.y/14 * deltaTime / 16; }
		if (left) speed.x -= speeding.x/ 1.4;
		if (right) speed.x += speeding.x/ 1.4;
		speed.x *= 0.9f;
	}
	else
	{
		gravity.slowing = 1;
		if (up && canJump)
		{ 
			speed.y -= speeding.y; canJump = false; 
			Sound::setVolume(soundJump, sprite.getPosition());
			soundJump.setVolume(soundJump.getVolume() / 2);
			soundJump.play();
		}
		if (canJump)
		{
			//if (!left && !right) speed.x *= 0.7;
			if (left) speed.x -= speeding.x;
			if (right) speed.x += speeding.x;
			speed.x *= 0.9f;
		}
		else
		{
			if (left) speed.x -= speeding.x/2;
			if (right) speed.x += speeding.x/2;
			speed.x *= 0.95f;
		}
		
	}
	if (abs(speed.x) < 0.001)speed.x = 0;
	if (abs(speed.y) < 0.0001)speed.y = 0;
	
	gravity.gravity(speed, deltaTime);

	sprite.move((speed.x + blockSpeed.x)*deltaTime, (speed.y + blockSpeed.y)*deltaTime);
}

void Player::shoot(int deltaTime)
{
	//deltaTime2 += deltaTime;
	if (numer == 0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) shootLeft = true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) shootLeft = false;
	}

	if (numer == 1)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) shootLeft = true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) shootLeft = false;
	}

	
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && numer == 0) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && numer == 1)) isShooting = true;
	else isShooting = false;

	//if (isShooting && deltaTime2 >= shootSpeed)
	if (isShooting)
	{
		sf::Vector2f v = sprite.getPosition();

		if (shootLeft) weapon.shoot(v.x - 30, v.y - 16, false, dmg);
		else		   weapon.shoot(v.x + 30, v.y - 16, true, dmg);

		deltaTime2 = 0;
	}
}

void Player::hited(float dmg)
{
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

	sf::Vector2f v = sprite.getPosition();

	if (hp <= 0) Splinter::addSplinter(v.x, v.y, "blood", 50, false);
	else Splinter::addSplinter(v.x, v.y, "blood", 10, false);
}

bool Player::collision(sf::Vector2f position2, sf::Vector2f size2)
{
	sf::Vector2f position;
	sf::Vector2f size;

	position = sprite.getPosition();
	size.x = sprite.getScale().x * this->size.x;
	size.y = sprite.getScale().y * this->size.y;

	Collision collision( position, size );
	sf::Vector2f changePosition = collision.checkCollision(position2, size2);

	if (changePosition.y < 0.0f) canJump = true;

	if (changePosition.x != 0.0f && hitWall2) { hitWall = true; hitWall2 = false; }
	if (changePosition.x != 0.0f) hitWall2 = true;
	if (changePosition.y != 0.0f && hitFloor2) { hitFloor = true; hitFloor2 = false; }
	if (changePosition.y != 0.0f) hitFloor2 = true;

	sprite.move(changePosition);
	

	if (changePosition.x == 0 && changePosition.y == 0 ) return false;
	return true;
}

bool Player::boolCollision(sf::Vector2f position2, sf::Vector2f size2)
{
	sf::Vector2f position;
	sf::Vector2f size;

	position = sprite.getPosition();
	size.x = sprite.getScale().x * this->size.x;
	size.y = sprite.getScale().y * this->size.y;

	Collision collision(position, size);

	return collision.boolCheckCollision(position2, size2);
}

bool Player::checkCollision(sf::RenderWindow *window, int deltaTime)
{
	inWater = false;
	blockSpeed.x = 0;
	blockSpeed.y = 0;

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
					if (Block::block[j]->name == "finish") { LevelMenager::level++;	LevelMenager::restartLevel(window); return true; }
				}
			}
			else
			{
				if (collision(Block::block[j]->getPosition(), Block::block[j]->getSize()))
				{
					if (Block::block[j]->isMoving)
					{
						blockSpeed = Block::block[j]->speed;
					}
				}
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
	if (hitWall) speed.x = 0;
	if (hitFloor) speed.y = 0;

	return false;
}

void Player::checkDeath(sf::RenderWindow *window, int playerNumber)
{
	if (hp <= 0)
	{
		player.erase(player.begin() + playerNumber);
	}
	//if (player.size() == 0) LevelMenager::restartLevel(window);
	if (player.size() == 0)  HUD::deadScreen = true;
}

void Player::teleport(float a, float h)
{
	sprite.setPosition(a * 50 + 25, h * 50 + 25);
}

sf::Vector2f Player::getPosition()
{
	return sprite.getPosition();
}

float Player::getPositionX()
{
	sf::Vector2f vector;
	vector = sprite.getPosition();
	return vector.x;
}

float Player::getPositionY()
{
	sf::Vector2f vector;
	vector = sprite.getPosition();
	return vector.y;
}

sf::Vector2f Player::getSize()
{
	sf::Vector2f size;
	size.x = sprite.getScale().x * this->size.x;
	size.y = sprite.getScale().y * this->size.y;

	return size;
}

void Player::chechHitWall()
{
	check = !check;
	hitWall = false;
	hitFloor = false;
	if (check) { hitWall2 = false; hitFloor2 = false; }
}

