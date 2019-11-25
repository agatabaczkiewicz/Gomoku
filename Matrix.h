#pragma once
class Matrix
{
private:
	int size;
	int moveX, moveY;
	int numberofpawns;

public:
	int** matrix;
	Matrix();
	Matrix(int size);
	
	void martix_generator();
	int** get_matrix();
	void reset_matrix();
	bool is_0(int x, int y);
	bool noMoreMoves();
	void set_field(int x,int y, int pawn);
	void print_matrix();
	int where_moveX();
	int where_moveY();

};

