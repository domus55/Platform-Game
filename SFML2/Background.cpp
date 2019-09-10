#include "Background.h"

std::vector < std::shared_ptr <Background> > Background::background;


Background::Background()
{
	secondBackground = false;

	height = 800;
	width = 900;
	scaleX = 1;
	scaleY = 1;
	teksture.loadFromFile("images/background/sky.png");
	sprite1.setTexture(teksture);
	sprite2.setTexture(teksture);
	sprite3.setTexture(teksture);
	sprite1.setOrigin(width / 2, height / 2);
	sprite2.setOrigin(width / 2, height / 2);
	sprite3.setOrigin(width / 2, height / 2);
	sprite1.setScale(scaleX, scaleY);
	sprite2.setScale(scaleX, scaleY);
	sprite3.setScale(scaleX, scaleY);

	height2 = 450;
	width2 = 900;
	scaleX2 = 1.9;	//4
	scaleY2 = 1.5;	//1.3
	teksture2.loadFromFile("images/background/mountain.png");
	sprite4.setTexture(teksture2);
	sprite5.setTexture(teksture2);
	sprite6.setTexture(teksture2);
	sprite4.setOrigin(width2 / 2, height2 / 2);
	sprite5.setOrigin(width2 / 2, height2 / 2);
	sprite6.setOrigin(width2 / 2, height2 / 2);
	sprite4.setScale(scaleX2, scaleY2);
	sprite5.setScale(scaleX2, scaleY2);
	sprite6.setScale(scaleX2, scaleY2);
}

void Background::addBackground()
{
	Background::background.push_back(std::make_shared <Background>());
}

void Background::renderAll(sf::RenderWindow * window, sf::Vector2f view)
{
	renderFirst(window, view);
	renderSecond(window, view);
}

void Background::renderFirst(sf::RenderWindow * window, sf::Vector2f view)
{
	if (!secondBackground)
	{
		static bool firstTime = true;
		if (firstTime) { center1 = view;  firstTime = false; }

		static float distance = 4;

		sf::Vector2f vector2 = sprite2.getPosition();
		if (!(view.x >= (vector2.x - scaleX * width / 2) && view.x <= (vector2.x + scaleX * width / 2)))
		{
			sf::Vector2f vector3 = sprite3.getPosition();
			if (view.x >= (vector3.x - scaleX * width / 2) && view.x <= (vector3.x + scaleX * width / 2))
			{
				center1.x -= width * scaleX * distance;
			}
			else
			{
				sf::Vector2f vector1 = sprite1.getPosition();
				if (view.x >= (vector1.x - scaleX * width / 2) && view.x <= (vector1.x + scaleX * width / 2))
				{
					center1.x += width * scaleX * distance;
				}
				else center1.x = view.x * -distance;
			}
		}

		sf::Vector2f chengeView;
		chengeView.x = (view.x - center1.x) / distance;	//2 mean distance, from background
		sprite2.setPosition(chengeView.x, view.y - 100);
		sprite1.setPosition(chengeView.x - width * scaleX, view.y - 100);
		sprite3.setPosition(chengeView.x + width * scaleX, view.y - 100);
		window->draw(sprite1);
		window->draw(sprite2);
		window->draw(sprite3);
	}
}

void Background::renderSecond(sf::RenderWindow * window, sf::Vector2f view)
{
	if (LevelMenager::level == 6 && secondBackground == false)
	{
		teksture2.loadFromFile("images/background/mountain2.png");
		sprite4.setTexture(teksture2);
		sprite5.setTexture(teksture2);
		sprite6.setTexture(teksture2);
		scaleY2 = 2;
		sprite4.setScale(scaleX2, scaleY2);
		sprite5.setScale(scaleX2, scaleY2);
		sprite6.setScale(scaleX2, scaleY2);
		secondBackground = true;
	}

	static bool firstTime = true;
	if (firstTime) { center2 = view;  firstTime = false; }

	static float distance = 3.5;

	sf::Vector2f vector2 = sprite5.getPosition();
	if (!(view.x >= (vector2.x - scaleX2 * width2 / 2) && view.x <= (vector2.x + scaleX2 * width2 / 2)))
	{
		sf::Vector2f vector3 = sprite6.getPosition();
		if (view.x >= (vector3.x - scaleX2 * width2 / 2) && view.x <= (vector3.x + scaleX2 * width2 / 2))
		{
			center2.x -= width2 * scaleX2 * distance;
		}
		else
		{
			sf::Vector2f vector1 = sprite4.getPosition();
			if (view.x >= (vector1.x - scaleX2 * width2 / 2) && view.x <= (vector1.x + scaleX2 * width2 / 2))
			{
				center2.x += width2 * scaleX2 * distance;
			}
			else center2.x = view.x * -distance;
		}
	}

	sf::Vector2f chengeView;
	chengeView.x = (view.x - center2.x) / distance;	//2 mean distance, from background
	if (!secondBackground)
	{
		sprite5.setPosition(chengeView.x, view.y + 160);
		sprite4.setPosition(chengeView.x - width2 * scaleX2, view.y + 160);
		sprite6.setPosition(chengeView.x + width2 * scaleX2, view.y + 160);
	}
	else
	{
		sprite5.setPosition(chengeView.x, view.y);
		sprite4.setPosition(chengeView.x - width2 * scaleX2, view.y);
		sprite6.setPosition(chengeView.x + width2 * scaleX2, view.y);
	}

	window->draw(sprite4);
	window->draw(sprite5);
	window->draw(sprite6);
}
