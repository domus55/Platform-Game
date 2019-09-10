#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include "MenuMenager.h"
#include "LevelMenager.h"
#include "Player.h"
#include "Button.h"
#include "GameInfo.h"

class MainMenu
{
public:
	MainMenu();
	void makeAll(sf::RenderWindow *window, sf::Vector2f view);
	void checkInMenu();
	void renderMenu(sf::RenderWindow *window, sf::Vector2f view);
	void saveToFile();
	void loadFromFile();

	//bool inMenu;
	static bool movingCamera;
	static int numberOfPlayers;
	static bool friendlyFire;

	static std::vector < std::shared_ptr <MainMenu> > mainMenu;

private:
	sf::Sprite sprite;
	sf::Texture teksture;
	bool firstTimeInMenu;
	bool firstTimeInOptions;
	bool inOptions;
};

