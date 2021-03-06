#include "Matrix.h"
#include "GraphicBoard.h"
#include<iostream>

Matrix::Matrix()
{

}
Matrix::Matrix(int size)
{
	this->size = size;
	martix_generator();
	reset_matrix();
}

void Matrix::martix_generator()
{
	this->numberofpawns = 0;
	this->matrix = new int* [size];
	for (int i = 0; i < size; ++i)
	{
		matrix[i] = new int[size];
	}
}

void Matrix::reset_matrix()
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			this->matrix[i][j] = 0;
		}
	}
}
bool Matrix::is_0(int x,int y)
{
	return this->matrix[x][y] == 0;
}

void Matrix::set_field(int x, int y, int pawn)
{
	this->matrix[x][y] = pawn;

	this->numberofpawns += 1;
	//cout << this->numberofpawns << " ";
	this->moveX = x;
	this->moveY = y;


}
int** Matrix::get_matrix()
{
	return this->matrix;
}
void Matrix::print_matrix()
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			std::cout << this->matrix[i][j] << "  ";
		}
		std::cout << std::endl;
	}
}
int Matrix::where_moveX(){
	return this->moveX;
}
int Matrix::where_moveY() {
	return this->moveY;
}
bool Matrix::noMoreMoves() {
	return this->numberofpawns == 81;

}