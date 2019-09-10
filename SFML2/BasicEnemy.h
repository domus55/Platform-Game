#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <memory>
#include <iostream>
#include "Collision.h"
#include "RenderHp.h"
#include "Gravity.h"
#include "Splinter.h"


class BasicEnemy
{
public:
	BasicEnemy();
	virtual void render(sf::RenderWindow *window) = 0;
	virtual void update(int deltaTime, int enemyNumber) = 0;

	static void renderAll(sf::RenderWindow *window);
	static void renderAllHp(sf::RenderWindow *window);
	static void updateAll(int deltaTime);

	void renderHp2(sf::RenderWindow *window);
	void hited(float dmg);
	sf::Vector2f getPosition();
	sf::Vector2f getSize();

	void checkDeath(int enemyNumber);
	bool collision(sf::Vector2f position, sf::Vector2f size);
	bool boolCollision(sf::Vector2f position, sf::Vector2f size);
	void checkHitWall();
	void jump();
	void speedInWater();
	void AImove1();	//chodzi od œciany do œciany
	void AImove2(); //pod¹¿a za najbli¿szym graczem
	void AImove3(int distance); //chodzi na wyznaczon¹ odleg³oœæ
	void AImove4(); //lata za graczem
	void AIattack1(int deltaTime);	//zadaje obra¿enie, tylko gdy siê na niego wejdzie
	void AIattack2(int deltaTime, sf::Vector2f attackPosition, sf::Vector2f attackSize);
	bool checkAttack2(sf::Vector2f attackPosition, sf::Vector2f attackSize);
	void move(int deltaTime);

	static std::vector < std::shared_ptr <BasicEnemy> > enemy;
protected:

	static sf::Sound soundHit;
	static sf::Sound soundDead;
	static sf::SoundBuffer bufferHit;
	static sf::SoundBuffer bufferDead;

	float dmg;
	float startPosition;
	void checkCollision(int deltaTime);

	bool hitWall;
	bool hitWall2;	//do poprawnego sprawdzania, uzywane tylko w funkicji collision
	bool hitFloor;
	bool hitFloor2;
	bool check;

	bool right;
	bool canJump;
	bool inWater;
	bool firstTime;
	bool left;
	float hp;
	float maxHp;

	sf::Sprite sprite;
	sf::Vector2u size;
	sf::Vector2f speed;
	sf::Vector2f speeding;

	float attackSpeed;
	int deltaTime2;

	RenderHp renderHp;
	Gravity gravity;

	bool goRight;
	bool goLeft;
	bool goUp;
	bool goDown;
};