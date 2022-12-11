//============================================================================
// Name        : Dandi Biyo Header File
// Author      : Sudip Thapa & Prakash Layo Magar
// Description : Program that allows to play Dandi Biyo game with CPU
//============================================================================

#ifndef GAME_H_
#define GAME_H_

#include<iostream>
#include <fstream>
#include <chrono>

namespace std {

class Game {

private:
	string player1Name;
	string player2Name;
	string winner;
	string turn;
	string playedDate;
	double gameDuration;
	bool gameEnded;
	int player1Point;
	int player2Point;
	void setWinner(string win){ winner = win; gameEnded = true; };
	void setPlayedDate(string d){ playedDate = d; };
	void checkWinner();

public:
	Game();
	Game(string, string, int, int, string, double, string);
	void setPlayedDuration(double duration) { gameDuration = duration; };
	string getPlayer1Name() const { return player1Name; };
	double getPlayedDuration() const { return gameDuration; };
	string getTurn() const { return turn; }
	string getWinner() const { return winner; };
	void leaveGame();
	void toString();
	bool isGameEnded() const { return gameEnded; };
	void setPlayer1Name();
	void setPlayer2Name();
	void play();
	void toFile(ofstream&);
	bool isDate(string);
	void readFile(ifstream&);

};

} /* namespace std */

#endif /* GAME_H_ */
