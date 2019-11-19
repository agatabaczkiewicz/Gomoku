#include <SFML/Graphics.hpp>

#include<Windows.h>
#include <string>
#include <iostream>
#include <algorithm>
#include"Board.h"
using namespace std;


Board::Board(sf::RenderWindow* window, int size, int width, int height)
{
	this->window = window;
	this->window->setFramerateLimit(10);
	this->width = width;
	this->height = height;
	this->size = size;

	//wczytuje pliki
	if (!textureCell.loadFromFile("whiterect.jpg"))
	{
		std::cout << "error loading the sprite";
	}
	if (!textureBlackCell.loadFromFile("blackcell.jpg"))
	{
		std::cout << "error loading the sprite";
	}
	
	if (!textureBackground.loadFromFile("background.jpg"))
	{
		std::cout << "error loading the sprite";
	}
	pCellTexture = &textureCell;
	pBlackCellTexture = &textureBlackCell;
	
	pBackgroundTexture = &textureBackground;
	}

void Board::generateCells()
{
	cells = std::vector<sf::RectangleShape>();
	alreadyCliked = std::vector<int>();

	cout << this->size << endl;
	float y = (0.03125 / size) * height;
	for (int i = 0; i < size; i++)
	{
		float x = (0.03125 / size) * height;
		for (int j = 0; j < size; j++)
		{
			sf::RectangleShape rectangle;
			rectangle.setSize(sf::Vector2f(((float)0.9375 / size) * width, ((float)0.9375 / size) * height));
			rectangle.setPosition(x, y);
			rectangle.setTexture(pCellTexture);
			cells.push_back(rectangle);
			x += (((float)1 / size) * height);
		}
		y += (((float)1 / size) * height);
	}
}
void Board::mouseClick(int& xClicked, int& yClicked)
{
	int width = this->width;
	int height = this->height;
	sf::Vector2i localPosition = sf::Mouse::getPosition(*(this->window));
	for (size_t i = 0; i < cells.size(); i++)
	{

		if (localPosition.x > cells[i].getPosition().x&& localPosition.x < cells[i].getPosition().x + cells[i].getLocalBounds().width
			&& localPosition.y > cells[i].getPosition().y&& localPosition.y < cells[i].getPosition().y + cells[i].getLocalBounds().height
			&& !(std::find(alreadyCliked.begin(), alreadyCliked.end(), i) != alreadyCliked.end()))
		{
			
		
				cells[i].setTexture(pBlackCellTexture);
		
			this->alreadyCliked.push_back(i);

			xClicked = i % size;
			yClicked = i / size;
			yClicked = ((size - 1) - yClicked);
		}
	}
}
sf::RenderWindow* Board::getWindow()
{
	return window;
}

void Board::setSize(int size)
{
	this->size = size;
}


void Board::renderGame()
{
	generateMenu();
	window->draw(background);
	for (sf::RectangleShape r : cells) {
		window->draw(r);
	}
}

void Board::generateMenu() {

	int width = this->width;
	int height = this->height;

	int y = (0.5) * height;
	int x = (0.5) * width;

	font.loadFromFile("micross.ttf");
	t1 = sf::Text("GRAJ!!", font);
	t1.setFillColor(sf::Color::White);
	t1.setStyle(sf::Text::Bold | sf::Text::Underlined);
	t1.setCharacterSize(60);
	t1.setStyle(sf::Text::Bold);
	t1.setPosition(sf::Vector2f(0.35 * width - 0.5 * t2.getLocalBounds().width, 0.5 * height - (0.5 * t2.getLocalBounds().height)));

	sf::RectangleShape background;
	background.setSize(sf::Vector2f(width, height));
	background.setPosition(0, 0);
	background.setTexture(pBackgroundTexture);
	this->background = background;


}
void Board::renderMenu() {
	window->draw(background);
	window->draw(t1);
	//window->draw(fromfile);
}
void Board::mouseMenu(int& xClicked, int& yClicked,int& view) {
	int width = this->width;
	int height = this->height;

	sf::Vector2i localPosition = sf::Mouse::getPosition(*(this->window));
	if (localPosition.x > t1.getPosition().x&& localPosition.x < t1.getPosition().x + t1.getGlobalBounds().width
		&& localPosition.y > t1.getPosition().y&& localPosition.y < (t1.getPosition().y + t1.getGlobalBounds().height))
	{
		t1.setFillColor(sf::Color::Magenta);
		view = 1;
	}
}