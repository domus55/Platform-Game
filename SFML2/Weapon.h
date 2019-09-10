#pragma once

#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>  

class Weapon
{
public:
	Weapon();
	void shoot(float x, float y, bool right, float dmg);
	void update(int deltaTime);
	void changeWeapon(std::string name);
	std::string name;
private:
	sf::Sound sound;
	static sf::SoundBuffer bufferAk47;
	static sf::SoundBuffer bufferShotgun;
	int shootSpeed;
	int deltaTime;
};

