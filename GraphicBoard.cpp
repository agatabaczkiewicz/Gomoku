#include <SFML/Graphics.hpp>

#include<Windows.h>
#include <string>
#include <iostream>
#include <algorithm>
#include"GraphicBoard.h"
#include"FileManager.h"
using namespace std;


GraphicBoard::GraphicBoard(sf::RenderWindow* window, int size, int width, int height)
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
	if (!textureLogo.loadFromFile("logo.jpg"))
	{
		std::cout << "error loading the sprite";
	}
	if (!textureplay.loadFromFile("garj.jpg"))
	{
		std::cout << "error loading the sprite";
	}
	if (!textureRanking.loadFromFile("ranking.jpg"))
	{
		std::cout << "error loading the sprite";
	}
	pCellTexture = &textureCell;
	pBlackCellTexture = &textureBlackCell;
	pLogoTexture = &textureLogo;
	pBackgroundTexture = &textureBackground;
	pPlayTexture=&textureplay;
	pRankingTexture = &textureRanking;
	}

void GraphicBoard::generateCells()
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
void GraphicBoard::mouseClick(int& xClicked, int& yClicked)
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
sf::RenderWindow* GraphicBoard::getWindow()
{
	return window;
}

void GraphicBoard::setSize(int size)
{
	this->size = size;
}


void GraphicBoard::renderGame()
{
	generateMenu();
	window->draw(background);
	for (sf::RectangleShape r : cells) {
		window->draw(r);
	}
}

void GraphicBoard::generateMenu() {

	int width = this->width;
	int height = this->height;

	int y = (0.5) * height;
	int x = (0.5) * width;

	sf::RectangleShape graj;
	
	graj.setSize(sf::Vector2f(200, 100));
	graj.setPosition((x-110), y - 25);
	graj.setTexture(pPlayTexture);
	playclick = graj;

	
	// -(0.5 * t2.getLocalBounds().height)));
	sf::RectangleShape ran;
	ran.setSize(sf::Vector2f(200, 100));
	ran.setPosition((x - 100), y+40);
	ran.setTexture(pRankingTexture);
	rankingclick = ran;

	sf::RectangleShape logo;
	logo.setSize(sf::Vector2f(500, 200));
	logo.setPosition((x - 250), y - (0.3 * height));
	logo.setTexture(pLogoTexture);
	gamelogo = logo;


	sf::RectangleShape background;
	background.setSize(sf::Vector2f(width, height));
	background.setPosition(0, 0);
	background.setTexture(pBackgroundTexture);
	this->background = background;


}
void GraphicBoard::renderMenu() {
	window->draw(background);
	window->draw(gamelogo);
	window->draw(playclick);
	window->draw(rankingclick);
	//window->draw(fromfile);
}
void GraphicBoard::mouseMenu(int& xClicked, int& yClicked,int& view) {
	int width = this->width;
	int height = this->height;

	sf::Vector2i localPosition = sf::Mouse::getPosition(*(this->window));
	if (localPosition.x > playclick.getPosition().x&& localPosition.x < playclick.getPosition().x + playclick.getGlobalBounds().width
		&& localPosition.y > playclick.getPosition().y&& localPosition.y < (playclick.getPosition().y + playclick.getGlobalBounds().height)&&view!=2)
	{
		view = 1;
	}
	else if (localPosition.x > rankingclick.getPosition().x&& localPosition.x < rankingclick.getPosition().x + rankingclick.getGlobalBounds().width
		&& localPosition.y > rankingclick.getPosition().y&& localPosition.y < (rankingclick.getPosition().y + rankingclick.getGlobalBounds().height)) {
	
		view = 2;
	}
	else if (localPosition.x > t4.getPosition().x&& localPosition.x < t4.getPosition().x + t4.getGlobalBounds().width
		&& localPosition.y > t4.getPosition().y&& localPosition.y < (t4.getPosition().y + t4.getGlobalBounds().height)&&view==2) {
		
		view = 0;
	}


}
void GraphicBoard::generateRanking(){
	int width = this->width;
	int height = this->height;

	string hhh;
	FileManager www;
	hhh = www.ShowFile();
	//cout << hhh;

	font.loadFromFile("micross.ttf");
	t3 = sf::Text(hhh, font);
	t3.setFillColor(sf::Color::White);
	t3.setStyle(sf::Text::Bold | sf::Text::Underlined);
	t3.setCharacterSize(20);
	t3.setStyle(sf::Text::Bold);
	t3.setPosition(sf::Vector2f(0.3 * width, 0.1*height));
	// -(0.5 * t2.getLocalBounds().height)));
	
	t4 = sf::Text("MENU", font);
	t4.setFillColor(sf::Color::White);
	t4.setStyle(sf::Text::Bold | sf::Text::Underlined);
	t4.setCharacterSize(20);
	t4.setStyle(sf::Text::Bold);
	t4.setPosition(sf::Vector2f(0.7 * width, 0.8 * height));

}

void GraphicBoard::renderRanking() {
	window->draw(background);
	window->draw(t3);
	window->draw(t4);
}
