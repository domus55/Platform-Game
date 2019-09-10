#include "Game.h"

Game::Game()
{
	isRunning = true;
	window.create(sf::VideoMode(1600, 900, 32), "Game", sf::Style::Close);
	
	deltaTime = 0;
	view.setSize(1600, 900);
	MenuMenager::createMenu();
	Background::addBackground();

	GameInfo::setViewCenter(sf::Vector2f(800, 450));
	//LevelMenager::makeAll(&window, true, deltaTime);	//usun¹æ po dodaniu mainmenu i dodaæ do main menu
	//MenuMenager::inMainMenu = false;	//usun¹æ po dodaniu mainmenu
	//view.zoom(2.5);

	//music.openFromFile("music/music2.wav");	//zmieniæ na music/music.wav
	//music.setVolume(15);
	//music.setLoop(true);
	//music.play();
	GameInfo::inMenu = true;	//dodaæ po dodaniu menu
}

void Game::exit()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
			isRunning = false;
		}		
	}
}

void Game::update()
{
	if (deltaTime > 50) deltaTime = 0;	// resetuje po ³adowaniu nastêpnego poziomu
	GameInfo::setDeltaTime(deltaTime);
	MenuMenager::update(&window);
	if (GameInfo::inMenu)
	{

		GameInfo::setViewCenter(view.getCenter());
	}
	else
	{
		Bonus::updateAll();
		Player::updateAll(&window, deltaTime);
		BasicEnemy::updateAll(deltaTime);
		Block::updateAll(deltaTime);
		Shoot::updateAll(deltaTime);
		LevelMenager::makeAll(&window, false, deltaTime);
		Splinter::updateAll();
		Camera::update(view);
		GameInfo::setViewCenter(view.getCenter());
		Visible::makeAll();	//sprawie, ¿e obiekty poza ekranem nie s¹ renderowane
	}
}

void Game::output()
{
	window.clear(sf::Color(155,155,155,255));
	window.setView(view);

	Background::background[0]->renderAll(&window, view.getCenter());
	Block::renderBackground(&window);
	Shoot::renderAll(&window);
	Player::renderAll(&window);
	BasicEnemy::renderAll(&window);
	Bonus::renderAll(&window);
	Splinter::renderAll(&window);
	Block::renderBlock(&window);
	HUD::renderHp(&window);

	if (GameInfo::inMenu)
	{
		
		MenuMenager::renderAll(&window);
	}

	window.display();
}

void Game::wait()
{
	static int maxFPS2 = maxFPS;
	static int FPS = 0;
	static clock_t start = clock();
	static int time;
	static int zegar = clock();
	float delay = 1000.0f / maxFPS;

	time = clock() - start;
	

	if (delay > time)
	{
		Sleep(delay - time);
	}
	FPS++;

	if ((clock() - zegar) > 1000)
	{
		std::cout << FPS << std::endl;

		FPS = 0;
		zegar = clock();
	}

	deltaTime = (clock() - start);
	start = clock();
}


Game::~Game()
{

}
