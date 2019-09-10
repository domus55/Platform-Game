#include "MenuMenager.h"

bool MenuMenager::inMainMenu = true;

void MenuMenager::renderAll(sf::RenderWindow * window)
{
	if(inMainMenu) MainMenu::mainMenu[0]->renderMenu(window, GameInfo::getViewCenter());
	else  Menu::menu[0]->renderMenu(window, GameInfo::getViewCenter());
}

void MenuMenager::update(sf::RenderWindow * window)
{
	if (inMainMenu)MainMenu::mainMenu[0]->makeAll(window, GameInfo::getViewCenter());
	else Menu::menu[0]->makeAll(window, GameInfo::getViewCenter());
}

void MenuMenager::createMenu()
{
	Menu::menu.push_back(std::make_shared <Menu>());
	MainMenu::mainMenu.push_back(std::make_shared <MainMenu>());
}
