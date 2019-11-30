#pragma once
#include"Matrix.h"
class Player
{
private:
	int pawn;
	Matrix* matrix;
	
public:
int count;
	Player();
	Player(int pawn, Matrix* matrix);
	void play(int x, int y);
	int get_pawn();

};

