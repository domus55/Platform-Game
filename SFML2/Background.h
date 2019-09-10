#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"

class Background
{
public:
	Background();
	static void addBackground();
	void renderAll(sf::RenderWindow * window, sf::Vector2f view);
	void renderFirst(sf::RenderWindow * window, sf::Vector2f view);
	void renderSecond(sf::RenderWindow * window, sf::Vector2f view);


	static std::vector < std::shared_ptr <Background> > background;
private:
	sf::Sprite sprite1;
	sf::Sprite sprite2;
	sf::Sprite sprite3;
	sf::Texture teksture;

	int height;
	int width;
	float scaleX;
	float scaleY;

	sf::Sprite sprite4;
	sf::Sprite sprite5;
	sf::Sprite sprite6;
	sf::Texture teksture2;

	int height2;
	int width2;
	float scaleX2;
	float scaleY2;

	sf::Vector2f center1;
	sf::Vector2f center2;

	bool secondBackground;
};

