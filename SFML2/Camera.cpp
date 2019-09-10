#include "Camera.h"

bool Camera::dynamicCamera = true;
int Camera::smoothness = 25;
bool Camera::IsShaking = false;
int Camera::shakeDuration = 250;
float Camera::shakeForce = 1;

void Camera::update(sf::View & view)
{
	setCamera(view);
	shake(view);
}

void Camera::setCamera(sf::View & view)
{
	if (Player::player.size() != 0)
	{
		if (dynamicCamera)
		{
			sf::Vector2f center = view.getCenter();

			if (Player::player.size() == 1)	//sprawdza, czy gracz siê nie teleportowa³
			{
				if (abs(Player::player[0]->getPositionX() - center.x) > 1000)
				{
					if (Menu::menu[0]->movingCamera) view.setCenter(Player::player[0]->getPosition());
					else view.setCenter(Player::player[0]->getPositionX(), 450);
				}

			}
			else
			{
				sf::Vector2f betweenPlayers;
				betweenPlayers.x = (Player::player[0]->getPositionX() + Player::player[1]->getPositionX()) / 2;
				betweenPlayers.y = (Player::player[0]->getPositionY() + Player::player[1]->getPositionY()) / 2;

				if (abs(betweenPlayers.x - center.x) > 1000)
				{
					if (Menu::menu[0]->movingCamera) view.setCenter(betweenPlayers);
					else view.setCenter(betweenPlayers.x, 450);
				}
			}

			if (Menu::menu[0]->movingCamera)
			{
				if (Player::player.size() == 1)
				{
					view.move((Player::player[0]->getPositionX() - center.x) / smoothness, (Player::player[0]->getPositionY() - center.y) / smoothness);
				}
				else
				{
					view.move((((Player::player[0]->getPositionX() + Player::player[1]->getPositionX()) / 2) - center.x) / smoothness, (((Player::player[0]->getPositionY() + Player::player[1]->getPositionY()) / 2) - center.y) / smoothness);
				}

			}
			else
			{
				if (Player::player.size() == 1)
				{
					view.move((Player::player[0]->getPositionX() - center.x) / smoothness, 450 - center.y);
				}
				else
				{
					view.move((((Player::player[0]->getPositionX() + Player::player[1]->getPositionX()) / 2) - center.x) / smoothness, 450 - center.y);
				}
			}
		}
		else
		{
			if (Menu::menu[0]->movingCamera)
			{
				if (Player::player.size() == 1)
				{
					view.setCenter(Player::player[0]->getPosition());
				}
				else
				{
					view.setCenter((Player::player[0]->getPositionX() + Player::player[1]->getPositionX()) / 2, (Player::player[0]->getPositionY() + Player::player[1]->getPositionY()) / 2);
				}

			}
			else
			{
				if (Player::player.size() == 1)
				{
					view.setCenter(Player::player[0]->getPositionX(), 450);
				}
				else
				{
					view.setCenter((Player::player[0]->getPositionX() + Player::player[1]->getPositionX()) / 2, 450);
				}
			}
		}
	}
}

void Camera::shake(sf::View & view)
{
	static bool firstTime = true;
	static int time = 0;

	time += GameInfo::getDeltaTime();

	if (firstTime && IsShaking)
	{
		time = 0;
		firstTime = false;
	}

	if (time > shakeDuration)
	{
		IsShaking = false;
		firstTime = true;
	}

	if (IsShaking)
	{
		if (time % 5 == 0)
		{
			sf::Vector2f move;
			move.x = (rand() % 100 - 50) / 10.0f * shakeForce;
			move.y = (rand() % 100 - 50) / 10.0f * shakeForce;

			view.move(move);
		}
		
	}

	//int los = rand() % 100;
	//std::cout << IsShaking;
}
