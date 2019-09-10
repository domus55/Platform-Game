#include "HUD.h"

bool HUD::deadScreen = false;
//sf::Sprite HUD::sprite;
//sf::Texture HUD::texture;

void HUD::renderHp(sf::RenderWindow *window)
{
	BasicEnemy::renderAllHp(window);
	Player::renderAllHp(window, GameInfo::getViewCenter());
	renderDeadScreen(window);
}

void HUD::renderDeadScreen(sf::RenderWindow * window)
{
	static sf::Sprite sprite;
	static sf::Texture texture;
	static bool LoadTexture = true;
	static int deltaTime = 0;
	static bool firstTime = true;
	static sf::Color color(255, 255, 255);
	static float basicColor = 0;


	if (LoadTexture)
	{
		texture.loadFromFile("images/HUD/youDied.png");
		sprite.setTexture(texture);
		sprite.setOrigin(20, 4);
		sprite.setScale(10, 10);

		LoadTexture = false;
	}
	
	if (deadScreen)
	{
		deltaTime += GameInfo::getDeltaTime();

		if (firstTime) 
		{
			deltaTime = 0;
			basicColor = 0;
			firstTime = false;
		}

		basicColor += GameInfo::getDeltaTime() / 8.0;

		color.r = basicColor;
		color.g = basicColor;
		color.b = basicColor;
		sprite.setColor(color);

		sprite.setPosition(GameInfo::getViewCenter());
		window->draw(sprite);

		if (deltaTime >= 2000 || (deltaTime >= 500 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)))
		{
			deadScreen = false;
			LevelMenager::restartLevel(window);
			firstTime = true;
		}
	}
}
