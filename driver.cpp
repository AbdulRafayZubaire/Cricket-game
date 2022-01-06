#include "player.h"
#include "team.h"

// Function prototypes
//bool isStrike();
int userStrike();
string bowl();
int Bat(string, Team*, Team*, Player*, Player*);
void displayScoreCard(Team*, Team*, Player*, Player*);
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


// --------------- Setting the Batting and Bowling pointers accordingly ------------- //

			int count = 0;
			//do {
				//if (count == 0) {
					if (alpha.getInnings()) {		// if alpha chooses to bat			
						battingTeam = &alpha;
						bowlingTeam = &comp;
					}
					else {
						battingTeam = &comp;
						bowlingTeam = &alpha;
					}
				//}
				//if (count == 1) {					// after change of innings		
				//		battingTeam = &comp;
				//		bowlingTeam = &alpha;
				//	}
				//	else {
				//		battingTeam = &alpha;
				//		bowlingTeam = &comp;
				//	}

				int ballsbowled = 0;
				int wickets = 0;

				for (int i = 0; i < 12; i++) {

					// referencing to the current batsman and bowler
					batsman = &(battingTeam->getPlayer(wickets));
					bowler = &(bowlingTeam->getPlayer(ballsbowled / 6));

					// Overall Display Fuction
					displayScoreCard(battingTeam, bowlingTeam, batsman, bowler);

					// calling the balling function
					string ball = bowl();

					// calling the batting function
					wickets = Bat(ball, battingTeam, bowlingTeam, batsman, bowler);

					// incrementing the balls
					ballsbowled++;

					// a count to maintain the shifting of innings btw batting and bowling team
					count++;
				}

			//} while (count % 12 == 0);					// do while loop
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

int Bat(string ball, Team *battingTeam, Team *bowlingTeam, Player *batsman, Player *bowler) {

	if (ball != "wide" && ball!= "noBall") {
		if (out(battingTeam)) {

			bowler->addWickets();
			battingTeam->addWicket();
			bowlingTeam->addWicket();

			return 1;
		}
		}

		if (userStrike()) {

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
			else if(ball == "spin") {			// spin
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
			battingTeam->addRuns(0);
			return 0;
		}
}

// bowling function
string bowl() {

	string bowl[5] = { "bouncer", "noBall", "wide", "spin" , "normal"};

	int random = rand() % 5;

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

// Display innings Function
void displayScoreCard(Team* battingTeam, Team* bowlingTeam, Player* batsman, Player* bowler) {
	cout << "------------------------------- Score Card -------------------------------------" << endl;

	cout << "BattingTeam: " << battingTeam->getName() << endl;
	cout << "BowlingTeam: " << bowlingTeam->getName() << endl;

	cout << battingTeam->getName() << ": " << battingTeam->getRuns() << " / " << battingTeam->getWickets() << endl;

}

