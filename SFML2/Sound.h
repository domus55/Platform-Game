#pragma once

#include <SFML/Audio.hpp>

class Sound
{
public:
	static void setVolume(sf::Sound &sound, sf::Vector2f position);
};

