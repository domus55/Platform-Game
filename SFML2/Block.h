#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include "Animation.h"
#include "Splinter.h"
#include "Collision.h"
#include "GameInfo.h"
#include "Sound.h"

class Block
{
public:
	std::string name;
	Block(int x, int y, std::string name, bool haveHitbox, int id, bool background = false);
	static void renderBlock(sf::RenderWindow *window);
	static void renderBackground(sf::RenderWindow *window);
	void render(sf::RenderWindow *window);
	static void updateAll(int deltaTime);
	void update(int deltaTime);
	void setPosition(float x, float y);
	static void makeBlock(float x, float y, std::string name, bool haveHitbox = true, int id = -1);
	static void makeBlockBackground(float x, float y, std::string name);
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	static std::vector < std::shared_ptr <Block> > block;
	static std::vector < std::shared_ptr <Block> > dmgBlock;
	static std::vector < std::shared_ptr <Block> > background;
	bool attack(int deltaTime);
	void moveBlock(sf::Vector2f distance);
	void hited(bool left, float height);
	void setMove(sf::Vector2f speed, sf::Vector2f distance);	//sprawia, ¿e blok bêdzie siê porusza³
	void checkMove();	//sprawdza, czy blok odpowiednio siê porusza

	float dmg;
	bool water;
	bool haveHitbox;
	bool isVisible;
	bool isMoving;
	int id;
	sf::Vector2f speed;
	sf::Vector2f speed2;
private:
	static sf::Sound sound;
	static sf::SoundBuffer buffer;
	sf::Sprite sprite;
	sf::Texture teksture;
	sf::Vector2i size;

	sf::Vector2f startPosition;
	sf::Vector2f distance;
	bool right;

	static bool showHitbox;
	static int lavaAnimation;
	static int waterAnimation;
	static int flowerAnimation;
	static int flower2Animation;
	bool isAnimated;
	bool canAttack;
	int attackSpeed;
	int deltaTime2;
};

