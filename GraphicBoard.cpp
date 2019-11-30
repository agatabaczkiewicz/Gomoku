#include <SFML/Graphics.hpp>

#include<Windows.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <stdexcept>

#include"GraphicBoard.h"
#include"Matrix.h"
#include"FileManager.h"
#include"Game.h"
#include"Player.h"
using namespace std;


GraphicBoard::GraphicBoard(sf::RenderWindow* window, int size, int width, int height)
{
	this->window = window;
	this->window->setFramerateLimit(10);
	this->width = width;
	this->height = height;
	this->size = size;
	this->game = new Game();
	round = game->get_player1();

	//wczytuje pliki

	if (!textureCell.loadFromFile("whiterect.jpg"))
	{
		
		throw("CANNOT OPEN THE FILE whiterect.jpg ");
	}
	if (!textureBlackCell.loadFromFile("blackcell.jpg"))
	{
		throw("CANNOT OPEN THE FILE blackcell.jpg");
	}
	
	if (!textureBackground.loadFromFile("background.jpg"))
	{
		throw("CANNOT OPEN THE FILE background.jpg");
	}
	if (!textureLogo.loadFromFile("logo.jpg"))
	{
		throw("CANNOT OPEN THE FILE logo.jpg");
	}
	if (!textureplay.loadFromFile("garj.jpg"))
	{
		throw("CANNOT OPEN THE FILE garj.jpg");
	}
	if (!textureRanking.loadFromFile("ranking.jpg"))
	{
		throw("CANNOT OPEN THE FILE ranking.jpg");
	}
	if (!textureOrangeCell.loadFromFile("orange.jpg"))
	{
		throw("CANNOT OPEN THE FILE orange.jpg");
	}



	pCellTexture = &textureCell;
	pBlackCellTexture = &textureBlackCell;
	pOrangeCellTexture = &textureOrangeCell;
	pLogoTexture = &textureLogo;


	pBackgroundTexture = &textureBackground;
	pPlayTexture = &textureplay;
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
void GraphicBoard::mouseClick(int& xClicked, int& yClicked,int&view)
{
	int width = this->width;
	int height = this->height;
	int mov;
	sf::Vector2i localPosition = sf::Mouse::getPosition(*(this->window));
	for (size_t i = 0; i < cells.size(); i++)
	{

		if (localPosition.x > cells[i].getPosition().x&& localPosition.x < cells[i].getPosition().x + cells[i].getLocalBounds().width
			&& localPosition.y > cells[i].getPosition().y&& localPosition.y < cells[i].getPosition().y + cells[i].getLocalBounds().height
			&& !(std::find(alreadyCliked.begin(), alreadyCliked.end(), i) != alreadyCliked.end()))
		{
		

				
			this->alreadyCliked.push_back(i);

			xClicked = i % size;
			yClicked = i / size;
			yClicked = ((size - 1) - yClicked);

			yClicked = abs(8-yClicked);
			tabl = game->get_matrix();
      
			round->play(yClicked, xClicked);

			if (round == game->get_player1())
			{ 
				cells[i].setTexture(pBlackCellTexture);
				round = game->get_player2();

			}
			else if (round == game->get_player2())
			{
				cells[i].setTexture(pOrangeCellTexture);
				round = game->get_player1();
      }
	//tabl->numberofpawns = 81;
			if (game->checkTheEnd()) {
				mov = round->count;
				cout << mov;
				game->get_player1()->count = 0;
				game->get_player2()->count = 0;
				tabl->numberofpawns = 0;
			//	try {
					theEndWindow("The end has come", "\t\tYOU WIN!!!\nWe are so proud of you", 500, 400, mov);
			//	}
			//	catch (const char* msg) {
			//		cout << msg;
			//	}
				view = 0;
			}
		
			else if (tabl->noMoreMoves()) {
				tabl->numberofpawns = 0;
				theEndWindow("The end has come", "\t\t\t\t\tOH NO!\n\tTHERE IS NO MORE MOVES\nPRESS ENTER TO GO TO MENU", 500, 400,0);
				view = 0;
			}
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
	graj.setPosition((x - 110), y - 25);
	graj.setTexture(pPlayTexture);
	playclick = graj;


	// -(0.5 * t2.getLocalBounds().height)));
	sf::RectangleShape ran;
	ran.setSize(sf::Vector2f(200, 100));
	ran.setPosition((x - 100), y + 40);
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
		&& localPosition.y > playclick.getPosition().y&& localPosition.y < (playclick.getPosition().y + playclick.getGlobalBounds().height) && view != 2)
	{
	
		view = 1;
	}
	else if (localPosition.x > rankingclick.getPosition().x&& localPosition.x < rankingclick.getPosition().x + rankingclick.getGlobalBounds().width
		&& localPosition.y > rankingclick.getPosition().y&& localPosition.y < (rankingclick.getPosition().y + rankingclick.getGlobalBounds().height)) {

		view = 2;
	}
	else if (localPosition.x > t4.getPosition().x&& localPosition.x < t4.getPosition().x + t4.getGlobalBounds().width
		&& localPosition.y > t4.getPosition().y&& localPosition.y < (t4.getPosition().y + t4.getGlobalBounds().height) && view == 2) {

		view = 0;
	}
}
void GraphicBoard::generateRanking() {
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
	t3.setPosition(sf::Vector2f(0.3 * width, 0.1 * height));
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

void GraphicBoard::theEndWindow(string title,string message, int width, int height,int mov) 
{
		sf::RenderWindow popupWindow(sf::VideoMode(width, height), title, sf::Style::Titlebar | sf::Style::Close);
		popupWindow.setFramerateLimit(10);

		sf::String playerInput;
		

		// Create a text
		sf::Font font;
		font.loadFromFile("micross.ttf");
		sf::Text text(message, font);
		text.setFillColor(sf::Color::Black);
		text.setStyle(sf::Text::Bold | sf::Text::Underlined);
		text.setCharacterSize(30);
		text.setStyle(sf::Text::Bold);
		text.setPosition(sf::Vector2f(0.5 * width - 0.5 * text.getLocalBounds().width, 0.2 * height));

		font.loadFromFile("micross.ttf");
		sf::Text text2("Give us youre nick to ranking table", font);
		text2.setFillColor(sf::Color::Black);
		text2.setStyle(sf::Text::Bold | sf::Text::Underlined);
		text2.setCharacterSize(20);
		text2.setStyle(sf::Text::Bold);
		text2.setPosition(sf::Vector2f(0.5 * width - 0.5 * text2.getLocalBounds().width, 0.5 * height));


		sf::Text playerText("",font);
		playerText.setFillColor(sf::Color::Black);
		playerText.setStyle(sf::Text::Bold | sf::Text::Underlined);
		playerText.setCharacterSize(15);
		playerText.setStyle(sf::Text::Bold);
		playerText.setPosition(sf::Vector2f(0.45 * width , 0.6*height));
		
		// run the program as long as the window is open
		while (popupWindow.isOpen())
		{
			sf::Event event;
			//popupWindow.clear(sf::Color(255, 255, 255));
			while (popupWindow.pollEvent(event))
			{
				if (mov != 0) {
					if (event.type == sf::Event::TextEntered)
					{
						if (event.text.unicode == '\b') // handle backspace explicitly
						{
							playerInput.erase(playerInput.getSize() - 1, 1);
							playerText.setString(playerInput);
						}
						else if (event.text.unicode < 128 && event.text.unicode != '\b')
						{
							playerInput += (char)event.text.unicode;
							cout << event.text.unicode << " ";

							playerText.setString(playerInput);
						}
						else if (event.text.unicode >= 128)throw"THIS SIGN IS NOT ALLOWED!";

					}
				}

				if (event.type == sf::Event::Closed)
					popupWindow.close();
				else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Enter))
					popupWindow.close();
			}


			popupWindow.clear(sf::Color(255, 255, 255));
			popupWindow.draw(text);
			if (mov != 0) {
				popupWindow.draw(text2);
				popupWindow.draw(playerText);
			}
			popupWindow.display();
		}
		if (mov != 0) {
			string s = playerInput;
			FileManager wwww;
			if (s == "")
				s = "Anonim";
	
				wwww.AddToFile(s, mov);
			
			
		}
	}
			




