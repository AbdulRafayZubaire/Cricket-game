#include <stdlib.h>
#include "player.h"
#include "team.h"


// Function prototypes
bool isStrike();
int userStrike();
string bowl();
string userBowl();
int Bat(string, Team*, Team*, Player*, Player*);
int compBat(string, Team*, Team*, Player*, Player*);
void displayScoreCard(Team*, Team*, Player*, Player*);
int out(Team*);

// -----------------------------------------------


int main() {

	bool userToss;
	Team alpha, comp;

	Team *battingTeam = nullptr, *bowlingTeam = nullptr;
	Player *batsman, *bowler;
	string ball;




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
				// screen clear


		switch (option) {
		case 1: {
			int team;
			cout << "Select your team from the following." << endl;
			cout << setw(15) << "1. Pakistan" << endl;
			cout << setw(16) << "2. Australia" << endl;
			cout << setw(18) << "3. New Zealand" << endl;
			cout << setw(15) << "4. Zimbabwe" << endl;
			cout << setw(15) << "5. Srilanka" << endl;

			// Team selection
			cout << "your choice: ";
			cin >> team;
			alpha.setName(team);
			alpha.setPlayers(team - 1,"user");

			cout << "opponent team: ";
			cin >> team;
			comp.setName(team);
			comp.setPlayers(team - 1, "comp");

			//system("CLS");			// screen clear

			alpha.display();

			// Toss for the game
			alpha.gameToss(userToss, comp);


			// --------------- Setting the Batting and Bowling pointers accordingly ------------- //

			int in = 0;
			int proceed = 0;
			do {
				proceed++;
				if (in == 0) {
					if (alpha.getInnings() == "Bat") {		// if alpha chooses to bat			
						battingTeam = &alpha;
						bowlingTeam = &comp;
					}
					else {
						battingTeam = &comp;
						bowlingTeam = &alpha;
					}
				}
				else {
					if (alpha.getInnings() == "Bat") {		// if alpha chooses to bat			
						battingTeam = &comp;
						bowlingTeam = &alpha;
					}
					else{
						battingTeam = &alpha;
						bowlingTeam = &comp;
					}
				}


				int ballsBowled = 0;
				int wickets = 0;

				for (int i = 0; i < 10; i++) {

					// referencing to the current batsman and bowler
					batsman = &(battingTeam->getPlayer(wickets));
					bowler = &(bowlingTeam->getPlayer(ballsBowled / 6));

					// clear screeen
					system("cls");
					// Overall Display Fuction
					displayScoreCard(battingTeam, bowlingTeam, batsman, bowler);



					if (battingTeam == &alpha) {
						// calling the balling function
						ball = bowl();
						// calling the batting function
						wickets += Bat(ball, battingTeam, bowlingTeam, batsman, bowler);
					}

					else if (bowlingTeam == &alpha) {
						ball = userBowl();
						wickets += compBat(ball, battingTeam, bowlingTeam, batsman, bowler);

					}
					// incrementing the balls
					ballsBowled++;

					// a count to maintain the shifting of innings btw batting and bowling team

				}
				in++;
			} while (proceed < 2);					// do while loop
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




// is strike function for the user
int userStrike(){
	int strike;

	cout << " -> To strike press 1" << endl;
	cout << " -> To leave press 2" << endl;
	cin >> strike;
	while (strike != 1 && strike != 2) {
		cout << "------- Invalid choice -------";
		cout << " -> To strike press 1" << endl;
		cout << " -> To leave press 2" << endl;
		cin >> strike;
	}
	return strike;
}

// Automatic Batting Function
int compBat(string ball, Team* battingTeam, Team* bowlingTeam, Player* batsman, Player* bowler) {

	if (isStrike()) {

		if (ball != "wide" && ball != "noBall") {
			if (out(battingTeam)) {

				bowler->addWickets();
				battingTeam->addWicket();

				return 1;
			}
		}

		if (ball == "bouncer") {			// bouncer
			battingTeam->addRuns(6);
			batsman->addRuns(6);
			bowler->addRuns(6);
			return 0;
		}

		else if (ball == "noBall") {			// no ball
			int boundary[2] = { 4, 6 };

			int random = rand() % 2;
			battingTeam->addRuns(boundary[random]);
			batsman->addRuns(boundary[random]);
			bowler->addRuns(boundary[random]);
			return 0;
		}
		else if (ball == "wide") {			// wide
			battingTeam->addRuns(4);
			batsman->addRuns(4);
			bowler->addRuns(4);
			return 0;
		}
		else if (ball == "spin") {			// spin
			int score[5] = { 0, 1, 2, 4, 6 };

			int random = rand() % 5;
			battingTeam->addRuns(score[random]);
			batsman->addRuns(score[random]);
			bowler->addRuns(score[random]);
			return 0;
		}
		else {
			int score[5] = { 0, 1, 2, 4, 6 };

			int random = rand() % 5;
			battingTeam->addRuns(score[random]);
			batsman->addRuns(score[random]);
			bowler->addRuns(score[random]);
			return 0;
		}
	}
	else {
		if (ball != "wide" && ball != "noBall") {
			if (out(battingTeam)) {

				bowler->addWickets();
				battingTeam->addWicket();

				return 1;
			}
			else
				return 0;
		}

		battingTeam->addRuns(0);
		return 0;
	}
}

int Bat(string ball, Team *battingTeam, Team *bowlingTeam, Player *batsman, Player *bowler) {

		
	
		if (userStrike() == 1) {

			if (ball != "wide" && ball != "noBall") {
				if (out(battingTeam)) {

					bowler->addWickets();
					battingTeam->addWicket();

					return 1;
				}
			}

			if (ball == "bouncer") {			// bouncer
				battingTeam->addRuns(6);
				batsman->addRuns(6);
				bowler->addBowlerRuns(6);
				return 0;
			}

			else if (ball == "noBall") {			// no ball
				int boundary[2] = { 4, 6 };

				int random = rand() % 2;
				battingTeam->addRuns(boundary[random]);
				 batsman->addRuns(boundary[random]);
				 bowler->addBowlerRuns(boundary[random]);
				return 0;
			}
			else if (ball == "wide") {			// wide
				battingTeam->addRuns(4);
				 batsman->addRuns(4);
				 bowler->addBowlerRuns(4);
				return 0;
			}
			else if(ball == "spin") {			// spin
				int score[5] = { 0, 1, 2, 4, 6 };

				int random = rand() % 5;
				battingTeam->addRuns(score[random]);
				 batsman->addRuns(score[random]);
				 bowler->addBowlerRuns(score[random]);
				return 0;
			}
			else {
				int score[5] = { 0, 1, 2, 4, 6 };

				int random = rand() % 5;
				battingTeam->addRuns(score[random]);
				batsman->addRuns(score[random]);
				bowler->addBowlerRuns(score[random]);
				return 0;
			}
		}
		else {
			if (ball != "wide" && ball != "noBall") {
				if (out(battingTeam)) {

					bowler->addWickets();
					battingTeam->addWicket();

					return 1;
				}
				else
					return 0;
			}

			battingTeam->addRuns(0);
			return 0;
		}
}

// bowling function
string bowl() {

	string bowl[7] = { "bouncer", "noBall", "wide", "spin" , "normal", "normal" , "normal" };

	int random = rand() % 7;

	return bowl[random];

}

string userBowl() {
	const int constDistance = 50;
	const int constWidth = 10;
	const int constHeight = 20;
	const int const angle = 90;

	int distance = 0;
	int width = 0;
	int height = 0;
	int angles = 0;

	cout << "-------- Now Bowling ---------" << endl;

	cout << "-------------------Choose Carefully---------------------------------" << endl<< endl;
	cout << "-----------Distance:   -- > less than 50" << endl;
	cout << "-----------Width:		-- > less than 10" << endl;
	cout << "-----------height:		-- > less than 20" << endl;
	cout << "-----------angle:		-- > 85 < spin < 95" << endl;
	cout << "--------------------------------------------------------------------" << endl;
	cout << "Enter Distance: ";
	cin >> distance;
	cout << "Enter Width: ";
	cin >> width;
	cout << "Enter height: ";
	cin >> height;

	if (height > constHeight) {
		return "Bouncer";
	}
	else if (distance < constDistance) {
		return "noBall";
	}
	else if (width > constWidth) {
		return "wideBall";
	}
	else if (angles > 95 || angles < 85) {
		return "spin";
	}
	else {
		return "normal";
	}
}


// wicket increment function
int out(Team *battingTeam)
{
	srand(time(0));
	int out = rand() % 2;
	if (out == 0)
	{
		return 1;
	}
	return 0;
}

// Display innings Function
void displayScoreCard(Team* battingTeam, Team* bowlingTeam, Player* batsman, Player* bowler) {
	cout << "------------------------------- Score Card -------------------------------------" << endl;

	cout << "BattingTeam: " << battingTeam->getName() << "\t\t\t\t\t" << "Batsman: " << batsman->getName() << endl;
	cout << "BowlingTeam: " << bowlingTeam->getName() << "\t\t\t\t\t" << "Bowler: " << bowler->getName() << endl;

	cout << battingTeam->getName() << ": " << battingTeam->getRuns() << " / " << battingTeam->getWickets() << endl;

}

