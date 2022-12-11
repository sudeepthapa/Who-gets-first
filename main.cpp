//============================================================================
// Name        : Dandi Biyo
// Author      : Sudip Thapa & Prakash Layo Magar
// Description : Program that allows to play Dandi Biyo game with CPU
//============================================================================

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <thread> // std::this_thread::sleep_for
#include <chrono>
#include "Game.h"
using namespace std;

#define GAMES_FILE "src/games.txt"

// Function declarations
void printGameHistory(vector<Game> games);
void searchGameHistory(vector<Game> games);
void playGame(vector<Game> &games);
void searchGameHistoryByDate(vector<Game> games);
void printTableHeader();
void prepareMenuSelection(vector<Game> &games);

/*
  main()
  Author: Sudip Thapa
  Description: Contoller that controls the flow of the game.
  Return Value: a integer 0.
 */

int main() {
	cout << "Welcome, Lets play Dandi Biyo !!" << endl;
	vector<Game> games;
	ifstream inpFile(GAMES_FILE);

	// Check if file exists
	if (!inpFile) {
		cout << "File not created!";
		exit(0);
	}

	// Check if file is open
	if (!inpFile.is_open()) {
		cout << "Cannot open the file." << endl;
		exit(0);
	}

	// Get data from file
	while (!inpFile.eof()) {
		Game game = Game();
		game.readFile(inpFile);
		if(!game.getPlayer1Name().empty()){
			games.push_back(game);
		}
	}

	inpFile.close();

	// Preparing menu for selection
	prepareMenuSelection(games);

	// Persisting data to file
	ofstream outFile(GAMES_FILE);
	for(int i=0; i<games.size(); i++){
		games[i].toFile(outFile);
	}

	outFile.close();

	cout << "\n\nThank you for playing the game.\n";
	cout << "Bye.\n";

	return 0;
}

/*
  prepareMenuSelection()
  Author: Sudip Thapa
  Parameters:
  	  games: reference to vector of game class
  Description: Displays menu and controls the flow
  Return Value: void.
 */

void prepareMenuSelection(vector<Game> &games){
	int menuSelection = -1;

	// Provide menu for selection
	while(menuSelection != 0){
		cout << "\nWhat do you want to do? : " << endl;
		cout << "\t1 : Play Game" << endl;
		cout << "\t2 : See Previous Game History" << endl;
		cout << "\t3 : Search game history by winner name" << endl;
		cout << "\t4 : Search by game date" << endl;

		cout << "\t0 : Exit Game" << endl;

		cout << "-> ";
		cin >> menuSelection;

		// Validate menu
		while(menuSelection < 0 || menuSelection > 4){
			cout << "Invalid Entry. Please refer to menu and enter: ";
			cin >> menuSelection;
		}

		// Make choice based on  menu selection
		if(menuSelection == 0){
			break;
		} else if(menuSelection == 1){
			playGame(games);
		} else if(menuSelection == 2){
			printGameHistory(games);
		} else if(menuSelection == 3){
			searchGameHistory(games);
		} else if(menuSelection == 4){
			searchGameHistoryByDate(games);
		}
	}
}

/*
  printTableHeader()
  Author: Prakash Layo Magar
  Description: Prints header of a table
  Return Value: void.
 */

void printTableHeader(){
	cout << "\n----------------------------------------------------------------------------------------------------------------------------------------------\n";

	cout << left << setw(20) << "Player 1"
			<< left << setw(20) << "Player 2"
			<< left << setw(20) << "Player 1 Point"
			<< left << setw(20) << "Player 2 Point"
			<< left << setw(20) << "Winner"
			<< left << setw(20) << "Game Duration(sec)"
			<< left << setw(20) << "Played Date" << endl;
	cout << "----------------------------------------------------------------------------------------------------------------------------------------------" << endl;
}

/*
  playGame()
  Author: Sudip Thapa
  Parameters:
  	  games: reference to vector of game class
  Description: Controls game start and end logic
  Return Value: void.
 */

void playGame(vector<Game> &games){
	cout << "\n----------------------------------------------------------------------------------------------------------------------------------------------\n";

	int gameStatus = 1;
	while(gameStatus == 1){
		Game game = Game(); // @suppress("Invalid arguments")
		game.setPlayer1Name();
		game.setPlayer2Name();

		// Game start time
		chrono::time_point<chrono::steady_clock> start = std::chrono::steady_clock::now();

		for(;;){
			if(game.isGameEnded()) break;

			cout << "\n" << game.getTurn() << " Turn ";
			cout << "[1: Play , 0: Exit]: ";

			if(game.getTurn() == "CPU"){
				// Creating some delays
				std::this_thread::sleep_for(chrono::milliseconds(2000)); // @suppress("Symbol is not resolved")
				cout << "CPU chooses to play." << endl;
				std::this_thread::sleep_for(chrono::milliseconds(2000)); // @suppress("Symbol is not resolved")

			} else {
				cin >> gameStatus;
				while(gameStatus != 0 && gameStatus != 1){
					cout << "Invalid Entry. Please refer to menu and enter: ";
					cin >> gameStatus;
				}
			}

			if(gameStatus == 1){
				game.play();
			} else {
				game.leaveGame();
				break;
			}
		}

		// Store game and display win logic if game is ended
		if(game.isGameEnded()){
			chrono::time_point<chrono::steady_clock> end = chrono::steady_clock::now();
			chrono::duration<double> elapsed_seconds = end-start; // @suppress("Invalid arguments")
			game.setPlayedDuration(elapsed_seconds.count());

			cout << "\nCongratulations !!" << endl;
			cout << "Winner is: " << game.getWinner() << endl;
			cout << "Game played time: " << game.getPlayedDuration() << " sec" << endl;

			games.push_back(game);
		}
		gameStatus = 0;
	}

	cout << "\n----------------------------------------------------------------------------------------------------------------------------------------------\n";
}

/*
  printGameHistory()
  Author: Prakash layo Magar
  Parameters:
  	  games: reference to vector of game class and prints
  Description: Prints game history
  Return Value: void.
 */

void printGameHistory(vector<Game> games){
	cout << "\n----------------------------------------------------------------------------------------------------------------------------------------------\n";

	if(games.size() == 0){
		cout << "Sorry, we don't have any history till now." << endl;
		return;
	}
	printTableHeader();

	for(int i = 0; i< games.size(); i++){
		games[i].toString();
	}
	cout << "\n----------------------------------------------------------------------------------------------------------------------------------------------\n";

}


/*
  searchGameHistory()
  Author: Prakash layo Magar
  Parameters:
  	  games: reference to vector of game class
  Description: Search previous games based on winner and prints
  Return Value: void.
 */


void searchGameHistory(vector<Game> games){
	string searchKey;
	cout << "\n----------------------------------------------------------------------------------------------------------------------------------------------\n";
	if(games.size() == 0){
		cout << "Sorry, we don't have any history till now." << endl;
		return;
	}
	cout << "Please enter winner to search: ";
	getline(cin >> ws, searchKey);
	printTableHeader();

	for(int i = 0; i< games.size(); i++){
		if(games[i].getWinner() == searchKey){
			games[i].toString();
		}
	}
	cout << "\n----------------------------------------------------------------------------------------------------------------------------------------------\n";

}

/*
  searchGameHistoryByDate()
  Author: Sudip Thapa
  Parameters:
  	  games: reference to vector of game class
  Description: Searches game history based on date and prints
  Return Value: void.
 */

void searchGameHistoryByDate(vector<Game> games){
	string searchKey;
	cout << "\n----------------------------------------------------------------------------------------------------------------------------------------------\n";
	if(games.size() == 0){
		cout << "Sorry, we don't have any history till now." << endl;
		return;
	}
	cout << "Please enter date (YYYY-MM-DD): ";
	getline(cin >> ws, searchKey);
	printTableHeader();
	for(int i = 0; i< games.size(); i++){
		if(games[i].isDate(searchKey)){
			games[i].toString();
		}
	}
	cout << "\n----------------------------------------------------------------------------------------------------------------------------------------------\n";
}

