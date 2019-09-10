#include "Visible.h"

void Visible::makeAll()
{
	blockSetVisible();
}

void Visible::blockSetVisible()
{
	/*for (int i = 0; i < Block::block.size(); i++)
	{
		Block::block[i]->isVisible = false;
	}

	for (int i = 0; i < Block::dmgBlock.size(); i++)
	{
		Block::dmgBlock[i]->isVisible = false;
	}*/

	for (int i = 0; i < Block::block.size(); i++)
	{
		if (boolCollision(Block::block[i]->getPosition(), Block::block[i]->getSize())) Block::block[i]->isVisible = true;
		else Block::block[i]->isVisible = false;
	}

	for (int i = 0; i < Block::dmgBlock.size(); i++)
	{
		if (boolCollision(Block::dmgBlock[i]->getPosition(), Block::dmgBlock[i]->getSize())) Block::dmgBlock[i]->isVisible = true;
		else Block::dmgBlock[i]->isVisible = false;
	}

	for (int i = 0; i < Block::background.size(); i++)
	{
		if (boolCollision(Block::background[i]->getPosition(), Block::background[i]->getSize())) Block::background[i]->isVisible = true;
		else Block::background[i]->isVisible = false;
	}

}

bool Visible::boolCollision(sf::Vector2f position2, sf::Vector2f size2)
{
	sf::Vector2f position;
	sf::Vector2f size;

	position = GameInfo::getViewCenter();
	size.x = 1600;
	size.y = 900;

	Collision collision(position, size);

	return collision.boolCheckCollision(position2, size2);
}
