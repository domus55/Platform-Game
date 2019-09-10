#include "Collision.h"


Collision::Collision(sf::Vector2f position, sf::Vector2f size)
{
	this->position = position;
	this->halfSize.x = 0.5*size.x;
	this->halfSize.y = 0.5*size.y;
}

sf::Vector2f Collision::checkCollision(sf::Vector2f otherPosition, sf::Vector2f otherSize)
{
	sf::Vector2f otherHalfSize;
	otherHalfSize.x = 0.5*otherSize.x;
	otherHalfSize.y = 0.5*otherSize.y;

	float deltaX = otherPosition.x - position.x;
	float deltaY = otherPosition.y - position.y;
	float intersectX = abs(deltaX) - ( otherHalfSize.x + halfSize.x );
	float intersectY = abs(deltaY) - (otherHalfSize.y + halfSize.y);

	sf::Vector2f changePosition;
	changePosition.x = 0.0f;
	changePosition.y = 0.0f;

	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		if (intersectX > intersectY)
		{
			if (deltaX > 0.0f)
			{
				changePosition.x = intersectX;
				changePosition.y = 0.0f;
			}
			else
			{
				changePosition.x = -intersectX;
				changePosition.y = 0.0f;
			}
		}
		else
		{
			if (deltaY > 0.0f)
			{
				changePosition.x = 0.0f;
				changePosition.y = intersectY;
			}
			else
			{
				changePosition.x = 0.0f;
				changePosition.y = -intersectY;
			}

		}
		return changePosition;
	}
	return changePosition;
}

bool Collision::boolCheckCollision(sf::Vector2f otherPosition, sf::Vector2f otherSize)
{
	sf::Vector2f otherHalfSize;
	otherHalfSize.x = 0.5*otherSize.x;
	otherHalfSize.y = 0.5*otherSize.y;



	float deltaX = otherPosition.x - position.x;
	float deltaY = otherPosition.y - position.y;
	float intersectX = abs(deltaX) - (otherHalfSize.x + halfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + halfSize.y);

	sf::Vector2f changePosition;
	changePosition.x = 0.0f;
	changePosition.y = 0.0f;

	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		return true;
	}
	return false;
}

float Collision::distance(sf::Vector2f position, sf::Vector2f position2)
{
	float a = position.x - position2.x;
	float h = position.y - position2.y;
	float distance = sqrt(pow(a,2) + pow(h,2));
	return distance;
}


Collision::~Collision()
{
}
