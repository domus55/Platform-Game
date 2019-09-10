#pragma once

#include <SFML/Graphics.hpp>

class Collision
{
public:
	Collision( sf::Vector2f position, sf::Vector2f halfSize );
	sf::Vector2f checkCollision( sf::Vector2f position, sf::Vector2f halfSize );
	bool boolCheckCollision(sf::Vector2f position, sf::Vector2f halfSize);
	static float distance(sf::Vector2f position, sf::Vector2f position2);
	~Collision();
private:
	sf::Vector2f position;
	sf::Vector2f halfSize;
};

// gracz.checkCollision( przeciwnik.poz );