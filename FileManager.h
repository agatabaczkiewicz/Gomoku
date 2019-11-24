#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
#include<Windows.h>
#include<sstream>
#include<fstream>
#include <string>

using namespace std;

class FileManager {
private:
	string name;
	int score;
	string date;
	string result;
public:
	FileManager();
	void tovector(int score, string name, string date);
	void AddToFile(string name, int number_of_moves);
	string ShowFile();
};