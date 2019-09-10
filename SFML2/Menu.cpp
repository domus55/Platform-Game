#include "Menu.h"

std::vector < std::shared_ptr <Menu> > Menu::menu;

int Menu::numberOfPlayers = 1;
bool Menu::movingCamera = true;
bool Menu::friendlyFire = false;

Menu::Menu()
{
	//inMenu = false;
	inOptions = false;
	firstTimeInMenu = true;
	firstTimeInOptions = true;
	teksture.loadFromFile("images/menu/menu.png");
	sprite.setTexture(teksture);
	sprite.setOrigin(35, 30);
	sprite.setScale(10, 10);

	loadFromFile();
}

void Menu::makeAll(sf::RenderWindow * window, sf::Vector2f view)
{
	checkInMenu();
	static bool relase = true;

	if (!GameInfo::inMenu && Button::button.size() != 0) { Button::button.clear(); firstTimeInMenu = true; }
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		for (int i = Button::button.size() - 1; i >= 0; i--)
		{
			if (Button::button[i]->isClicked(window, view) && relase )
			{
				if (Button::button[i]->name == "resume" ) GameInfo::inMenu = false;
				if (Button::button[i]->name == "options") inOptions = true;
				if (Button::button[i]->name == "players1") { numberOfPlayers = 2; firstTimeInOptions = true; saveToFile(); }
				if (Button::button[i]->name == "players2") { numberOfPlayers = 1; firstTimeInOptions = true;  saveToFile(); }
				if (Button::button[i]->name == "movingCameraTrue") { movingCamera = false; firstTimeInOptions = true; saveToFile(); }
				if (Button::button[i]->name == "movingCameraFalse") { movingCamera = true; firstTimeInOptions = true; saveToFile(); }
				if (Button::button[i]->name == "restart") 
				{ 
					LevelMenager::restartLevel(window); GameInfo::inMenu = false;
					for (unsigned int i = 0; i < Player::player.size(); i++)
					{
						Player::player[i]->hp = Player::player[i]->maxHp;
					}
				}
				relase = false;
			}
		}
	}
	else relase = true;
}

void Menu::checkInMenu()
{
	static bool relase = true;

	//std::cout << Button::button.size() << std::endl;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && relase)
	{
		if (inOptions) inOptions = false;
		else GameInfo::inMenu = !GameInfo::inMenu;
		relase = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) == false) relase = true;
}

void Menu::renderMenu(sf::RenderWindow *window, sf::Vector2f view)
{
	if (GameInfo::inMenu && inOptions == false)
	{
		if (firstTimeInMenu)
		{
			firstTimeInOptions = true;
			Button::button.clear();
			
			Button::makeButton(view.x, view.y - 160, "resume");
			Button::makeButton(view.x, view.y      , "restart");
			Button::makeButton(view.x, view.y + 160, "options");
			firstTimeInMenu = false;
		}
		sprite.setPosition(view);
		window->draw(sprite);
		Button::renderAll(window);
	}
	if (inOptions)
	{
		if (firstTimeInOptions)
		{
			firstTimeInMenu = true;
			Button::button.clear();

			if (numberOfPlayers == 1) Button::makeButton(view.x, view.y - 160, "players1");
			if (numberOfPlayers == 2) Button::makeButton(view.x, view.y - 160, "players2");
			if (movingCamera == true) Button::makeButton(view.x, view.y, "movingCameraTrue");
			if (movingCamera == false) Button::makeButton(view.x, view.y, "movingCameraFalse");
			
			firstTimeInOptions = false;
		}
		sprite.setPosition(view);
		window->draw(sprite);
		Button::renderAll(window);
	}

}

void Menu::saveToFile()
{
	std::fstream plik;
	plik.open("options.txt", std::ios::out);

	plik << numberOfPlayers <<" "<< movingCamera;

	plik.close();

	
}

void Menu::loadFromFile()
{
	std::fstream plik;
	plik.open("options.txt", std::ios::in);

	plik >> numberOfPlayers >> movingCamera;

	plik.close();
}
