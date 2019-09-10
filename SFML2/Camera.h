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
	
	static bool dynamicCamera; 	// je�li tak, to kamera przesuwa si� p�ynniej
	static int smoothness; //jak p�ynnie ma si� przesuwa� kamera
	static bool IsShaking;	//bool czy kamera ma si� trz���
	static int shakeDuration; //czas w mili sekundach ile ma si� trz��� kamera
	static float shakeForce;	//moc z jak� trz�sie si� kamera
private:
	static void setCamera(sf::View &view);
	static void shake(sf::View & view);
};

