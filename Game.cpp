//============================================================================
// Name        : Dandi Biyo
// Author      : Sudip Thapa & Prakash Layo Magar
// Description : Program that allows to play Dandi Biyo game with CPU
//============================================================================

#include <fstream>
#include <iostream>
#include "Game.h"
#include <thread>// std::this_thread::sleep_for
#include <chrono>
#include <ctime>// std::chrono::seconds
#include <iomanip>
#include <string>

namespace std {

// Default Constructor
Game::Game() {
	player1Point = 0;
	player2Point = 0;
	gameEnded = false;
	gameDuration = 0.0;
	winner = "";
	player1Name = "";
	player2Name = "";

	// Setting current date as game played date
	time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	string s(10, '\0');
	strftime(&s[0], s.size(), "%Y-%m-%d", std::localtime(&now));
	playedDate = s;

}

// Parameterized Constructor
Game::Game(string p1, string p2, int p1Point, int p2Point, string win, double duration, string pDate){
	player1Name = p1;
	player2Name = p2;
	player1Point = p1Point;
	player2Point = p2Point;
	winner = win;
	gameEnded = true;
	gameDuration = duration;
	playedDate = pDate;
}


void Game::setPlayer1Name(){
	cout << "Enter your name: ";
	getline(cin >> ws, player1Name);
	turn = player1Name;
}

void Game::setPlayer2Name(){
	cout << "Preparing CPU to play with you. Please wait...." << endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(3000)); // @suppress("Symbol is not resolved")
	cout << "CPU is ready to play.\n" << endl;
	player2Name = "CPU";
}

void Game::checkWinner(){
	if(player1Point >= 100){
		setWinner(player1Name);
	}
	if(player2Point >=100){
		setWinner(player2Name);
	}
}

void Game::play(){
	int point = (int)rand() % 50;
	string newTurn;
	if(turn == player1Name){
		player1Point += point;
		cout << "Your Point received: " << point << ". Total Point: " << player1Point << "\n" << endl;
		newTurn = player2Name;
	} else {
		player2Point += point;
		cout << "CPU Point received: " << point << ". Total Point: " << player2Point << endl;
		newTurn = player1Name;
	}
	cout << "-------------------------------------------------------------------------------------------------------------" << endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // @suppress("Symbol is not resolved")
	checkWinner();
	if(!isGameEnded()){
		turn = newTurn;
	}
}

void Game::leaveGame(){
	if(turn == player1Name){
		setWinner(player2Name);
	} else {
		setWinner(player1Name);
	}
}

void Game::toFile(ofstream& outFile){
	outFile << player1Name << "|" << player2Name << "|" << player1Point << "|" << player2Point << "|" << winner << "|" << gameDuration << "|" << playedDate << endl;
}

void Game::readFile(ifstream& inpFile){
	string p1, p2, p1Point, p2Point, win, duration, date;
	getline(inpFile, p1, '|');
	getline(inpFile, p2, '|');
	getline(inpFile, p1Point, '|');
	getline(inpFile, p2Point, '|');
	getline(inpFile, win, '|');
	getline(inpFile, duration, '|');
	getline(inpFile, date);

	if(!p1.empty() && !p2.empty() && !p1Point.empty() && !p2Point.empty() && !duration.empty()){
		player1Name = p1;
		player2Name = p2;
		player1Point = stoi(p1Point);
		player2Point = stoi(p2Point);
		winner = win;
		gameDuration = stod(duration);
		playedDate = date;
	}
}

void Game::toString(){
	cout << left << setw(20) << player1Name
		<< left << setw(20) << player2Name
		<< left << setw(20) << player1Point
		<< left << setw(20) << player2Point
		<< left << setw(20) << winner
		<< left << setw(20) << gameDuration
		<< left << setw(20) << playedDate << endl;
}

bool Game::isDate(string d){
	return playedDate.compare(d) == 0;
}

} /* namespace std */
