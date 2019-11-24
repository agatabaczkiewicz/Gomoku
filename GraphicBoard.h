#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
#include<Windows.h>
#include"Matrix.h"
#include"Game.h"
using namespace std;

class GraphicBoard
{
private:
	vector<sf::RectangleShape> cells;
	vector<int> alreadyCliked;
	sf::RenderWindow* window;
	int width;
	int height;
	int size;
	Game *game;
	Matrix* tabl;
	

	sf::RectangleShape background;
	sf::Text t1;
	sf::Text t2;
	sf::Font font;

	sf::Texture textureCell;
	const sf::Texture* pCellTexture;

	sf::Texture textureBlackCell;
	const sf::Texture* pBlackCellTexture;

	sf::Texture textureBackground;
	const sf::Texture* pBackgroundTexture;

public:
	GraphicBoard(sf::RenderWindow* window, int size, int width, int height);
	sf::RenderWindow* getWindow();
	void generateCells();
	void setSize(int size);
	void generateMenu();
	void renderMenu();
	void renderGame();
	void mouseClick(int& xClicked, int& yClicked);
	void mouseMenu(int& xClicked, int& yClicked, int& view);
};

