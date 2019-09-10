#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Collision.h"
#include "Player.h"

class Shoot
{
public:
	Shoot(float x, float y, bool right, sf::Vector2f speed, float dmg);
	static void addShoot(float x, float y, bool right, sf::Vector2f speed, float dmg);
	static void renderAll(sf::RenderWindow *window);
	static void updateAll(int deltaTime);

	static void setBorderMap(sf::Vector2f RightDownCorner);

	void render(sf::RenderWindow *window);
	void update(int deltaTime, int shootNumber);

	void outsideMap(int shootNumber);	//sprawdza czy strza³ nie jest za daleko, jeœli tak, to go usuwa
	void collision(int shootNumber);
	bool boolCollision(sf::Vector2f position2, sf::Vector2f size2);
	bool ColisionLeft(sf::Vector2f position2, sf::Vector2f size2);

	static std::vector < std::shared_ptr <Shoot> > shoot;

	static bool deleteShoot;	//jeœli tak, to usuwa strza³y poza map¹

private:
	Gravity gravity;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2u size;
	sf::Vector2f speed;
	static int borderUp;
	static int borderBottom;
	static int borderLeft;
	static int borderRight;
	bool right;
	bool inWater;
	float dmg;
};

