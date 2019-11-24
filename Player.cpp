#include "Player.h"
#include "Game.h"

Player::Player(int pawn, Matrix* matrix)
{
	this->pawn = pawn;
	this->matrix = matrix;
}
void Player::play(int x, int y)
{
	matrix->set_field(x, y, this->pawn);
	matrix->print_matrix();
}
int Player::get_pawn()
{
	return this->pawn;
}