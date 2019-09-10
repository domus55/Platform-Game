#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <ctime>
#include <cstdlib>
#include "GameInfo.h"
#include "Gravity.h"
   

class Splinter
{
public:
	Splinter(float a, float h, std::string name, bool left);
	static void renderAll(sf::RenderWindow *window);
	void render(sf::RenderWindow *window);
	static void updateAll();
	void update();

	static void addSplinter(float a, float h, std::string name, int ammount, bool left);
	static std::vector < std::shared_ptr <Splinter> > splinter;
	
private:
	sf::Sprite sprite;
	sf::Texture teksture;
	sf::Vector2f speed;
	Gravity gravity;
	int timee;
	float rotation;
};

