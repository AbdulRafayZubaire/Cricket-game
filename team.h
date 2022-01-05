#pragma once
#include "player.h"
#include <time.h>
#include <iomanip>


class Team {
private:
	string name;
	Player squad[16] = {};					// complete 16 member squad
	Player beta[11] = {};					// Final playing 11 member squad
	int totalRuns;
	int wickets;
	//int overs;
	bool toss;
	string firstIn;
	string secondIn;


public:

	void setPlayers(int);
	int getInnings();
	void swap(int, int);
	void playingOrder();
	void display();
	void displaySquad();
	bool gameToss(int, Team&);
	void setName(int);
	void addRuns(int);
	void addWicket();
	Player& getPlayer(int);
};


// get player reference function
Player& Team::getPlayer(int num) {
	
	return this->beta[num];
}

void Team::setName(int num) {
	if (num == 1) {
		this->name = "Pakistan";
	}
	else if (num == 2) {
		this->name = "Australia";
	}
	else if (num == 3) {
		this->name = "New Zealand";
	}
	else if(num == 4) {
		this->name = "Zimbabwe";
	}
	else{
		this->name = "Sri Lanka";
	}
}

// setting Innings
int Team::getInnings() {
	if (this->firstIn == "Bat") {
		return 1;
	}
	else
		return 0;
}

// set player member function
void Team::setPlayers(int t) {

	int team = t;
	char choice;
	string line;

	fstream file;
	file.open("players.txt", ios::in);

	int i = 0;
	int limit = (team * 16);
	int count = 0;

	if (file.is_open()) {
		while (getline(file, line)) {
			if (count >= limit && count < (limit + 16)) {
				cout << i + 1 << ". " << line << endl;

				//name assignation
				squad[i].setName(line);

				// category assignation
				if (i <= 5) {
					squad[i].setCategory("Batsman");
				}
				else if (i <= 8) {
					squad[i].setCategory("All-rounder");
				}
				else if (i <= 14) {
					squad[i].setCategory("Bowler");
				}
				else {
					squad[i].setCategory("Wicket-Keeper");
				}
				i++;
			}
			count++;
		}
	}
	file.close();

	cout << "Select Your final playing 11: " << endl;


	int index = 0;
	for (int i = 0; i < 11; i++)
	{
		cout << "Player " << i + 1 << ": ";
		cin >> index;

		// validation for repeated selection of a player
		for (int j = 0; j < i; j++)
		{
			while (squad[index - 1].getName() == beta[j].getName()) {
				cout << "\t\t\t!--WARNING--! -> You cannot select the same player twice" << endl;
				cout << "Player " << i + 1 << ": ";
				cin >> index;
			}
		}

		// shortlisting the playing 11 from the 16 member squad
		beta[i] = squad[index - 1];

		//cout << beta[i].getName() << endl;
	}

	display();			// displaying the final 11

	cout << "Do you want to modify the batting order (Y/N)? : ";
	cin >> choice;
	do {

		while (choice != 'y' && choice != 'Y' && choice != 'N' && choice != 'n') {
			cout << "------- Invalid choice -------";
			cout << "Do you want to modify the batting order (Y/N)? : ";
			cin >> choice;
		}

		if (choice == 'y' || choice == 'Y') {

			// function calling for adjusting the playing order
			playingOrder();
		}

		//display();

		cout << "Do you want to modify the batting order again (Y/N)? : ";
		cin >> choice;
	} while (choice == 'y' || choice == 'Y');
}


//string Players::getplayers() {
//
//}

void Team::playingOrder() {

	int id = 0, place = 0;

	cout << "Enter the player ID you want to switch: ";
	cin >> id;
	cout << "Enter the position you want to switch with: ";
	cin >> place;

	// players swapping function called 
	swap(id, place);
}

// playing 11 swapping function called[;p
void Team::swap(int id, int place) {

	string temp = beta[place - 1].getName();
	beta[place - 1] = beta[id - 1];
	beta[id - 1].setName(temp);
}

// playing 11 display function
void Team::display() {

	for (int i = 0; i < 11; i++)
	{
		cout << i + 1 << ". " << beta[i].getName();
		cout << setw(15) << "  (" << beta[i].getCategory() << ")" << endl;

	}
}

// complete squad display function 
void Team::displaySquad() {

	for (int i = 0; i < 16; i++)
	{
		cout << i + 1 << ". " << squad[i].getName() << endl;
	}
}

// TOSS
bool Team::gameToss(int userToss, Team &comp) {
	srand(time(0));

	int random = rand() % 2;
	cout << random;

	if (random == 0) {
		this->toss = 0;
		comp.toss = 1;
	}
	else
		this->toss = 1;
		comp.toss = 0;

	if (userToss == this->toss) {
		int choice;
		cout << "Congratulations! You won the toss.. Would you like to bat or bowl ? " << endl;
		cout << "1. Bat\n2. Ball" << endl;
		
		cout << "Your choice";
		cin >> choice;
		if (choice == 1) {
			this->firstIn = "Bat";
			this->secondIn = "Ball";
		}
		else{
			comp.firstIn = "Ball";
			comp.secondIn = "Bat";
		}
	}
	else {
		cout << "Sorry, You lost the toss..The opponent has chosen to bat. " << endl;

	}

	return random;
}

void Team::addRuns(int runs) {
	this->totalRuns += runs;
}

void Team::addWicket() {
	this->wickets = +1;
}