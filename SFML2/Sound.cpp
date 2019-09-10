#include "Sound.h"
#include "Collision.h"
#include "Player.h"

void Sound::setVolume(sf::Sound & sound, sf::Vector2f position)
{
	sf::Vector2f playersCentre;
	playersCentre.x = 0;
	playersCentre.y = 0;

	int i = 0;
	for (i = 0; i < Player::player.size(); i++)
	{
		playersCentre += Player::player[i]->getPosition();
	}
	if (Player::player.size() != 0)
	{
		playersCentre.x /= i;
		playersCentre.y /= i;
	}

	float distance = Collision::distance(position, playersCentre);

	float volume = 100 - distance / 30;
	volume -= 50;
	if (volume < 0) volume = 0;
	sound.setVolume(volume);
}
