#pragma once
#include "player.h"
#include <time.h>


class Team {
private:
	string name;
	Player squad[16] = {};					// complete 16 member squad
	Player beta[11] = {};					// Final playing 11 member squad
	//int totalRuns;
	//int wickets;
	//int overs;
	//bool toss;


public:
	//compisition
	//Player alpha;

	void setPlayers(int);
	//string getplayers();
	void swap(int, int);
	void playingOrder();
	void display();
	void displaySquad();
	bool gameToss();
	void setName(string);
};


void Team::setName(string name) {
	this->name = name;
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
bool Team::gameToss() {
	srand(time(0));

	int random = rand() % 2;

	if (random == 0) {
		return 0;
	}
	else
		return 1;
}