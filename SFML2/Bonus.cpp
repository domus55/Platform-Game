#include "Bonus.h"


std::vector < std::shared_ptr <Bonus> > Bonus::bonus;

Bonus::Bonus(float x, float y, std::string name)
{
	sprite.setScale(5, 5);

	if (name == "heart") { teksture.loadFromFile("images/bonus/heart.png"); this->name = "heart"; }
	if (name == "pistol") { teksture.loadFromFile("images/bonus/pistol.png"); this->name = "pistol"; sprite.setScale(4, 4); }
	if (name == "p90") { teksture.loadFromFile("images/bonus/p90.png"); this->name = "p90"; sprite.setScale(4, 4); }
	if (name == "shotgun") { teksture.loadFromFile("images/bonus/shotgun.png"); this->name = "shotgun"; sprite.setScale(8, 8); }
	if (name == "ak47") { teksture.loadFromFile("images/bonus/ak47.png"); this->name = "ak47"; sprite.setScale(8, 8); }

	sprite.setTexture(teksture);
	size = sprite.getTexture()->getSize();
	sprite.setOrigin(static_cast<float>(size.x / 2), static_cast<float>(size.y / 2));
	sprite.setPosition(x, y);
}

void Bonus::makeBonus(float x, float y, std::string name)
{
	Bonus::bonus.push_back(std::make_shared <Bonus>(x * 50 + 25, y * 50 + 25, name));
}

void Bonus::renderAll(sf::RenderWindow * window)
{
	for (unsigned int i = 0; i < bonus.size(); i++)
	{
		bonus[i]->render(window);
	}
}

void Bonus::updateAll()
{
	for (int i = bonus.size() - 1; i >= 0; i--)
	{
		bonus[i]->update(i);
	}
}

void Bonus::update(int bonusNumber)
{
	for (int i = Player::player.size() - 1; i >= 0; i--)
	{
		if (boolCollision(Player::player[i]->getPosition(), Player::player[i]->getSize()))
		{
			if (name == "heart") Player::player[i] -> hp += 2;
			if (name == "pistol") Player::player[i]->weapon.changeWeapon("pistol");
			if (name == "p90") Player::player[i]->weapon.changeWeapon("p90");
			if (name == "shotgun") Player::player[i]->weapon.changeWeapon("shotgun");
			if (name == "ak47") Player::player[i]->weapon.changeWeapon("ak47");
			Bonus::bonus.erase(Bonus::bonus.begin() + bonusNumber); 
		}
	}
}

void Bonus::render(sf::RenderWindow * window)
{
	window->draw(sprite);
}

sf::Vector2f Bonus::getPosition()
{
	sf::Vector2f position = sprite.getPosition();
	return position;
}

sf::Vector2f Bonus::getSize()
{
	sf::Vector2f size;
	size.x = sprite.getScale().x * this->size.x;
	size.y = sprite.getScale().y * this->size.y;

	return size;
}

bool Bonus::boolCollision(sf::Vector2f position2, sf::Vector2f size2)
{
	sf::Vector2f position;
	sf::Vector2f size;

	position = sprite.getPosition();
	size.x = sprite.getScale().x * this->size.x;
	size.y = sprite.getScale().y * this->size.y;

	Collision collision(position, size);

	return collision.boolCheckCollision(position2, size2);
}

