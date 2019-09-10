#include "Button.h"

std::vector < std::shared_ptr <Button> > Button::button;

Button::Button(float x, float y, std::string name)
{
	if (name == "resume") teksture.loadFromFile("images/menu/resume.png");
	if (name == "play") teksture.loadFromFile("images/menu/play.png");
	if (name == "restart") teksture.loadFromFile("images/menu/restart.png");
	if (name == "options") teksture.loadFromFile("images/menu/options.png");
	if (name == "players1") teksture.loadFromFile("images/menu/players1.png");
	if (name == "players2") teksture.loadFromFile("images/menu/players2.png");
	if (name == "movingCameraTrue") teksture.loadFromFile("images/menu/movingCameraTrue.png");
	if (name == "movingCameraFalse") teksture.loadFromFile("images/menu/movingCameraFalse.png");
	

	this->name = name;

	sprite.setTexture(teksture);
	size = sprite.getTexture()->getSize();
	sprite.setOrigin(size.x/2, size.y/2); // sprite.setOrigin(27, 6);
	sprite.setScale(8, 8);
	sprite.setPosition(x, y);
}

void Button::makeButton(int x, int y, std::string name)
{
	Button::button.push_back(std::make_shared <Button>(x, y, name));
}

void Button::renderAll(sf::RenderWindow *window)
{
	for (unsigned int i = 0; i < button.size(); i++)
	{
		button[i]->render(window);
	}
}

void Button::render(sf::RenderWindow *window)
{
	window->draw(sprite);
}

bool Button::isClicked(sf::RenderWindow *window, sf::Vector2f view)
{
	static sf::Vector2f size;
	static sf::Vector2f size2;
	static bool firstTime = true;
	if (firstTime)
	{
		float sizeX = sprite.getScale().x * this->size.x;
		float sizeY = sprite.getScale().y * this->size.y;

		size.x = sizeX;
		size.y = sizeY;

		size2.x = 1;
		size2.y = 1;
	}	

	sf::Vector2i v2 = sf::Mouse::getPosition(*window);
	sf::Vector2f v;
	v.x = v2.x;
	v.y = v2.y;

	v.x -= 800;
	v.x += view.x;
	v.y -= 450;
	v.y += view.y;

	Collision collision(sprite.getPosition(), size);
	return collision.boolCheckCollision(v, size2);
}
