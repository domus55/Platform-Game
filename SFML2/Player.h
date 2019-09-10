#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <memory>
#include <time.h>
#include "Camera.h"
#include "HUD.h"
#include "Menu.h"
#include "Collision.h"
#include "Gravity.h"
#include "Bonus.h"
#include "Shoot.h"
#include "Weapon.h"
#include "RenderHp.h"
#include "GameInfo.h"

class Player
{
public:
	Player();
	
	static void renderAll(sf::RenderWindow *window);
	static void renderAllHp(sf::RenderWindow *window, sf::Vector2f view);
	void renderHp2(sf::RenderWindow *window, sf::Vector2f view);
	static void updateAll(sf::RenderWindow *window, int deltaTime);
	void render( sf::RenderWindow *window );
	void update(sf::RenderWindow *window, int deltaTime, int playerNumber);
	void move(int deltaTime);
	void shoot(int deltaTime);
	void hited(float dmg = 1);
	bool collision( sf::Vector2f position, sf::Vector2f size );
	bool boolCollision(sf::Vector2f position, sf::Vector2f size);
	bool checkCollision(sf::RenderWindow *window, int deltaTime);	//je¿eli gracz ma kolizje z blokiem finish i restartuje poziom, to zwraca true
	void checkDeath(sf::RenderWindow *window, int playerNumber);
	void teleport(float a, float h);
	sf::Vector2f getPosition();
	float getPositionX();
	float getPositionY();
	sf::Vector2f getSize();

	static std::vector < std::shared_ptr <Player> > player;

	float maxHp;
	float hp;
	float dmg;
	Weapon weapon;
	bool inWater;
private:

	void chechHitWall();

	static sf::Sound soundHit;
	static sf::Sound soundDead;
	static sf::Sound soundJump;
	static sf::SoundBuffer bufferHit;
	static sf::SoundBuffer bufferDead;
	static sf::SoundBuffer bufferJump;

	sf::Sprite sprite;
	sf::Texture tekstureLeft;
	sf::Texture tekstureRight;
	sf::Texture tekstureHeart;
	sf::Sprite heart;
	sf::Vector2i size;
	sf::Vector2f speed;
	sf::Vector2f blockSpeed;
	sf::Vector2f speeding;
	bool canJump;
	int numer;
	
	bool up;
	bool left;
	bool down;
	bool right;
	bool isShooting;
	bool shootLeft;
	bool hitWall;
	bool hitWall2;
	bool hitFloor;
	bool hitFloor2;
	bool check;
	int shootSpeed;	//odstêp czasu miêdzy strza³ami czym wiêcej, tym wiêkszy
	int deltaTime2;
	Gravity gravity;
	RenderHp renderHp;

	//animations
	int pistolLeft;
	int pistolRight;
	int goPistolLeft;
	int goPistolRight;
	int shotgunLeft;
	int shotgunRight;
	int goShotgunLeft;
	int goShotgunRight;
	int ak47Left;
	int ak47Right;
	int goAk47Left;
	int goAk47Right;
	int p90Left;
	int p90Right;
	int goP90Left;
	int goP90Right;
	//end animations
};

