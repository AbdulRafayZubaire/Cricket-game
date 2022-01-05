#pragma once
#include <time.h>
#include <iostream>

using namespace std;

int random;


class Batting {
private:
	int overs;
	int wickets;
	int runs;

public:	
	// -------------------------------- Automoatic (computer) batting functions ---------------------------------

	bool isStrike() {					// if function returns 1 than score will be incremented according
										// to the rules if it returns 0 no score will be incremented
		bool random;
		random = rand() % 2;
		return random;
	}

	void Bat(int ball) {
		for (int i = 0; i < 10; i++) {			// will decide how many balls willl be bowled in an over

			if (isStrike()) {

				if (ball == "bouncer") {			// bouncer
					runs += 6;
					// *batsman.runs += 6;
					// *bowler.runs += 6;
				}

				else if (ball == "noBall") {			// no ball
					int boundary[2] = { 4, 6 };

					random = rand() % 2;
					runs += boundary[random];
					// *batsman.runs += boundary[random];
					// *bowler.runs += boundary[random];
				}
				else if (ball == "wide") {			// wide
					runs += 4;
					// *batsman.runs += 4;
					// *bowler.runs += 4;
				}
				else if (ball == "spin") {			// spin
					int score[5] = { 0, 1, 2, 4, 6 };

					random = rand() % 5;
					runs += score[random];
					// *batsman.runs += score[random];
					// *bowler.runs += score[random];
				}
			}
		}
	}

	string bowl() {
		
		string bowl[4] = { "bouncer", "noBall", "wide", "spin" };

		random = rand() % 4;

		return bowl[random];

	}

};
