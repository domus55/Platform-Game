#include "GameInfo.h"

int GameInfo::deltaTime = 0;
bool GameInfo::inMenu = false;
sf::Vector2f GameInfo::viewCenter;

int GameInfo::getDeltaTime()
{
	return deltaTime;
}

void GameInfo::setDeltaTime(int deltaTime)
{
	GameInfo::deltaTime = deltaTime;
}

sf::Vector2f GameInfo::getViewCenter()
{
	return viewCenter;
}

void GameInfo::setViewCenter(sf::Vector2f viewCenter)
{
	GameInfo::viewCenter = viewCenter;
}
