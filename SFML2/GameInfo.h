#pragma once

#include <SFML/Graphics.hpp>

class GameInfo
{
public:

	static int getDeltaTime();
	static void setDeltaTime(int deltaTime);

	static sf::Vector2f getViewCenter();
	static void setViewCenter(sf::Vector2f viewCenter);
	static bool inMenu;
private:
	static int deltaTime;
	static sf::Vector2f viewCenter;
};

