#include "Player.h"
#include "Game.h"
#include<iostream>

Player::Player(int pawn, Matrix* matrix)
{
	this->pawn = pawn;
	this->matrix = matrix;
	this->count = 0;
}
void Player::play(int x, int y)
{
	matrix->set_field(x, y, this->pawn);
	matrix->print_matrix();
	count++;
	std::cout <<std::endl<< "XXX  " << count << std::endl;
}
int Player::get_pawn()
{
	return this->pawn;
}