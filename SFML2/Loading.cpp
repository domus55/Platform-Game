#include "Loading.h"

int Loading::animation = -1;
sf::Sprite Loading::sprite;
sf::Texture Loading::texture;
clock_t Loading::time;

void Loading::render(sf::RenderWindow *window)
{
	sprite.setPosition(GameInfo::getViewCenter());

	static bool firstTime = true;
	if (firstTime)
	{
		texture.loadFromFile("images/load/1.png");
		sprite.setTexture(texture);

		
		animation = Animation::addAnimation(100000);

		Animation::animation[animation]->addImage("images/load/1.png");
		Animation::animation[animation]->addImage("images/load/2.png");
		Animation::animation[animation]->addImage("images/load/3.png");
		Animation::animation[animation]->addImage("images/load/4.png");

		Animation::animation[animation]->blockAmount++;

		firstTime = false;

		sprite.setOrigin(800, 450);
		//sprite.setPosition(800, 450);
		time = clock();
	}
	Animation::animation[animation]->blockAmount = 1;

	if (clock()-time >= 1000)
	{
		Animation::animation[animation]->licznik2++;
		time = clock();
	}
	
	Animation::animation[animation]->render(&sprite, window);
	window->display();
}
