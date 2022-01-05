#include <iostream>
#include <string>
#include <fstream>
#include "player.h"
#include "team.h"
#include "batting.h"

using namespace std;

// Function prototypes
bool isStrike();
string bowl();
int Bat(string, Team*, Team*);
int out(Team*);

// -----------------------------------------------


int main() {

	bool toss;
	bool userToss;
	Team alpha, comp;

	Team *battingTeam, *bowlingTeam;
	Player* batsman, * bowler;




	cout << "Heads or Tails ?" << endl;
	cout << "1. Heads" << endl;
	cout << "2. Tails" << endl;
	cout << "Enter your choice: ";
	cin >> userToss;
 
	
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

			alpha.setName(team);

			//system("CLS");			// screen clear

			alpha.setPlayers(team - 1);

			alpha.display();

			// Toss for the game
			toss = alpha.gameToss(userToss, comp);


// ------------- Setting the Batting and Bowling pointers accordingly -----------

			if (alpha.getInnings()) {		// if alpha chooses to bat			
				battingTeam = &alpha;
				//batsman = battingTe
				bowlingTeam = &comp;
			}
			else {
				battingTeam = &comp;
				bowlingTeam = &alpha;
			}
		
			for (int i = 0; i < 10; i++) {
				// calling the balling function
				string ball = bowl();

				// calling the batting function
				int wickets = Bat(ball, battingTeam, bowlingTeam);
			}
		}









// ------------------------------------------- RULES -----------------------------------------
		case 2: {

		}
// ------------------------------------------- QUIT ------------------------------------------
		case 3: {
			cout << "Thank you" << endl;
			break;
		}
		}


	} while (flag);












	system("pause");
	return 0;
}

// -------------------------------- Automoatic (computer) batting functions ---------------------------------

bool isStrike() {					// if function returns 1 than score will be incremented according
									// to the rules if it returns 0 no score will be incremented
	bool random;
	random = rand() % 2;
	return random;
}

int Bat(string ball, Team *battingTeam, Team *bowlingTeam) {
	
	cout << " -> To strike press 1" << endl;
	cout << " -> To leave press 2" << endl;

		if (isStrike()) {

			if (out(battingTeam)) {
				return 1;
			}

			if (ball == "bouncer") {			// bouncer
				battingTeam->addRuns(6);
				// *batsman.runs += 6;
				// *bowler.runs += 6;
				return 0;
			}

			else if (ball == "noBall") {			// no ball
				int boundary[2] = { 4, 6 };

				random = rand() % 2;
				battingTeam->addRuns(boundary[random]);
				// *batsman.runs += boundary[random];
				// *bowler.runs += boundary[random];
				return 0;
			}
			else if (ball == "wide") {			// wide
				battingTeam->addRuns(4);
				// *batsman.runs += 4;
				// *bowler.runs += 4;
				return 0;
			}
			else if (ball == "spin") {			// spin
				int score[5] = { 0, 1, 2, 4, 6 };

				random = rand() % 5;
				battingTeam->addRuns(score[random]);
				// *batsman.runs += score[random];
				// *bowler.runs += score[random];
				return 0;
			}
		}
		else {
			battingTeam->addRuns(0);
			return 0;
		}
}

// bowling function
string bowl() {

	string bowl[4] = { "bouncer", "noBall", "wide", "spin" };

	random = rand() % 4;

	return bowl[random];

}


// wicket increment function
int out(Team *battingTeam)
{
	srand(time(0));
	int out = rand() % 5;
	if (out == 0)
	{
		battingTeam->addWicket();
		return 1;
	}
	return 0;
}
