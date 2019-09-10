#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "MainMenu.h"
#include "Menu.h"
#include "GameInfo.h"

class MenuMenager
{
public:
	static void renderAll(sf::RenderWindow *window);
	static void update(sf::RenderWindow *window);
	static void createMenu();
	static bool inMainMenu;
};

