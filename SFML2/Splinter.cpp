#include "Splinter.h"

std::vector < std::shared_ptr <Splinter> > Splinter::splinter;


Splinter::Splinter(float a, float h, std::string name, bool left)
{
	if (name == "blood") teksture.loadFromFile("images/splinter/blood.png"); 
	if (name == "grass1")  teksture.loadFromFile("images/splinter/dirt1.png");
	if (name == "grass2")  teksture.loadFromFile("images/splinter/dirt2.png");
	if (name == "dirt1") teksture.loadFromFile("images/splinter/dirt1.png");
	if (name == "dirt2")  teksture.loadFromFile("images/splinter/dirt2.png");
	if (name == "sand1") teksture.loadFromFile("images/splinter/sand1.png");
	if (name == "sand2")  teksture.loadFromFile("images/splinter/sand2.png");
	if (name == "glass")  teksture.loadFromFile("images/splinter/glass.png");
	if (name == "stone")  teksture.loadFromFile("images/splinter/stone.png");
	if (name == "cactus1")  teksture.loadFromFile("images/splinter/cactus1.png");
	if (name == "cactus2")  teksture.loadFromFile("images/splinter/cactus2.png");
	if (name == "wood1") teksture.loadFromFile("images/splinter/wood1.png");
	if (name == "leaf1")  teksture.loadFromFile("images/splinter/leaf1.png");

	static bool firstTime = true;
	if(firstTime)
	{
		srand(time(NULL));
		firstTime = false;
	}
	sprite.setTexture(teksture);

	if (name == "blood")
	{
		sprite.setPosition(a, h);
	}
	else
	{
		if (left) sprite.setPosition(a - 25, h);
		else sprite.setPosition(a + 25, h);
	}
	

	

	timee = 0;

	int los = rand() % 100;
	int los2 = rand() % 100;
	int los3 = rand() % 100;
	speed.x = (los-50)/100.0f;
	speed.y = (los2-50) / 100.0f;
	rotation = (los3 - 50) / 100.0f;
}

void Splinter::renderAll(sf::RenderWindow * window)
{
	for (int i = splinter.size() - 1; i >= 0; i--)
	{
		splinter[i] -> render(window);
	}
}

void Splinter::render(sf::RenderWindow * window)
{
	window->draw(sprite);
}

void Splinter::updateAll()
{
	for (int i = splinter.size() - 1; i >= 0; i--)
	{
		splinter[i]->update();
	}

	for (int i = splinter.size() - 1; i >= 0; i--)
	{
		if (splinter[i]->timee > 5000) splinter.erase(splinter.begin() + i);
	}
}

void Splinter::update()
{
	timee += GameInfo::getDeltaTime();
	gravity.gravity(speed, GameInfo::getDeltaTime());
	sprite.move(speed.x * GameInfo::getDeltaTime() / 5.0, speed.y * GameInfo::getDeltaTime() / 5.0);
	rotation = rotation * 0.99;
	sprite.rotate(rotation);
}

void Splinter::addSplinter(float a, float h, std::string name, int ammount, bool left)
{
	for (int i = 0; i < ammount; i++)
	{
		Splinter::splinter.push_back(std::make_shared <Splinter>(a, h, name, left));
	}
}
