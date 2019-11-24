#include <SFML/Graphics.hpp>

#include<Windows.h>
#include <string>
#include <iostream>
#include <algorithm>
#include<sstream>
#include<fstream>
#include <string>
#include<time.h>
#include"FileManager.h"

using namespace std;


FileManager::FileManager() {}

void FileManager::tovector(int score, string name, string date) {
	this->score = score;
	this->name = name;
	this->date = date;
}

string FileManager::ShowFile()
{
	fstream file;
	string line;
	vector<FileManager>toshow;
	FileManager help;
	int x;
	string y, z;
	file.open("ranking.txt", ios::in);
	if (file.good())
	{

		while (!file.eof()) {
			getline(file, line);
			stringstream change(line);
			change >> x;
			getline(file, line);
			y = line;
			getline(file, line);
			z = line;
			help.tovector(x, y, z);
			toshow.push_back(help);
			
		}

		file.close();
		
		int i = 0;
		sort(toshow.begin(), toshow.end(), [](FileManager& one, FileManager& two) {return one.score < two.score; });
		for (auto j = toshow.begin(); j < toshow.end(); j++) {
			string _str = std::to_string(j->score);
			//esult.append(_str);
			result.append(_str+"\t"+j->name+"\t"+j->date+"\n");
		//	cout << j->score << " " << j->name << " " << j->date << endl;
			if (i > 15)break;
			i++;
		}
		//cout << result;
	}
	return result;
}

void FileManager::AddToFile(string name, int number_of_moves) {
	fstream file;
	file.open("ranking.txt", ios::app);
	if (file.good()) {
		file <<endl<<number_of_moves<<endl<<name<<endl;
		struct tm e;
		time_t now = time(0);
		localtime_s(&e,&now);
		file << e.tm_mday << "." << e.tm_mon + 1 << "." << e.tm_year + 1900;
	}
	file.close();
}


