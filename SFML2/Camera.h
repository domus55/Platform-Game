#pragma once

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>  
#include "Player.h"
#include "Menu.h"
#include "GameInfo.h"

class Camera
{
public:
	static void update(sf::View & view);
	
	static bool dynamicCamera; 	// jeœli tak, to kamera przesuwa siê p³ynniej
	static int smoothness; //jak p³ynnie ma siê przesuwaæ kamera
	static bool IsShaking;	//bool czy kamera ma siê trz¹œæ
	static int shakeDuration; //czas w mili sekundach ile ma siê trz¹œæ kamera
	static float shakeForce;	//moc z jak¹ trzêsie siê kamera
private:
	static void setCamera(sf::View &view);
	static void shake(sf::View & view);
};

