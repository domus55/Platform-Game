#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Collision.h"
#include "Player.h"

class Bonus
{
public:
	Bonus(float x, float y, std::string name);
	static void makeBonus(float x, float y, std::string name);
	static void renderAll(sf::RenderWindow *window);
	static void updateAll();
	void update(int bonusNumber);
	void render(sf::RenderWindow *window);
	sf::Vector2f getPosition();
	sf::Vector2f getSize();

	static std::vector < std::shared_ptr <Bonus> > bonus;
	std::string name;
private:
	bool boolCollision(sf::Vector2f position2, sf::Vector2f size2);
	sf::Sprite sprite;
	sf::Texture teksture;
	sf::Vector2u size;
};

