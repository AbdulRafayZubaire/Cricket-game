#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;


class Player {
private:
	string name;
	string category;
	int runs;
	int bowlerRuns;
	int wickets;

public:
	void setName(string);
	string getName();
	void setCategory(string);
	string getCategory();
	void addRuns(int);
	int getRuns();
	void addBowlerRuns(int);
	int getBowlerRuns();
	void addWickets();
	int getWickets();
	Player();
};

// constructor for the class Player
Player::Player() {
	this->name = '\0';
	this->category = '\0';
	this->runs = NULL;
	this->wickets = NULL;
	this->bowlerRuns = NULL;
}

// Add Bowler Runs
void Player::addBowlerRuns(int runs) {

	this->bowlerRuns += runs;
}
int Player::getBowlerRuns() {

	return this->bowlerRuns;
}

// wickets function
void Player::addWickets() {
	this->wickets += 1;
}

// get wickets function
int Player::getWickets() {

	return this->wickets;
}


// runs adder function
void Player::addRuns(int runs) {

	this->runs += runs;
}

// runs getter
int Player::getRuns() {

	return this->runs;
}

// set name for player
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