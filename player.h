#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;


class Player {
private:
	string name;
	string category;
	//int runs;
	//int wickets;
	static int number;

public:
	void setName(string);
	string getName();
	void setCategory(string);
	string getCategory();

};
int Player::number = 1;					// static member


void Player::setName(string name) {
	this->name = name;
}

// get name function
string Player::getName() {
	return this->name;
}

// set category function
void Player::setCategory(string category) {
	this->category = category;
}

// get category function
string Player::getCategory() {

	return this->category;
}