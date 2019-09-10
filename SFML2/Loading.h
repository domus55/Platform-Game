#pragma once

#include "Animation.h"

class Loading
{
public:
	static void render(sf::RenderWindow *window);
	static int animation;
	static sf::Sprite sprite;
	static sf::Texture texture;
	static clock_t time;
};

