#include <iostream>
#include "Block.h"
#include "Player.h"

std::vector < std::shared_ptr <Block> > Block::block;
std::vector < std::shared_ptr <Block> > Block::dmgBlock;
std::vector < std::shared_ptr <Block> > Block::background;
int Block::lavaAnimation = -1;
int Block::waterAnimation = -1;
int Block::flowerAnimation = -1;
int Block::flower2Animation = -1;
bool Block::showHitbox = false;
sf::SoundBuffer Block::buffer;
sf::Sound Block::sound;

Block::Block(int x, int y, std::string name, bool haveHitbox, int id, bool background)
{
	this->id = id;
	this->haveHitbox = haveHitbox;
	isVisible = true;
	dmg = 0;
	canAttack = false;
	deltaTime2 = 0;
	attackSpeed = 0;
	size.x = 10;
	size.y = 10;
	sprite.setScale(5, 5);
	sprite.setOrigin(static_cast<float>(size.x / 2), static_cast<float>(size.y / 2));
	sprite.setPosition(x, y);
	speed.x = 0;
	speed.y = 0;
	startPosition.x = 0;
	startPosition.y = 0;
	right = true;
	isMoving = false;

	water = false;

	static bool firsttTime = true;
	if (firsttTime)
	{
		buffer.loadFromFile("music/hitBlock.wav");
		sound.setBuffer(buffer);
		firsttTime = false;
	}
	
	if (name == "grass") { teksture.loadFromFile("images/block/grass1.jpg"); this->name = "grass1"; isAnimated = false; }
	if (name == "grass2") { teksture.loadFromFile("images/block/grass2.jpg"); this->name = "grass2"; isAnimated = false; }
	if (name == "dirt") {teksture.loadFromFile("images/block/dirt1.jpg"); this->name = "dirt1"; isAnimated = false;}
	if (name == "dirt2") { teksture.loadFromFile("images/block/dirt2.jpg"); this->name = "dirt2"; isAnimated = false; }
	if (name == "sand") {teksture.loadFromFile("images/block/sand1.jpg"); this->name = "sand1"; isAnimated = false;}
	if (name == "sand2") { teksture.loadFromFile("images/block/sand2.jpg"); this->name = "sand2"; isAnimated = false; }
	if (name == "glass") { teksture.loadFromFile("images/block/glass.png"); this->name = "glass"; isAnimated = false;}
	if (name == "stone") { teksture.loadFromFile("images/block/stone1.png"); this->name = "stone"; isAnimated = false;}
	if (name == "cactus") { teksture.loadFromFile("images/block/cactus1.png"); this->name = "cactus1"; isAnimated = false; canAttack = true; attackSpeed = 250; dmg = 0.5; }
	if (name == "cactus2") { teksture.loadFromFile("images/block/cactus2.png"); this->name = "cactus2"; isAnimated = false; canAttack = true; attackSpeed = 250; dmg = 1; }
	if (name == "wood1") { teksture.loadFromFile("images/block/wood1.png"); this->name = "wood1"; isAnimated = false; }
	if (name == "wood2") { teksture.loadFromFile("images/block/wood2.png"); this->name = "wood2"; isAnimated = false; }
	if (name == "leaf1") { teksture.loadFromFile("images/block/leaf1.png"); this->name = "leaf1"; isAnimated = false; }
	if (name == "leaf2") { teksture.loadFromFile("images/block/leaf2.png"); this->name = "leaf2"; isAnimated = false; }
	if (name == "finish") { teksture.loadFromFile("images/block/finish.png"); this->name = "finish"; isAnimated = false; water = true; }
	if (name == "ladder") { teksture.loadFromFile("images/block/ladder.png"); this->name = "ladder"; isAnimated = false; water = true; }
	if (name == "water") 
	{
		water = true;
		this->name = "water";
		static bool firstTimeWater = true;
		if (firstTimeWater)
		{
			waterAnimation = Animation::addAnimation(10);

			Animation::animation[waterAnimation]->addImage("images/block/water/water1.png");
			Animation::animation[waterAnimation]->addImage("images/block/water/water2.png");
			Animation::animation[waterAnimation]->addImage("images/block/water/water3.png");
			Animation::animation[waterAnimation]->addImage("images/block/water/water2.png");

			firstTimeWater = false;
		}
		teksture.loadFromFile("images/block/water/water1.png");
		isAnimated = true;
		Animation::animation[waterAnimation]->blockAmount++;
	}
	if (name == "lava") 
	{
		canAttack = true;
		attackSpeed = 25;
		dmg = 0.1;
		water = true;
		this->name = "lava";
		static bool firstTimeLava = true;
		if (firstTimeLava)
		{
			lavaAnimation = Animation::addAnimation(20);

			Animation::animation[lavaAnimation]->addImage("images/block/lava/lava1.png");
			Animation::animation[lavaAnimation]->addImage("images/block/lava/lava2.png");
			Animation::animation[lavaAnimation]->addImage("images/block/lava/lava3.png");
			Animation::animation[lavaAnimation]->addImage("images/block/lava/lava4.png");
			Animation::animation[lavaAnimation]->addImage("images/block/lava/lava5.png");

			firstTimeLava = false;
		}
		teksture.loadFromFile("images/block/lava/lava1.png");	
		isAnimated = true;
		Animation::animation[lavaAnimation]->blockAmount++;
	}
	if (name == "flower")
	{
		this->haveHitbox = false;
		this->name = "flower";
		static bool firstTimeFlower = true;
		if (firstTimeFlower)
		{
			flowerAnimation = Animation::addAnimation(30);

			Animation::animation[flowerAnimation]->addImage("images/block/flower/flower1.png");
			Animation::animation[flowerAnimation]->addImage("images/block/flower/flower2.png");
			Animation::animation[flowerAnimation]->addImage("images/block/flower/flower3.png");
			Animation::animation[flowerAnimation]->addImage("images/block/flower/flower2.png");

			firstTimeFlower = false;
		}
		teksture.loadFromFile("images/block/flower/flower1.png");
		isAnimated = true;
		Animation::animation[flowerAnimation]->blockAmount++;
	}
	if (name == "flower2")
	{
		this->haveHitbox = false;
		this->name = "flower";
		static bool firstTimeFlower = true;
		if (firstTimeFlower)
		{
			flower2Animation = Animation::addAnimation(30);

			Animation::animation[flower2Animation]->addImage("images/block/flower2/flower1.png");	//zmieniæ
			Animation::animation[flower2Animation]->addImage("images/block/flower2/flower2.png");
			Animation::animation[flower2Animation]->addImage("images/block/flower2/flower3.png");
			Animation::animation[flower2Animation]->addImage("images/block/flower2/flower2.png");

			firstTimeFlower = false;
		}
		teksture.loadFromFile("images/block/flower2/flower1.png");	//zmieniæ
		isAnimated = true;
		Animation::animation[flower2Animation]->blockAmount++;
	}
	
	sprite.setTexture(teksture);

	if(background)
	{
		sprite.setColor(sf::Color(150, 150, 150));
	}

	if(showHitbox && !haveHitbox) sprite.setColor(sf::Color(100, 100, 100));
}

void Block::renderBlock(sf::RenderWindow *window)
{
	for (unsigned int i = 0; i < block.size(); i++)
	{
		if(block[i]->isVisible) block[i]->render(window);
	}

	for (unsigned int i = 0; i < dmgBlock.size(); i++)
	{
		if(dmgBlock[i]->isVisible) dmgBlock[i]->render(window);
	}
}

void Block::renderBackground(sf::RenderWindow * window)
{
	for (unsigned int i = 0; i < background.size(); i++)
	{
		if(background[i]->isVisible)  background[i]->render(window);
	}
}

void Block::render(sf::RenderWindow *window)
{
	if (isAnimated)
	{
		if(name == "lava") Animation::animation[lavaAnimation]->render(&sprite, window);
		if (name == "water") Animation::animation[waterAnimation]->render(&sprite, window);
		if (name == "flower") Animation::animation[flowerAnimation]->render(&sprite, window);
	}
	else window->draw(sprite);
}

void Block::updateAll(int deltaTime)
{
	for (int i = Block::block.size() - 1; i >= 0; i--)
	{
		Block::block[i]->update(deltaTime);
	}

	for (int i = Block::dmgBlock.size() - 1; i >= 0; i--)
	{
		Block::dmgBlock[i]->update(deltaTime);
	}
}

void Block::update(int deltaTime)
{
	if (canAttack) deltaTime2 += deltaTime;
	checkMove();
	sprite.move(speed.x * GameInfo::getDeltaTime(), speed.y * GameInfo::getDeltaTime());
}

void Block::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
}

void Block::makeBlock(float x, float y, std::string name, bool haveHitbox, int id)
{
	if (name == "lava" || name == "cactus" || name == "cactus2")
	{
		Block::dmgBlock.push_back(std::make_shared <Block>(x*50 + 25, y* 50 +25, name, haveHitbox, id));
	}
	else
	{
		Block::block.push_back(std::make_shared <Block>(x * 50 + 25, y * 50 + 25, name, haveHitbox, id));
	}
}

void Block::makeBlockBackground(float x, float y, std::string name)
{
	Block::background.push_back(std::make_shared <Block>(x * 50 + 25, y * 50 + 25, name, false, -1, true));
}

sf::Vector2f Block::getPosition()
{
	sf::Vector2f position = sprite.getPosition();
	return position;
}

sf::Vector2f Block::getSize()
{
	sf::Vector2f size;
	size.x = sprite.getScale().x * this->size.x;
	size.y = sprite.getScale().y * this->size.y;

	return size;
}

bool Block::attack(int deltaTime)
{
	if (deltaTime2 >= attackSpeed)
	{
		deltaTime2 = 0;
		return true;
	}
	return false;
}

void Block::moveBlock(sf::Vector2f distance)
{
	sprite.move(distance);
}

void Block::hited(bool left, float height)
{
	
	sf::Vector2f v = sprite.getPosition();
	Splinter::addSplinter(v.x, height, name, 10, left);
	
	Sound::setVolume(sound, sprite.getPosition());
	sound.play();

	
}

void Block::setMove(sf::Vector2f speed, sf::Vector2f distance)
{
	startPosition = sprite.getPosition();
	this->distance.x = distance.x * 50;
	this->distance.y = distance.y * 50;
	this->speed2 = speed;
	isMoving = true;
}

void Block::checkMove()
{
	if (isMoving)
	{
		sf::Vector2f v = sprite.getPosition();

		if (speed2.x >= 0)
		{
			if (speed2.y >= 0)
			{
				if (v.x < startPosition.x || v.y < startPosition.y) right = true;
				if (v.x > startPosition.x + distance.x || v.y > startPosition.y + distance.y) right = false;
			}
			else
			{
				if (v.x < startPosition.x || v.y > startPosition.y) right = true;
				if (v.x > startPosition.x + distance.x || v.y < startPosition.y - distance.y) right = false;
			}
		}
		else
		{
			if (speed2.y >= 0)
			{
				if (v.x > startPosition.x || v.y < startPosition.y) right = true;
				if (v.x < startPosition.x - distance.x || v.y > startPosition.y + distance.y) right = false;
			}
			else
			{
				if (v.x > startPosition.x || v.y > startPosition.y) right = true;
				if (v.x < startPosition.x - distance.x || v.y < startPosition.y - distance.y) right = false;
			}
			
		}

		if (right) speed = speed2;
		else speed = -speed2;
	}
}
