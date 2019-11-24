#include "Game.h"

Game::Game()
{
	this->matrix = new Matrix(9);
	this->player1 = new Player(1);
	this->player2 = new Player(2);
	matrix->print_matrix();
}
Matrix* Game::get_matrix()
{
	return this->matrix;
}

Player* Game::get_player1()
{
	return this->player1;
}

Player* Game::get_player2()
{
	return this->player2;
}