#pragma once

#include <SFML/Graphics.hpp>

class Window
{
public:
	static void createWindow();
	static std::vector <std::shared_ptr <sf::RenderWindow> > window;
};

