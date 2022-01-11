#include <stdlib.h>
#include <windows.h>
#include "player.h"
#include "team.h"


// ------------------------------ Function prototypes ------------------------------
bool isStrike();
int userStrike();
string compBowl();
string userBowl();
int Bat(string, Team* &, Team* &, Player* &, Player* &);
int compBat(string, Team* &, Team* &, Player* &, Player* &);
void displayScoreCard(Team* &, Team* &, Player* &, Player* &);
int out(Team* &);
void teamSelection(Team&, Team&);
void gameDecision(Team&, Team&);
void pointerSetter(int, Team&, Team&, Team* &, Team* &);
void finalScoreCard(Team&, Team&);
//-----------------------------------------------------------------------------------


int main() {

	//char play = '\0';

		Team alpha, comp;
		Team* battingTeam = nullptr, * bowlingTeam = nullptr;
		Player* batsman = nullptr, * bowler = nullptr;
		string ball;
		int overs = 0;


		bool flag = 0;
		do {
			cout << "*************** ----- <        WELCOME        > ------ ****************" << endl << endl;
		
			int option;
			cout << "Select an option(1-3): " << endl;
			cout << "1. Play" << endl;
			cout << "2. Rules" << endl;
			cout << "3. Exit" << endl;

			cout << "Your choice: ";
			cin >> option;
			while (option != 1 && option != 2 && option != 3) {
				cout << "\t\t\t!--WARNING--! -> Select only between the given choices" << endl;
				cout << "Your choice: ";
				cin >> option;
			}

			system("cls");								// clear terminal

			switch (option) {
			case 1: {
				// Team selection
				teamSelection(alpha, comp);

				// Toss for the game
				alpha.gameToss(comp);


				// overs decision
				cout << "how many overs would you like to play: " << endl;
				cin >> overs;
				while (option < 1 || option > 10) {
					cout << "\t\t\t!--WARNING--! -> Overs cannot be zero" << endl;
					cout << "how many overs would you like to play: " << endl;
					cin >> overs;
				}

	// ------------------------- Setting the Batting and Bowling pointers accordingly ------------------------- //

				int inningsChanger = 0;							// deals in changin the batting and bowling pointers
				int proceed = 0;								// deals with no. of innings

				do {
					proceed++;

					//Setting the pointers of batting and bowling team respectively
					pointerSetter(inningsChanger, alpha, comp, battingTeam, bowlingTeam);

					int ballsBowled = 0;							// For the sake of changing the Bowler
					int wickets = 0;								// For the sake of changing the Batsman
					int bowlerNumber = 10;

					for (int i = 0; i < (overs * 6); i++) {

						// setting the reference to the curerent Batsman
						batsman = &(battingTeam->getPlayer(wickets));

						// setting the reference to the curerent Bowler
						if (ballsBowled % 6 == 0) {
							bowler = &(bowlingTeam->getPlayer(bowlerNumber));
							bowlerNumber--;
						}
						
						// clear screeen
						system("cls");

	// --------------------------------------- Breaking Points ---------------------------------------------------------------------

						if (inningsChanger) {
							cout << "TARGET: " << bowlingTeam->getRuns();

							if (battingTeam->getRuns() > bowlingTeam->getRuns()) {
								break;
							}
							else if (battingTeam->getWickets() == 10) {
								break;
							}
						}
						else {
							cout << "TARGET: _____";
						}

						if (battingTeam->getWickets() == 10) {
							break;
						}

	 // ---------------------------------------------------------------------------------------------------------------------------

						// Current score Display Fuction
						displayScoreCard(battingTeam, bowlingTeam, batsman, bowler);				


						if (battingTeam == &alpha) {

							// calling the balling function and batting functions
							ball = compBowl();
							wickets += Bat(ball, battingTeam, bowlingTeam, batsman, bowler);
						}

						else if (bowlingTeam == &alpha) {

							// calling the balling function and batting functions
							ball = userBowl();
							wickets += compBat(ball, battingTeam, bowlingTeam, batsman, bowler);

						}

						// incrementing the balls
						ballsBowled++;

					}

					inningsChanger++;

				} while (proceed < 2);					// do while loop


				// game decision
				gameDecision(alpha, comp);

				// screen clear
				system("cls");

				if (alpha.getWin() == 1 && comp.getWin() == 1) {
					cout << "match Drawn" << endl;
				}
				else if (alpha.getWin() == 1) {
					cout << "Congratulations You won the game" << endl;
				}
				else if (comp.getWin() == 1) {
					cout << "You lost the game" << endl;
				}
				break;
			}


// ------------------------------------------- RULES -----------------------------------------
			case 2: {

				// Rules reading from the file
				char choice;
				string line;

				fstream file;
				file.open("Rules.txt", ios::in);

				if (file.is_open()) {
					while (getline(file, line)) {												// file reading
						cout << line << endl;

					}
				}
				file.close();

				break;
			}

// ------------------------------------------- QUIT ------------------------------------------
			case 3: {
				cout << "Thank you" << endl;
				break;
			}
			}


		} while (flag);

		finalScoreCard(alpha, comp);

		// clear screen

// ----------------------------------------------------- Game Finishes --------------------------------------------------------
	//	cout << "Do you want to play Again. ?";
	//	cin >> play;
	//	while (play != 'y' && play != 'Y' && play != 'N' && play != 'n') {
	//		cout << "\t\t\t!--WARNING--! -> Invalid Input .." << endl;
	//		cout << "Do you want to play Again. ?";
	//		cin >> play;
	//	}
	//}while (play == 'y' || play == 'Y');

	system("pause");
	return 0;
}

// ---------------------------------------------- Function Definitions ----------------------------------------------------

// team selection
void teamSelection(Team &alpha, Team &comp) {
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
	while (team < 0 && team > 5) {
		cout << "\t\t\t!--WARNING--! -> Select between the given choices only" << endl;
		cout << "your choice: ";
		cin >> team;
	}
	alpha.setName(team);
	alpha.setPlayers(team - 1, "user");

	system("cls");

	cout << "Select the opponent team from th following: " << endl;
	cout << setw(15) << "1. Pakistan" << endl;
	cout << setw(16) << "2. Australia" << endl;
	cout << setw(18) << "3. New Zealand" << endl;
	cout << setw(15) << "4. Zimbabwe" << endl;
	cout << setw(15) << "5. Srilanka" << endl;
	cout << "opponent team: ";
	cin >> team;
	while (team < 0 && team > 5) {
		cout << "\t\t\t!--WARNING--! -> Select between the given choices only" << endl;
		cout << "your choice: ";
		cin >> team;
	}
	comp.setName(team);
	comp.setPlayers(team - 1, "comp");
}


// -------------------------------- Automoatic (computer) batting functions ---------------------------------

bool isStrike() {					// if function returns 1 than score will be incremented according
									// to the rules if it returns 0 no score will be incremented
	
	int stroke[5] = { 1, 1, 1, 1, 0};
	
	bool random;
	random = rand() % 5;
	return stroke[random];
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
int compBat(string ball, Team* &battingTeam, Team* &bowlingTeam, Player* &batsman, Player* &bowler) {

	if (isStrike()) {

		if (ball != "noBall") {
			if (out(battingTeam)) {

				bowler->addWickets();
				batsman->addRuns(0);
				battingTeam->addWicket();

				cout << " ! ------------------- OUT --------------------!" << endl;
				Sleep(1000);

				return 1;
			}
		}

		if (ball == "bouncer") {			// bouncer
			battingTeam->addRuns(6);
			batsman->addRuns(6);
			bowler->addBowlerRuns(6);

			cout << "*** ----------------- It's a SIXER ----------------- ***" << endl;
			Sleep(1000);
			
			return 0;
		}

		else if (ball == "noBall") {			// no ball
			int boundary[2] = { 4, 6 };

			int random = rand() % 2;
			battingTeam->addRuns(boundary[random]);
			batsman->addRuns(boundary[random]);
			bowler->addBowlerRuns(boundary[random]);

			cout << "*** ----------------- It's a (" << boundary[random] << ") ---------------- - ***" << endl;
			Sleep(1000);
			
			return 0;
		}
		else if (ball == "wide") {			// wide
			battingTeam->addRuns(4);
			batsman->addRuns(4);
			bowler->addBowlerRuns(4);

			cout << "*** ----------------- It's a SIXER ----------------- ***" << endl;
			Sleep(1000);
			
			return 0;
		}
		else if (ball == "spin") {			// spin
			int score[5] = { 0, 1, 2, 4, 6 };

			int random = rand() % 5;
			battingTeam->addRuns(score[random]);
			batsman->addRuns(score[random]);
			bowler->addBowlerRuns(score[random]);

			cout << "*** ----------------- It's a (" << score[random] << ") ---------------- - ***" << endl;
			Sleep(1000);
			
			return 0;
		}
		else {
			int score[5] = { 0, 1, 2, 4, 6 };

			int random = rand() % 5;
			battingTeam->addRuns(score[random]);
			batsman->addRuns(score[random]);
			bowler->addBowlerRuns(score[random]);

			cout << "*** ----------------- It's a (" << score[random] << ") ---------------- - ***" << endl;
			Sleep(1000);
			
			return 0;
		}
	}
	else {
		if (ball == "normal") {											// if computer does not strike

			bowler->addWickets();
			batsman->addRuns(0);
			battingTeam->addWicket();

			cout << " ! ------------------- OUT --------------------!" << endl;
			Sleep(1000);
			
			return 1;
		}
		else
			return 0;
	}
}

int Bat(string ball, Team* &battingTeam, Team* &bowlingTeam, Player* &batsman, Player* &bowler) {

	
		if (userStrike() == 1) {

			if (ball != "noBall") {
				if (out(battingTeam)) {

					bowler->addWickets();
					batsman->addRuns(0);
					battingTeam->addWicket();

					cout << " ! ------------------- OUT --------------------!" << endl;
					Sleep(1000);
					return 1;
				}
			}

			if (ball == "bouncer") {			// bouncer
				battingTeam->addRuns(6);
				batsman->addRuns(6);
				bowler->addBowlerRuns(6);
				cout << bowler->getBowlerRuns();

				cout << "*** ----------------- It's a SIXER ----------------- ***" << endl;
				Sleep(1000);
				return 0;
			}

			else if (ball == "noBall") {			// no ball
				int boundary[2] = { 4, 6 };

				int random = rand() % 2;
				battingTeam->addRuns(boundary[random]);
				 batsman->addRuns(boundary[random]);
				 bowler->addBowlerRuns(boundary[random]);
				 cout << bowler->getBowlerRuns();

				 cout << "*** ----------------- It's a (" <<  boundary[random] << ") ---------------- - ***" << endl;
				 Sleep(1000);
				 return 0;
			}
			else if (ball == "wide") {			// wide
				battingTeam->addRuns(4);
				batsman->addRuns(4);
				bowler->addBowlerRuns(4);

				cout << "*** ----------------- It's a FOUR ----------------- ***" << endl;
				Sleep(1000);
				return 0;
			}
			else if (ball == "spin") {			// spin
				int score[5] = { 0, 1, 2, 4, 6 };

				int random = rand() % 5;
				battingTeam->addRuns(score[random]);
				batsman->addRuns(score[random]);
				bowler->addBowlerRuns(score[random]);

				cout << "*** ----------------- It's a (" << score[random] << ") ---------------- - ***" << endl;
				Sleep(1000);
				return 0;
			}
			else {
				int score[5] = { 0, 1, 2, 4, 6 };

				int random = rand() % 5;
				battingTeam->addRuns(score[random]);
				batsman->addRuns(score[random]);
				bowler->addBowlerRuns(score[random]);

				cout << "*** ----------------- It's a (" << score[random] << ") ---------------- - ***" << endl;
				Sleep(1000);
				return 0;
			}
		}

		else {													// If user does not strike
			if (ball == "normal") {

				bowler->addWickets();
				batsman->addRuns(0);
				battingTeam->addWicket();

				cout << " ! ------------------- OUT --------------------!" << endl;
				Sleep(1000);
				return 1;
			}
			else
				return 0;
		}
}

// -------------------------------------------- bowling function ---------------------------------------
string compBowl() {

	string bowl[8] = { "bouncer", "noBall", "wide", "spin", "spin" , "normal", "normal" , "normal" };

	int random = rand() % 8;

	return bowl[random];

}


// ----------------------------------------- User batting Function -------------------------------------
string userBowl() {
	const int constDistance = 20;
	const int constWidth = 10;
	const int constHeight = 10;

	int distance = 0;
	int width = 0;
	int height = 0;
	int spin = 0;

	cout << "------------------------ Now Bowling -------------------------------" << endl << endl;

	cout << "-----------------------Choose Carefully-----------------------------" << endl<< endl;
	cout << "-----------Distance:		-- > keep your Distance above 20" << endl;
	cout << "-----------Width:		-- > For wider delivery bowl above (10)" << endl;
	cout << "-----------height:		-- > For Bouncer above (10)" << endl;
	cout << "-----------angle:		-- > For Spin -> (85 > spin > 95)" << endl;
	cout << "--------------------------------------------------------------------" << endl;
	cout << "Enter Distance: ";
	cin >> distance;
	cout << "Enter Width: ";
	cin >> width;
	cout << "Enter height: ";
	cin >> height;
	cout << "Enter spin: ";
	cin >> spin;

	if (height > constHeight) {
		return "Bouncer";
	}
	else if (distance <= constDistance) {
		return "noBall";
	}
	else if (width > constWidth) {
		return "wideBall";
	}
	else if (spin > 95 || spin < 85) {
		return "spin";
	}
	else {
		return "normal";
	}
}


// -------------------------------------------- wicket increment function -------------------------------------
int out(Team* &battingTeam)
{
	srand(time(0));
	int out = rand() % 4;
	if (out == 0)
	{
		return 1;
	}
	return 0;
}

// ------------------------------------------ Display innings Function -------------------------------------
void displayScoreCard(Team* &battingTeam, Team* &bowlingTeam, Player* &batsman, Player* &bowler) {


// --------------------------------------------------------------------------------------------------------------------------
	cout << "\t\t\t\t\t\t\t" << "overs: " << (battingTeam->getOvers() / 6) << "." << (battingTeam->getOvers() % 6) << endl;
// --------------------------------------------------------------------------------------------------------------------------


	cout << "------------------------------- Score Card --------------------------------------" << endl;

	cout << "BattingTeam: " << battingTeam->getName() << "\t\t\t\t\t" << "Batsman: " << batsman->getName() << endl;
	cout << "BowlingTeam: " << bowlingTeam->getName() << "\t\t\t\t\t" << "Bowler: " << bowler->getName() << endl << endl << endl << endl << endl;



	cout << battingTeam->getName() << ": (" << battingTeam->getRuns() << " | " << battingTeam->getWickets() << ")" << endl;
	cout << "---------------------------------------------------------------------------------" << endl;
	cout << batsman->getName() << ": "<< batsman->getRuns() << "\t\t\t\t\t\t" << bowler->getName() << ": (" << bowler->getBowlerRuns() << "/" << bowler->getWickets() << ")" << endl;
	cout << "---------------------------------------------------------------------------------" << endl << endl << endl;


// --------------
	battingTeam->setOvers();
// --------------

}

void gameDecision(Team &alpha, Team &comp) {

	if (alpha.getFirstInnings() == "Bat") {

		if (alpha.getWickets() == 10) {
			alpha.setWin(1);
			comp.setWin(0);
		}

		else if (comp.getRuns() < alpha.getRuns()) {
			comp.setWin(0);
			alpha.setWin(1);
		}

		else if (comp.getRuns() == alpha.getRuns()) {
			comp.setWin(1);
			alpha.setWin(1);
		}

		else {
			comp.setWin(1);
			alpha.setWin(0);
		}
	}
	
	else {
		if (comp.getWickets() == 10) {
			comp.setWin(1);
			alpha.setWin(0);
		}
		else if (alpha.getRuns() < comp.getRuns()) {
			comp.setWin(1);
			alpha.setWin(0);
		}
		else if (comp.getRuns() == alpha.getRuns()) {
			comp.setWin(1);
			alpha.setWin(1);
		}
		else {
			alpha.setWin(1);
			comp.setWin(0);
		}
	}
}

void pointerSetter(int inningsChanger, Team &alpha, Team &comp, Team* &battingTeam, Team* &bowlingTeam) {

	// Setting the pointer for first innings
	if (inningsChanger == 0) {
		if (alpha.getFirstInnings() == "Bat") {		// if alpha chooses to bat			

			battingTeam = &alpha;				// setting the pointers according to the result of toss
			bowlingTeam = &comp;
		}
		else {

			battingTeam = &comp;
			bowlingTeam = &alpha;
		}
	}

	// Setting the pointer for Second innings
	else {
		if (alpha.getFirstInnings() == "Bat") {		// if alpha chooses to bat			
			battingTeam = &comp;
			bowlingTeam = &alpha;
		}
		else {
			battingTeam = &alpha;
			bowlingTeam = &comp;
		}
	}
}

void finalScoreCard(Team& alpha, Team& comp) {
	cout << "--------------------------------------- Match Summary -------------------------------------------" << endl << endl;
	
	cout << "                                      Batting ScoreCard" << endl;

	cout << "-------------------------------------------------------------------------------------------------" << endl;
	cout << "  " << alpha.getName() << endl;
	cout << "----------------------" << endl;
	
	for (int i = 0; i < 11; i++) {
	
		if (alpha.getPlayer(i).getRuns() == '\0') {
			break;
		}
		cout << "  " << setw(20) << left << alpha.getPlayer(i).getName() << left;
		cout << alpha.getPlayer(i).getRuns() << endl;
	}

	cout << endl << endl;

	cout << "-------------------------------------------------------------------------------------------------" << endl;
	cout << "  " << comp.getName() << endl;
	cout << "---------------------" << endl;

	for (int i = 0; i < 11; i++) {

		if (comp.getPlayer(i).getRuns() == '\0') {
			break;
		}
		cout << "  " << setw(20) << left << comp.getPlayer(i).getName() << left;
		cout << comp.getPlayer(i).getRuns() << endl;
	}
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	cout << endl;

	cout << "                                      Bowling ScoreCard" << endl;
	cout << " " <<alpha.getName() << " ------------" << endl;

	for (int i = 10; i > 0; i--) {

		if (alpha.getPlayer(i).getBowlerRuns() == '\0') {
			break;
		}
		cout << "  " << setw(20) << left << alpha.getPlayer(i).getName() << left;
		cout << "( " << alpha.getPlayer(i).getBowlerRuns() << " | " << alpha.getPlayer(i).getWickets() << " )" << endl;
	}
	cout << endl << endl;

	cout << " " <<comp.getName() << " -------------" << endl;
	for (int i = 10; i > 0; i--) {

		if (comp.getPlayer(i).getBowlerRuns() == '\0') {
			break;
		}
		cout << "  " << setw(20) << left << comp.getPlayer(i).getName() << left;
		cout << "(" << comp.getPlayer(i).getBowlerRuns() << " | " << comp.getPlayer(i).getWickets() << " )" << endl;
	}
}