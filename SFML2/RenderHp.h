#pragma once

#include <SFML/Graphics.hpp>

class RenderHp
{
public:
	RenderHp();
	void render(sf::RenderWindow *window,  sf::Sprite sprite, float  hp, float maxHp);
	void render(sf::RenderWindow *window, sf::Vector2f view, int number,float hp, float maxHp);

private:
	sf::Sprite hp1;
	sf::Sprite hp2;
	sf::Texture texture1;
	sf::Texture texture2;
};

