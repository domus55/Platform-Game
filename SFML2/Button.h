#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Collision.h"

class Button
{
public:
	std::string name;
	static std::vector < std::shared_ptr <Button> > button;

	Button(float x, float y, std::string name);
	static void makeButton(int x, int y, std::string name);
	static void renderAll(sf::RenderWindow *window);
	void render(sf::RenderWindow *window);
	bool isClicked(sf::RenderWindow *window, sf::Vector2f view);


private:
	sf::Sprite sprite;
	sf::Texture teksture;
	sf::Vector2u size;
};

