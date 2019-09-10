#include "LevelMenager.h"

int LevelMenager::level = 0;

void LevelMenager::makeAll(sf::RenderWindow *window, bool nextLevel, int deltaTime)
{
	if(nextLevel==true)
	{
		LevelEvent::restart = true;

		std::string weapon[2] = { "pistol", "pistol" };
		for (unsigned int i = 0; i < Player::player.size(); i++)
		{
			weapon[i] = Player::player[i]->weapon.name;
		}

		Player::player.clear();
		Player::player.push_back(std::make_shared <Player>()); Player::player[0]->weapon.changeWeapon(weapon[0]);
		if (Menu::numberOfPlayers == 2) { Player::player.push_back(std::make_shared <Player>()); Player::player[1]->weapon.changeWeapon(weapon[1]); }

		level++;
		switch (level)
		{
		case 1: level1(window);    break;
		case 2: level2(window);    break;
		case 3: level3(window);    break;
		case 4: level4(window);    break;
		case 5: level5(window);    break;
		case 6: level6(window);    break;
		case 7: level7(window);    break;
		case 8: level8(window);    break;
		case 9: level9(window);    break;
		case 10: level10(window);    break;
		case 11: level11(window);    break;
		case 12: level12(window);    break;
		case 13: level13(window);    break;
		case 14: level14(window);    break;
		case 15: level15(window);    break;
		}
	}

	LevelEvent::deltaTime = deltaTime;
	LevelEvent::levelEvent(level, deltaTime);
}

void LevelMenager::restartLevel(sf::RenderWindow *window)
{
	Block::dmgBlock.clear();
	Block::block.clear();
	Block::background.clear();
	BasicEnemy::enemy.clear();
	Bonus::bonus.clear();
	Shoot::shoot.clear();
	Splinter::splinter.clear();
	Animation::restart();

	level--;
	makeAll(window, true, 0);
}

void LevelMenager::makeLevel(sf::RenderWindow *window, sf::Image image, int up)
{
	int h = 0;
	sf::Vector2f teleport;
	teleport.x = 0;
	teleport.y = 0;

	for (int a = 0; ; a ++)
	{
		if(a%5 == 0) Loading::render(window);
		sf::Color color = image.getPixel(a, h);

		if (!(color.r == 255 && color.g == 255 && color.b == 255))
		{
			if (color.r == 0 && color.g == 0 && color.b == 0) { h++; a = -1; }
			if (color.r == 101 && color.g == 0 && color.b == 0) { Shoot::setBorderMap(sf::Vector2f(a*50 + 1000, h*50 + 1000)); goto end; }
			if (color.r == 200 && color.g == 0 && color.b == 0)
			{
				teleport.x = a;
				teleport.y = h + up - 1;
			}
			if (level < 6)
			{
				if (color.r == 0 && color.g == 245 && color.b == 0) Block::makeBlock(a, h + up, "flower");
				else if (color.r == 0 && color.g == 255 && color.b == 0) Block::makeBlock(a, h + up, "grass");
				else if (color.r == 145 && color.g == 85 && color.b == 0) Block::makeBlock(a, h + up, "dirt");
				else if (color.r == 255 && color.g == 255 && color.b == 0) Block::makeBlock(a, h + up, "sand");
				else if (color.r == 200 && color.g == 200 && color.b == 200) Block::makeBlock(a, h + up, "glass");
				else if (color.r == 100 && color.g == 100 && color.b == 100) Block::makeBlock(a, h + up, "stone");
				else if (color.r == 0 && color.g == 250 && color.b == 0) Block::makeBlock(a, h + up, "cactus");
				else if (color.r == 120 && color.g == 100 && color.b == 0) Block::makeBlock(a, h + up, "wood1");
				else if (color.r == 0 && color.g == 100 && color.b == 0) Block::makeBlock(a, h + up, "leaf1");

				else if (color.r == 0 && color.g == 255 && color.b == 40) Block::makeBlock(a, h + up, "grass", false);
				else if (color.r == 145 && color.g == 85 && color.b == 40) Block::makeBlock(a, h + up, "dirt", false);
				else if (color.r == 255 && color.g == 255 && color.b == 40) Block::makeBlock(a, h + up, "sand", false);
				else if (color.r == 100 && color.g == 100 && color.b == 140) Block::makeBlock(a, h + up, "stone", false);
				else if (color.r == 120 && color.g == 100 && color.b == 40) Block::makeBlock(a, h + up, "wood1", false);
				else if (color.r == 0 && color.g == 100 && color.b == 40) Block::makeBlock(a, h + up, "leaf1", false);

				else if (color.r == 0 && color.g == 255 && color.b == 80) Block::makeBlockBackground(a, h + up, "grass");
				else if (color.r == 145 && color.g == 85 && color.b == 80) Block::makeBlockBackground(a, h + up, "dirt");
				else if (color.r == 255 && color.g == 255 && color.b == 80) Block::makeBlockBackground(a, h + up, "sand");
				else if (color.r == 100 && color.g == 100 && color.b == 180) Block::makeBlockBackground(a, h + up, "stone");
				else if (color.r == 120 && color.g == 100 && color.b == 80) Block::makeBlockBackground(a, h + up, "wood1");
				else if (color.r == 0 && color.g == 100 && color.b == 80) Block::makeBlockBackground(a, h + up, "leaf1");
				else if (color.r == 100 && color.g == 100 && color.b == 255) { Block::makeBlock(a, h + up, "water"); Block::makeBlockBackground(a, h + up, "stone"); }
				else if (color.r == 145 && color.g == 85 && color.b == 255) { Block::makeBlock(a, h + up, "water"); Block::makeBlockBackground(a, h + up, "dirt"); }
				else if (color.r == 0 && color.g == 255 && color.b == 255) { Block::makeBlock(a, h + up, "water"); Block::makeBlockBackground(a, h + up, "grass"); }

				else if (color.r == 200 && color.g == 185 && color.b == 0) { Block::makeBlock(a, h + up, "ladder"); Block::makeBlockBackground(a, h + up, "stone"); }
				else if (color.r == 245 && color.g == 170 && color.b == 0) { Block::makeBlock(a, h + up, "ladder"); Block::makeBlockBackground(a, h + up, "dirt"); }
				else if (color.r == 100 && color.g == 255 && color.b == 0) { Block::makeBlock(a, h + up, "ladder"); Block::makeBlockBackground(a, h + up, "grass"); }
			}
			else
			{
				if (color.r == 0 && color.g == 245 && color.b == 0) Block::makeBlock(a, h + up, "flower2");
				else if (color.r == 0 && color.g == 255 && color.b == 0) Block::makeBlock(a, h + up, "grass2");
				else if (color.r == 145 && color.g == 85 && color.b == 0) Block::makeBlock(a, h + up, "dirt2");
				else if (color.r == 255 && color.g == 255 && color.b == 0) Block::makeBlock(a, h + up, "sand2");
				else if (color.r == 200 && color.g == 200 && color.b == 200) Block::makeBlock(a, h + up, "glass");
				else if (color.r == 100 && color.g == 100 && color.b == 100) Block::makeBlock(a, h + up, "stone2");
				else if (color.r == 0 && color.g == 250 && color.b == 0) Block::makeBlock(a, h + up, "cactus2");
				else if (color.r == 120 && color.g == 100 && color.b == 0) Block::makeBlock(a, h + up, "wood2");
				else if (color.r == 0 && color.g == 100 && color.b == 0) Block::makeBlock(a, h + up, "leaf2");
			}
			
			
			if(color.r == 201 && color.g == 201 && color.b == 201) Block::makeBlock(a, h + up, "glassWall");
			else if(color.r == 120 && color.g == 120 && color.b == 120) Block::makeBlock(a, h + up, "finish");
			else if(color.r == 100 && color.g == 85 && color.b == 0) Block::makeBlock(a, h + up, "ladder");
			else if (color.r == 0 && color.g == 0 && color.b == 255) Block::makeBlock(a, h + up, "water");
			else if(color.r == 255 && color.g == 0 && color.b == 0) Block::makeBlock(a, h + up, "lava");
		}
	}
end:;
	for (int j = Player::player.size() - 1; j >= 0; j--)
	{
		Player::player[j]->teleport(teleport.x, teleport.y);
	}
}

void LevelMenager::level1(sf::RenderWindow *window)
{
	sf::Image image;
	image.loadFromFile("images/level/1.png");
	makeLevel(window, image);

	std::cout << "1";

	EnemyZombie::addEnemy(2, 59, 2000);
	EnemyZombie::addEnemy(27, 59, 1000);
	EnemyZombie::addEnemy(61, 59, 500);

	Bonus::makeBonus(10, 39, "heart");
	Bonus::makeBonus(2, 59, "ak47");
	Bonus::makeBonus(326, 36, "ak47");
}

void LevelMenager::level2(sf::RenderWindow *window)
{
	sf::Image image;
	image.loadFromFile("images/level/2.png");
	makeLevel(window, image);
	Block::makeBlockBackground(22, 127, "dirt");
}

void LevelMenager::level3(sf::RenderWindow *window)
{
	sf::Image image;
	image.loadFromFile("images/level/3.png");
	makeLevel(window, image, -15);

	for (int i = -1; i < 12; i++)
	{
		Block::makeBlock(49, 16 - i, "glass");
	}

	Block::makeBlock(153.8, -1, "stone");
	Block::makeBlock(156.2, -1, "stone");
	Block::makeBlock(153.8, -2, "grass");
	Block::makeBlock(156.2, -2, "grass");

	Bonus::makeBonus(141, -3, "heart");
	Bonus::makeBonus(167, -3, "heart");

	Bonus::makeBonus(153, -3, "shotgun");
	Bonus::makeBonus(157, -3, "shotgun");

	Bonus::makeBonus(18, 11, "shotgun");
	Bonus::makeBonus(20.5, 11, "ak47");
	Bonus::makeBonus(23, 11, "shotgun");
	Bonus::makeBonus(25.5, 11, "heart");
	Bonus::makeBonus(28, 11, "heart");

	EnemyZombie::addEnemy(240, 16, 800);
	EnemyZombie::addEnemy(241, 10, 550);
	EnemyZombie::addEnemy(245, 5, 600);
}

void LevelMenager::level4(sf::RenderWindow *window)
{
	sf::Image image;
	image.loadFromFile("images/level/4.png");
	makeLevel(window, image);

	for (int i = -1; i < 12; i++)
	{
		Block::makeBlock(0, 16 - i, "glass");
	}

	Block::makeBlock(68, 16, "glass", true, 0);
	Block::makeBlock(69, 16, "glass", true, 0);
	Block::makeBlock(70, 16, "glass", true, 0);

	Block::makeBlock(221, 10, "glass", true, 1);
	Block::makeBlock(222, 10, "glass", true, 1);
	Block::makeBlock(223, 10, "glass", true, 1);

	EnemyZombie::addEnemy(15, 10, 400);
	EnemyZombie::addEnemy(51, 7, 400);
	EnemyZombie::addEnemy(114, 11, 500);
	EnemyZombie::addEnemy(143, 14, 700);
	EnemyZombie::addEnemy(201, 14, 400);
}

void LevelMenager::level5(sf::RenderWindow *window)
{
	sf::Image image;
	image.loadFromFile("images/level/5.png");
	makeLevel(window, image);

	for (int i = 0; i < 12; i++)
	{
		Block::makeBlock(71, 16 - i, "glass");
	}
}

void LevelMenager::level6(sf::RenderWindow *window)
{
	Menu::movingCamera = false;

	Shoot::setBorderMap(sf::Vector2f(10000, 10000));

	for (int i = -32; i < 32; i++)
	{
		Block::makeBlock(i, 17, "grass2");
	}

	Player::player[0]->teleport(-8, 1);

	Block::makeBlock(-4.5, 14, "stone");
	Block::makeBlock(-3.5, 13, "stone");
	Block::makeBlock(-3.5, 12, "stone");
	Block::makeBlock(-2.6, 11, "stone");
	Block::makeBlock(-1.6, 11, "stone");

	Block::makeBlock(-0.5, 14, "ladder");
	Block::makeBlock(-0.5, 13, "ladder");
	Block::makeBlock(-0.5, 12, "ladder");
	Block::makeBlock(-0.5, 11, "ladder");

	Block::makeBlock(3.5, 14, "stone");
	Block::makeBlock(2.5, 13, "stone");
	Block::makeBlock(2.5, 12, "stone");
	Block::makeBlock(1.6, 11, "stone");
	Block::makeBlock(0.6, 11, "stone");
}

void LevelMenager::level7(sf::RenderWindow *window)
{
	sf::Image image;
	image.loadFromFile("images/level/7.png");
	makeLevel(window, image);

	Block::makeBlock(0, 15, "finish");
}

void LevelMenager::level8(sf::RenderWindow *window)
{
	sf::Image image;
	image.loadFromFile("images/level/8.png");
	makeLevel(window, image);

	Block::makeBlock(0, 15, "finish");
}

void LevelMenager::level9(sf::RenderWindow *window)
{
	sf::Image image;
	image.loadFromFile("images/level/9.png");
	makeLevel(window, image);

	Block::makeBlock(0, 15, "finish");
}

void LevelMenager::level10(sf::RenderWindow *window)
{
	sf::Image image;
	image.loadFromFile("images/level/10.png");
	makeLevel(window, image);

	Block::makeBlock(0, 15, "finish");
}

void LevelMenager::level11(sf::RenderWindow *window)
{
	sf::Image image;
	image.loadFromFile("images/level/11.png");
	makeLevel(window, image);

	Block::makeBlock(0, 15, "finish");
}

void LevelMenager::level12(sf::RenderWindow *window)
{
	sf::Image image;
	image.loadFromFile("images/level/12.png");
	makeLevel(window, image);

	Block::makeBlock(0, 15, "finish");
}

void LevelMenager::level13(sf::RenderWindow *window)
{
	sf::Image image;
	image.loadFromFile("images/level/13.png");
	makeLevel(window, image);

	Block::makeBlock(0, 15, "finish");
}

void LevelMenager::level14(sf::RenderWindow *window)
{
	sf::Image image;
	image.loadFromFile("images/level/14.png");
	makeLevel(window, image);

	Block::makeBlock(0, 15, "finish");
}

void LevelMenager::level15(sf::RenderWindow *window)
{
	sf::Image image;
	image.loadFromFile("images/level/15.png");
	makeLevel(window, image);

	Block::makeBlock(0, 15, "finish");
}