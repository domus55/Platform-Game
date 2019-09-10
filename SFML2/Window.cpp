#include "Window.h"

std::vector < std::shared_ptr < sf::RenderWindow > > Window::window;

void Window::createWindow()
{
	Window::window.push_back(std::make_shared <sf::RenderWindow>(sf::VideoMode(1600, 900, 32), "Game", sf::Style::Close) );
}
