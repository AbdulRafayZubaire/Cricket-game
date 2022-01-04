#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "player.h"
#include "team.h"
using namespace std;

int main() {

	bool toss;
	bool userToss;
	Team alpha;

	cout << "Heads or Tails ?" << endl;
	cout << "1. Heads" << endl;
	cout << "2. Tails" << endl;
	cout << "Enter your choice: ";
	cin >> userToss;

	toss = alpha.gameToss();

	if (userToss == toss) {
		cout << "Congratulations! You won the toss.. Would you like to bat or bowl ? " << endl;
	}
	else {
		cout << "Sorry, You lost the toss..The opponent has chosen to bat. " << endl;
	}


	bool flag = 0;
	do {
		cout << "**Welcome**" << endl;
		int option;
		cout << "Select an option(1-3): " << endl;
		cout << "1. Play" << endl;
		cout << "2. Rules" << endl;
		cout << "3. Exit" << endl;

		cout << "Your choice: ";
		cin >> option;
		system("CLS");				// screen clear


		switch (option) {
		case 1: {
			int team;
			cout << "Select your team from the following." << endl;
			cout << setw(15) << "1. Pakistan" << endl;
			cout << setw(16) << "2. Australia" << endl;
			cout << setw(18) << "3. New Zealand" << endl;
			cout << setw(15) << "4. Zimbabwe" << endl;
			cout << setw(15) << "5. Srilanka" << endl;

			cout << "your choice: ";
			cin >> team;

			//system("CLS");			// screen clear

			alpha.setPlayers(team - 1);

			alpha.display();

		}
		case 2: {

		}
		case 3: {
			cout << "Thank you" << endl;
			break;
		}
		}


	} while (flag);












	system("pause");
	return 0;
}
