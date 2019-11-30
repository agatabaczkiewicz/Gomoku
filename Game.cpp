#include "Game.h"

Game::Game()
{
	this->matrix = new Matrix(9);
	this->player1 = new Player(1, this->matrix);
	this->player2 = new Player(2,this->matrix);
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

bool Game::checkTheEnd()
{
	int** tab = this->matrix->get_matrix();
	int x = this->matrix->where_moveX();
	int y = this->matrix->where_moveY();
	int counter = 1;	// counter of the linked stones
	int* piece = &tab[x][y]; // the last placed piece to be checked

	/* horizontal line stones count */
	while (y > 0)	// counting backward 
	{
		y--;
		if (tab[x][y] == *piece) {
			counter++;	// if the left stone of the current are the same than p1, increment counter
		}
		else {
			break;	// if the left stone of the current are different than p1, exit the loop 
		}
	}

	if (counter >= 5) {
		this->matrix->reset_matrix();
		counter = 0;
		return true;	//check if there are already 5 stones in a line
	}

	y = this->matrix->where_moveY();	// reset the vertical axis 
	while (y < 8)	// counting forward
	{
		y++;
		if (tab[x][y] == *piece) {
			counter++;	// if the right stone of the current are the same than p1, increment counter
		}
		else {
			break;	// if the right stone of the current are different than p1, exit the loop 
		}
	}

	if (counter == 5) {
		this->matrix->reset_matrix();
		return true;
	}
	/* horizontal line stones count */

	/* vertical line stones count */
	counter = 1;	// reset the counter
	y = this->matrix->where_moveY();	// reset the vertical axis 
	while (x > 0)	// counting upward 
	{
		x--;
		if (tab[x][y] == *piece) {
			counter++;
		}
		else {
			break;
		}
	}

	if (counter == 5) {
		this->matrix->reset_matrix();
		counter = 0;
		return true;
	}

	x = this->matrix->where_moveX();	// reset the axis 
	while (x < 8)	// counting downward
	{
		x++;
		if (tab[x][y] == *piece) {
			counter++;
		}
		else {
			break;
		}
	}

	if (counter == 5) {
		this->matrix->reset_matrix();
		counter = 0;
		return true;
	}
	/* vertical line stones count */

	/* left diagonal lines stones count */
	counter = 1;	// reset the counter
	x = this->matrix->where_moveX();	// reset the axis 
	while (x > 0 && y > 0)	// counting left upper incline 
	{
		x--;
		y--;
		if (tab[x][y] == *piece) {
			counter++;
		}
		else {
			break;
		}
	}

	if (counter == 5) {
		this->matrix->reset_matrix();
		counter = 0;
		return true;
	}

	x = this->matrix->where_moveX();	// reset the axis
	y = this->matrix->where_moveY();	// reset the vertical axis
	while (x < 8 && y <8)	// counting downward
	{
		x++;
		y++;
		if (tab[x][y] == *piece) {
			counter++;
		}
		else {
			break;
		}
	}

	if (counter == 5) {
		this->matrix->reset_matrix();
		counter = 0;
		return true;
	}
	/* left diagonal line stones count */

	/* right diagonal lines stones count */
	counter = 1;	// reset the counter
	x = this->matrix->where_moveX();	// reset the axis
	y = this->matrix->where_moveY();	// reset the vertical axis
	while (y > 0 && x < 8)	// counting left
	{
		x++;
		y--;
		if (tab[x][y] == *piece) {
			counter++;
		}
		else {
			break;
		}
	}

	if (counter == 5) {
		this->matrix->reset_matrix();
		counter = 0;
		return true;
	}

	x = this->matrix->where_moveX();	// reset the axis
	y = this->matrix->where_moveY();	// reset the vertical axis
	while (x > 0 && y < 8)	// counting right
	{
		x--;
		y++;
		if (tab[x][y] == *piece) {
			counter++;
		}
		else {
			break;
		}
	}

	if (counter == 5) {
		this->matrix->reset_matrix();
		counter = 0;
		return true;
	}
	return false;
}