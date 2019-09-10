#include "Weapon.h"
#include"Shoot.h"
#include "Player.h"
#include "Camera.h"

sf::SoundBuffer Weapon::bufferAk47;
sf::SoundBuffer Weapon::bufferShotgun;

Weapon::Weapon()
{
	srand(time(NULL));
	this->name = "pistol";
	//buffer.loadFromFile("music/pistol.wav");
	//sound.setBuffer(buffer);

	shootSpeed = 500;
	deltaTime = 0;

	static bool firstTime = true;
	if (firstTime)
	{
		bufferAk47.loadFromFile("music/ak47.wav");
		bufferShotgun.loadFromFile("music/shotgun.wav");
		firstTime = false;
	}
	sound.setBuffer(bufferAk47);
}

void Weapon::shoot(float x, float y, bool right, float dmg)
{
	if (deltaTime >= shootSpeed)
	{
		if (name == "pistol") Shoot::addShoot(x, y, right, sf::Vector2f(1, 0), 1.0f * dmg);	// 2 dmg/s
		if (name == "p90") Shoot::addShoot(x, y, right, sf::Vector2f(0.8, 0), 0.5f * dmg); // 6.5 dmg/s
		if (name == "ak47") Shoot::addShoot(x, y, right, sf::Vector2f(1.2, 0), 1.0f * dmg); //5 dmg/s
		if (name == "shotgun") //7.5 dmg/s
		{
			int los;
			float strzal;
			for (int i = 0; i < 5; i++)
			{
				los = rand() % 100;
				los -= 50;
				strzal = los / 500.0f;
				Shoot::addShoot(x, y, right, sf::Vector2f(0.8, strzal), 1.5f * dmg);
			}
			Camera::IsShaking = true;
		}
		deltaTime = 0;
		sound.play();
	}
}

void Weapon::update(int deltaTime)
{
	this->deltaTime += deltaTime;	//b³¹d
}

void Weapon::changeWeapon(std::string name)
{
	this->name = name;

	if (name == "pistol")
	{
		shootSpeed = 500;
		sound.setBuffer(bufferAk47);
		sound.setVolume(10);
	}
	if (name == "p90")
	{
		shootSpeed = 75;
		sound.setBuffer(bufferAk47);
		sound.setVolume(7);
	}
	if (name == "shotgun")
	{
		shootSpeed = 1000;
		sound.setBuffer(bufferShotgun);
		sound.setVolume(40);
	}
	if (name == "ak47")
	{
		shootSpeed = 200;
		sound.setBuffer(bufferAk47);
		sound.setVolume(10);
	}

}
