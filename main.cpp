#include <SFML/Graphics.hpp>
#include<iostream>
#include<Windows.h>
#include"Board.h"
using namespace std;
int main()
{
	int grid_size = 9;
	int windowWidth = 800;
	int windowHeight = 800;
	int xClicked = 999;
	int yClicked = 999;
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Gomoku Game", sf::Style::Titlebar | sf::Style::Close);
	Board grm(&window, grid_size, windowWidth, windowHeight);
	grm.generateCells();
	grm.generateMenu();
	int view = 0; //0-menu,1-gra
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
			if (view == 1) {
				if (event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonPressed)
				{

					grm.mouseClick(xClicked, yClicked);
				}
			}
			else if (view == 0) {
				if (event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonPressed)
				{
					grm.mouseMenu(xClicked, yClicked, view);
					grm.generateCells();
				}
			}
		}

		window.clear();
		if(view==0)
			grm.renderMenu();
		else
			grm.renderGame();
		window.display();
	}
	return 0;
}