#pragma once
#include"Matrix.h"
#include"Player.h"
class Game
{
private:
	Matrix *matrix;
	Player *player1;
	Player *player2;

public:
	Game();

	Matrix *get_matrix();
	Player* get_player1();
	Player* get_player2();
	bool  checkTheEnd();
};

