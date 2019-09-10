#include "LevelEvent.h"

bool LevelEvent::restart = false;
int LevelEvent::deltaTime = 1;

void LevelEvent::levelEvent(int level, int deltaTime)
{
	switch(level)
	{
	case 1: level1(); break;
	case 2: level2(); break;
	case 3: level3(); break;
	case 4: level4(); break;
	case 5: level5(); break;
	case 6: level6(); break;
	}

	restart = false;
}

void LevelEvent::level1()
{

}

void LevelEvent::level2()
{
	
}

void LevelEvent::level3()
{
	static bool movingCamera = false;

	sf::Vector2f v = GameInfo::getViewCenter();
	if (v.y > 450) movingCamera = false;

	for (int i = Player::player.size() - 1; i >= 0; i--)
	{
		if (Player::player[i]->getPositionX() > 7750 && Player::player[i]->getPositionX() < 7850 &&  Player::player[i]->getPositionY() <= 450)
		{
			movingCamera = true;
		}

		if (Player::player[i]->getPositionY() <= 10) movingCamera = true;
	}
	Menu::movingCamera = movingCamera;
}

void LevelEvent::level4()
{
	static bool firstTime = true;
	static bool down = true;
	static bool right = true;
	static int distance0 = 0;
	static int distance1 = 0;
	static bool run = false;
	static int j = 0;
	if (restart)
	{
		firstTime = true;
		down = true;
		right = true;
		distance0 = 0;
		distance1 = 0;
		j = 0;
		run = false;
		//Player::player[0]->teleport(50, 5);

		for (int i = Block::block.size() - 1; i >= 0; i--)
		{
			if (Block::block[i]->id == 0)
			{
				Block::block[i]->setMove(sf::Vector2f(0, 0.05), sf::Vector2f(0, 2));
			}
		}
	}

	for (int i = Player::player.size() - 1; i >= 0; i--)
	{
		if (Player::player[i]->getPositionX() > 11000)
		{
			j += GameInfo::getDeltaTime();;
			if (j>1000) run = true;
		}
	}
	if (run && firstTime)
	{
		for (int i = Block::block.size() - 1; i >= 0; i--)
		{
			if (Block::block[i]->id == 1)
			{
				Block::block[i]->setMove(sf::Vector2f(0.2, 0), sf::Vector2f(40, 0));
			}
		}
		firstTime = false;
	}
}

void LevelEvent::level5()
{
	Shoot::deleteShoot = false;
	static int distance = 10175;
	if (restart) distance = 10175;
	for (int j = Player::player.size() - 1; j >= 0; j--)
	{
		if (Player::player[j]->getPositionX() >= distance)
		{
			for (int i = Block::block.size() - 1; i >= 0; i--)
			{
				if (Block::block[i]->name == "glass") Block::block.erase(Block::block.begin() + i);
				else Block::block[i]->moveBlock(sf::Vector2f(6500, 0));
			}

			for (int i = Block::dmgBlock.size() - 1; i >= 0; i--)
			{
				Block::dmgBlock[i]->moveBlock(sf::Vector2f(6500, 0));
			}
			distance += 6500;
		}
	}

}

void LevelEvent::level6()
{
	Shoot::deleteShoot = true;

	static float h = 0;
	static int deltaTime2 = 0;
	static int enemySpawnSpeed = 5000;
	static int los;
	if (h < 10) h += 0.00003 * deltaTime;
	deltaTime2 += deltaTime;

	if (restart)
	{
		enemySpawnSpeed = 5000;	//5000
		deltaTime2 = 0;
		h = 0;
	}

	if (deltaTime2 > enemySpawnSpeed)
	{
		bool pistol = false;
		bool p90 = false;
		bool ak47 = false;
		bool shotgun = false;

		for (int i = Bonus::bonus.size() - 1; i >= 0; i--)
		{
			if (Bonus::bonus[i]->name == "heart") Bonus::bonus.erase(Bonus::bonus.begin() + i);
			if (Bonus::bonus[i]->name == "pistol") pistol = true;
			if (Bonus::bonus[i]->name == "p90") p90 = true;
			if (Bonus::bonus[i]->name == "ak47") ak47 = true;
			if (Bonus::bonus[i]->name == "shotgun") shotgun = true;
		}

		Bonus::makeBonus(-2, 12.5, "heart");
		Bonus::makeBonus(1, 12.5, "heart");

		if (!pistol) Bonus::makeBonus(-2, 7, "pistol");
		if (!p90) Bonus::makeBonus(1, 7, "p90");
		if (!ak47) Bonus::makeBonus(3, 10, "ak47");
		if (!shotgun) Bonus::makeBonus(-4, 10, "shotgun");

		if (enemySpawnSpeed > 400 && enemySpawnSpeed < 900)
		{
			los = rand() % 10;
			if (los == 0) EnemyAlien::addEnemy(3, -2);
			if (los == 1) EnemyAlien::addEnemy(-3, -2);
			if (los > 1 && los < 6) EnemyAlien::addEnemy(32, 1);
			if (los >= 6) EnemyAlien::addEnemy(-32, 1);
		}
		else
		{
			if (enemySpawnSpeed <= 300)
			{
				EnemyAlien::addEnemy(32, 1);
				EnemyAlien::addEnemy(-32, 1);
			}
			else
			{
				los = rand() % 2;
				if (los == 0)
				{
					int los2;
					los2 = rand() % 7;	//usun¹æ

					if (los2 == 0) EnemyAlien::addEnemy(32, 1);
					if (los2 == 1) EnemyBoss::addEnemy(32, 1);
					if (los2 == 2) EnemyDemon::addEnemy(32, 1);
					if (los2 == 3) EnemyFlyingDemon::addEnemy(32, 1);
					if (los2 == 4) EnemyGhost::addEnemy(32, 1);
					if (los2 == 5) EnemyWoodcutter::addEnemy(32, 1);
					if (los2 == 6) EnemyZombie::addEnemy(32, 1, 1500);
					
				}
				else
				{
					int los2;
					los2 = rand() % 7;	//usun¹æ

					if (los2 == 0) EnemyAlien::addEnemy(-32, 1);
					if (los2 == 1) EnemyBoss::addEnemy(-32, 1);
					if (los2 == 2) EnemyDemon::addEnemy(-32, 1);
					if (los2 == 3) EnemyFlyingDemon::addEnemy(-32, 1);
					if (los2 == 4) EnemyGhost::addEnemy(-32, 1);
					if (los2 == 5) EnemyWoodcutter::addEnemy(-32, 1);
					if (los2 == 6) EnemyZombie::addEnemy(-32, 1, 1500);
				}
			}
		}



		if (enemySpawnSpeed > 300) enemySpawnSpeed *= 0.96;	//300 to limit

		deltaTime2 = 0;
	}

	for (int i = Block::block.size() - 1; i >= 0; i--)
	{
		if (Block::block[i]->name == "finish") Block::block.erase(Block::block.begin() + i);
	}
	Block::makeBlock(-0.5, h, "finish");
}

