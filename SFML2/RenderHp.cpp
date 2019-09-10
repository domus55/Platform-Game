#include "RenderHp.h"
#include "Player.h"


RenderHp::RenderHp()
{
	texture1.loadFromFile("images/HUD/hp1.png");
	texture2.loadFromFile("images/HUD/hp2.png");
	hp1.setTexture(texture1);
	hp2.setTexture(texture2);
	hp1.setOrigin(52, 11);
	hp2.setOrigin(50, 10);
	//hp1.setPosition(100, 600);
	//hp2.setPosition(100, 600);
}

void RenderHp::render(sf::RenderWindow * window, sf::Sprite sprite, float hp, float maxHp)
{
	//std::cout << "a";

	sf::Vector2f position = sprite.getPosition();
	sf::Vector2u size = sprite.getTexture()->getSize();
	sf::Vector2f scale = sprite.getScale();

	hp1.setPosition(position.x, 15 + position.y + size.y * scale.y/2);
	hp2.setPosition(position.x, 15 + position.y + size.y * scale.y/2);

	float skala = 0.7;

	hp1.setScale(size.x * scale.x * 0.01 , size.y * scale.y * 0.004);
	hp2.setScale(hp / maxHp * size.x * scale.x * 0.01, size.y * scale.y * 0.004);
	window->draw(hp1);
	window->draw(hp2);
}

void RenderHp::render(sf::RenderWindow *window, sf::Vector2f view, int number, float hp, float maxHp)
{
	if (number == 0)
	{

		hp1.setPosition(view.x - 525, view.y - 400);
		hp2.setPosition(view.x - 525, view.y - 400);

		hp1.setScale(5, 2.5);
		hp2.setScale(hp / maxHp * 5, 2.5);
		window->draw(hp1);
		window->draw(hp2);
	}

	if (number == 1)
	{
		hp1.setPosition(view.x + 525, view.y - 400);
		hp2.setPosition(view.x + 525, view.y - 400);

		hp1.setScale(5, 2.5);
		hp2.setScale(hp / maxHp * 5, 2.5);
		window->draw(hp1);
		window->draw(hp2);
	}
}
