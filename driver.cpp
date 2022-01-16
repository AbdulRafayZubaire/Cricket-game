#include <stdlib.h>
#include <windows.h>
#include "player.h"
#include "team.h"


// ------------------------------ Function prototypes ------------------------------
bool isStrike();
bool userStrike();
string compBowl();
string userBowl();
int Bat(string, Team*&, Team*&, Player*&, Player*&);
int compBat(string, Team*&, Team*&, Player*&, Player*&);
bool out();
void displayScoreCard(Team*&, Team*&, Player*&, Player*&, string);
void teamSelection(Team&, Team&);
void gameDecision(Team&, Team&);
void pointerSetter(int, Team&, Team&, Team*&, Team*&);
void finalScoreCard(Team&, Team&);
//-----------------------------------------------------------------------------------


int main() {

	char play = '\0';
	
	do{

	Team alpha, comp;
	Team* battingTeam = nullptr, * bowlingTeam = nullptr;
	Player* batsman = nullptr, * bowler = nullptr;
	string ball;
	char overs = '\0';
	int count = 0;


	bool flag = 0;
	do {
		cout << "*************** ----- <        WELCOME        > ------ ****************" << endl << endl;

		char option;
		cout << "Select an option(1-3): " << endl;
		cout << "1. Play" << endl;
		cout << "2. Rules" << endl;
		cout << "3. Exit" << endl;

		cout << "Your choice: ";
		option = _getch();
		while (option != '1' && option != '2' && option != '3') {
			cout << "\t\t\t!--WARNING--! -> Select only between the given choices" << endl;
			cout << "Your choice: ";
			option = _getch();
		}

		system("cls");								// clear terminal

		switch (option) {
		case '1': {
			// Team selection
			teamSelection(alpha, comp);

			//system("cls");

			// Toss for the game
			alpha.gameToss(comp);


			// overs decision
			cout << "how many overs would you like to play: " << endl;
			overs = _getch();
			while (overs != '1' && overs != '2' && overs != '3' && overs != '4' && overs != '5' && overs != '6' && overs != '7' && overs != '8' && overs != '9' && overs != '10' &&
				overs != '11' && overs != '12' && overs != '13' && overs != '14' && overs != '15' && overs != '16' && overs != '17' && overs != '18' && overs != '19' && overs != '20') {
				
				cout << "\t\t\t!--WARNING--! -> Overs cannot be zero" << endl;
				cout << "how many overs would you like to play: " << endl;
				overs = _getch();
			}
			overs = int(overs - 48);

			// ------------------------- Setting the Batting and Bowling pointers accordingly ------------------------- //

			int inningsChanger = 0;							// deals in changin the batting and bowling pointers
			int proceed = 0;								// deals with no. of innings

			do {
				proceed++;

				//Setting the pointers of batting and bowling team respectively
				pointerSetter(inningsChanger, alpha, comp, battingTeam, bowlingTeam);

				int ballsBowled = 0;							// For the sake of changing the Bowler
				int batsmanNO = 0;								// For the sake of changing the Batsman
				int bowlerNumber = 10;

				for (int i = 0; i < (overs * 6); i++) {

					// setting the reference to the curerent Batsman
					batsman = &(battingTeam->getPlayer(batsmanNO));

					// setting the reference to the curerent Bowler
					if (ballsBowled % 6 == 0) {
						if (bowlerNumber < 5) {
							bowlerNumber = 10;
						}
						if (count == 0) {
							bowler = &(bowlingTeam->getPlayer(bowlerNumber));
							bowlerNumber--;
						}
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
					displayScoreCard(battingTeam, bowlingTeam, batsman, bowler, ball);


					if (battingTeam == &alpha) {

						// calling the balling function and batting functions
						ball = compBowl();
						batsmanNO += Bat(ball, battingTeam, bowlingTeam, batsman, bowler);		// wickets is for changing batsman
					}

					else if (bowlingTeam == &alpha) {

						// calling the balling function and batting functions
						ball = userBowl();
						batsmanNO += compBat(ball, battingTeam, bowlingTeam, batsman, bowler);

					}

					// incrementing the balls
					
					if (ball != "wide" && ball != "noBall") {
						
						ballsBowled++;
						count = 0;
					}
					else {
						count++;
						i--;
					}

				}

				inningsChanger++;

			} while (proceed < 2);					// do while loop


			// game decision
			gameDecision(alpha, comp);

			// screen clear
			system("cls");

			if (alpha.getWin() == 1 && comp.getWin() == 1) {
				cout << "\n***************************  match Drawn  **************************" << endl << endl;
			}
			else if (alpha.getWin() == 1) {
				cout << "\n*******************  Congratulations You won the game  *********************" << endl << endl;
			}
			else if (comp.getWin() == 1) {
				cout << "\n**************************  You lost the game  *************************" << endl << endl;
			}
			break;
		}


			  // ------------------------------------------- RULES -----------------------------------------
		case '2': {

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
		case '3': {
			break;
		}
		}


	} while (flag);

	if (alpha.getWin() || comp.getWin()) {
		finalScoreCard(alpha, comp);
	}

	// clear screen

// ----------------------------------------------------- Game Finishes --------------------------------------------------------
		cout << "Do you want to play Again. ?";
		play = _getch();
		while (play != 'y' && play != 'Y' && play != 'N' && play != 'n') {
			cout << "\t\t\t!--WARNING--! -> Invalid Input .." << endl;
			cout << "Do you want to play Again. ?";
			play = _getch();
		}
	}while (play == 'y' || play == 'Y');


	cout << " \n <-----------------------------------> Game exited <------------------------------------> " << endl;

	system("pause");
	return 0;
}

// ---------------------------------------------- Function Definitions ----------------------------------------------------

// team selection
void teamSelection(Team& alpha, Team& comp) {
	char teamA, teamB;
	cout << "Select your team from the following." << endl;
	cout << setw(15) << "1. Pakistan" << endl;
	cout << setw(16) << "2. Australia" << endl;
	cout << setw(18) << "3. New Zealand" << endl;
	cout << setw(15) << "4. Zimbabwe" << endl;
	cout << setw(15) << "5. Srilanka" << endl;

	// Team selection
	cout << "your choice: ";
	teamA = _getch();
	while (teamA < '1' || teamA > '5') {
		cout << "\t\t\t!--WARNING--! -> Select between the given choices only" << endl;
		cout << "your choice: ";
		teamA = _getch();
		
	}
	alpha.setName(int(teamA)- 48);
	system("cls");
	cout << alpha.getName() << " is your TEAM" << endl;

	alpha.setPlayers(teamA - 1 -48, "user");

	system("cls");

	cout << "Select the opponent team from th following: " << endl;
	cout << setw(15) << "1. Pakistan" << endl;
	cout << setw(16) << "2. Australia" << endl;
	cout << setw(18) << "3. New Zealand" << endl;
	cout << setw(15) << "4. Zimbabwe" << endl;
	cout << setw(15) << "5. Srilanka" << endl;
	cout << "opponent team: ";
	teamB = _getch();
	while (teamB < '1' && teamB > '5') {
		cout << "\t\t\t!--WARNING--! -> Select between the given choices only" << endl;
		cout << "your choice: ";
		teamB = _getch();
	}
	while (teamB == teamA) {
		cout << "\t\t\t!--WARNING--! -> This team is already been selected for the user" << endl;
		cout << "your choice: ";
		teamB = _getch();
	}
	comp.setName((int)teamB - 48);

	system("cls");
	cout << alpha.getName() << " is your TEAM" << endl;

	comp.setPlayers((int)teamB -48 - 1, "comp");
}


// -------------------------------- Automoatic (computer) batting functions ---------------------------------

bool isStrike() {					// if function returns 1 than score will be incremented according
									// to the rules if it returns 0 no score will be incremented

	int strike[6] = { 1, 1, 1, 1, 1, 0 };

	bool random;
	random = rand() % 6;
	return strike[random];
}




// is strike function for the user
bool userStrike() {
	int strike = 0;

	cout << " -> To strike press 1" << endl;
	cout << " -> To leave press 2" << endl;
	cin >> strike;
	while (strike != 1 && strike != 2) {
		cout << "------- Invalid choice -------";
		cout << " -> To strike press 1" << endl;
		cout << " -> To leave press 2" << endl;
		cin >> strike;
	}
	if (strike == 1) {
		return 1;
	}
	else {
		return 0;
	}
}

// Automatic Batting Function
int compBat(string ball, Team*& battingTeam, Team*& bowlingTeam, Player*& batsman, Player*& bowler) {

	if (isStrike()) {

		if (ball != "noBall") {
			if (out()) {

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

int Bat(string ball, Team*& battingTeam, Team*& bowlingTeam, Player*& batsman, Player*& bowler) {


	if (userStrike()) {

		if (ball != "noBall") {
			if (out()) {

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

	// to make a solid algorithm I have used an idea of probability here
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

	cout << "-----------------------Choose Carefully-----------------------------" << endl << endl;
	cout << "-----------Distance:		-- > keep your Distance above 20" << endl;
	cout << "-----------Width:		-- > width above (10) will be considered wide" << endl;
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
	else if (distance < constDistance) {
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
bool out()
{
	srand(time(0));
	int out;
	out = rand() % 4;
	if (out == 1)
	{
		return 1;
	}
	else {
		return 0;
	}
}

// ------------------------------------------ Display innings Function -------------------------------------
void displayScoreCard(Team*& battingTeam, Team*& bowlingTeam, Player*& batsman, Player*& bowler, string ball) {


	// --------------------------------------------------------------------------------------------------------------------------
	cout << "\t\t\t\t\t\t\t" << "overs: " << (battingTeam->getOvers() / 6) << "." << (battingTeam->getOvers() % 6) << endl;
	// --------------------------------------------------------------------------------------------------------------------------


	cout << "------------------------------- Score Card --------------------------------------" << endl;

	cout << "BattingTeam: " << battingTeam->getName() << "\t\t\t\t\t" << "Batsman: " << batsman->getName() << endl;
	cout << "BowlingTeam: " << bowlingTeam->getName() << "\t\t\t\t\t" << "Bowler: " << bowler->getName() << endl << endl << endl << endl << endl;



	cout << battingTeam->getName() << ": (" << battingTeam->getRuns() << " | " << battingTeam->getWickets() << ")" << endl;
	cout << "---------------------------------------------------------------------------------" << endl;
	cout << batsman->getName() << ": " << batsman->getRuns() << "\t\t\t\t\t" << bowler->getName() << ": (" << bowler->getBowlerRuns() << "/" << bowler->getWickets() << ")" << endl;
	cout << "---------------------------------------------------------------------------------" << endl << endl << endl;


	// --------------
	if (ball != "noBall" && ball != "wide") {
		battingTeam->setOvers();						// balls increment
	}
	// --------------

}

void gameDecision(Team& alpha, Team& comp) {

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

void pointerSetter(int inningsChanger, Team& alpha, Team& comp, Team*& battingTeam, Team*& bowlingTeam) {

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
	cout << "                                        Match Summary" << endl << endl;
	cout << "*************************************************************************************************" << endl;
	cout << "                                      Batting ScoreCard" << endl;
	cout << "*************************************************************************************************" << endl << endl;
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	cout << "-> " << alpha.getName() << "\t\t\t\t\t"<< "Score ( " << alpha.getRuns() << " | " << alpha.getWickets() << " )" << endl;
	cout << "-------------------------------------------------------------------------------------------------" << endl;

	for (int i = 0; i < 11; i++) {

		if (alpha.getPlayer(i).getRuns() == NULL) {
			continue;
		}

		cout << "  " << setw(20) << left << alpha.getPlayer(i).getName() << left;
		cout << alpha.getPlayer(i).getRuns() << endl;
	}

	cout << endl << endl;

	cout << "-------------------------------------------------------------------------------------------------" << endl;
	cout << "-> " << comp.getName() << "\t\t\t\t\t" << "Score ( " << comp.getRuns() << " | " << comp.getWickets() << " )" << endl;
	cout << "-------------------------------------------------------------------------------------------------" << endl;

	for (int i = 0; i < 11; i++) {

		if (comp.getPlayer(i).getRuns() == NULL) {
			continue;
		}

		cout << "  " << setw(20) << left << comp.getPlayer(i).getName() << left;
		cout << comp.getPlayer(i).getRuns() << endl;

	}

	cout << endl;

	cout << "*************************************************************************************************" << endl;
	cout << "                                      Bowling ScoreCard" << endl;
	cout << "*************************************************************************************************" << endl << endl;
	cout << " -------------------" << alpha.getName() << " ----------------" << endl;

	for (int i = 10; i > 0; i--) {

			cout << "  " << setw(20) << left << alpha.getPlayer(i).getName() << left;
			cout << "( " << alpha.getPlayer(i).getBowlerRuns() << " | " << alpha.getPlayer(i).getWickets() << " )" << endl;

		if (alpha.getPlayer(i).getBowlerRuns() == NULL) {
			break;
		}
	}
	cout << endl << endl;

	cout << " -------------------" << comp.getName() << " ----------------" << endl;
	for (int i = 10; i > 0; i--) {

		cout << "  " << setw(20) << left << comp.getPlayer(i).getName() << left;
		cout << "(" << comp.getPlayer(i).getBowlerRuns() << " | " << comp.getPlayer(i).getWickets() << " )" << endl;

		if (comp.getPlayer(i).getBowlerRuns() == '\0') {
			break;
		}
	}
}