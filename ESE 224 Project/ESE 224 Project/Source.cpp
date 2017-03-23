/*--------------------------------------------------------------------*/
/*							ESE 224 Project							  */
/*--------------------------------------------------------------------*/
/*			This program is generates the game 2042					  */

// all the imports of other class objects
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include "record.h" 
#include "User.h"
#include "Rank.h"
#include "Board.h"
using namespace std;

// using a structure for convenience 
struct zeroInfo {
	int numberOf;
	bool zero;
} zeroinfo;

// declaring a few static variables for that they can be called by all the functions
// without having to include passing it
static vector<User> users;
static vector<Rank> rankList;
static User active;
static bool advanced = false;
static stack<Board> boards;

// this method creates the start menu and collects any entered input while there
int startMenu() {
	system("cls"); // clears the console
	cout << "\n";	cout << "\n";
	cout << "\t ==================================================================================\n";
	cout << "\t|        ******          ********        *           *           *******           |\n";
	cout << "\t|       ********        **********       **         **          *********          |\n";
	cout << "\t|      **      **       **      **       **         **          **     **          |\n";
	cout << "\t|              **       **      **       **         **          **     **      +   |\n";
	cout << "\t|       ********        **      **       *************           *******     +++++ |\n";
	cout << "\t|      ********         **      **        ************           *******       +   |\n";
	cout << "\t|      **               **      **                  **          **     **          |\n";
	cout << "\t|      **               **      **                  **          **     **          |\n";
	cout << "\t|      *********        **********                  **          *********          |\n";
	cout << "\t|       *******          ********                   *            *******           |\n";
	cout << "\t ==================================================================================\n";
	cout << "\n";
	cout << "___________________________________________________________________________________________________";
	cout << "\n";	cout << "\n";
	cout << "\t\t\t\t 1 ->> QUICK START\n";
	cout << "\t\t\t\t 2 ->> SIGN IN\n";
	cout << "\t\t\t\t 3 ->> SIGN UP\n";
	cout << "\t\t\t\t 4 ->> RANKING LIST\n";
	cout << "\t\t\t\t 5 ->> EXIT\n";
	cout << "\t\t\t\t\t\t\t\t Jason Klimaseski 2016, Version 1.0\n";
	cout << "\t\t\t\t INPUT : ";
	int input;
	cin >> input;
	return input;

}

// this method displays the game board for each turn and collects the next entered move
char displayGame(Board board) {
	system("cls"); // clears the console
	cout << "***********************************************************************************\n";
	cout << "\t Score to Win: 2048   Current Score: " << board.getScore() << " Current Step: " << board.getStep() << "\n";
	cout << "___________________________________________________________________________________\n";
	cout << "\n";
	// this nest for loop runs through the board displaying each locations value
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << "\t\t" <<board.getLayout(i,j);
		}
		cout << "\n\n";
	}
	cout << "___________________________________________________________________________________\n";
	// different options for advanced users
	if (advanced)
		cout << "\t w - UP   s - DOWN   a - LEFT    d - RIGHT   b - GO BACK   p - EXIT \n";
	// different options for trial users
	else
		cout << "\t w - UP   s - DOWN   a - LEFT    d - RIGHT   p - EXIT \n";
	cout << "***********************************************************************************\n";
	cout << "\t\t\t\t INPUT : ";
	char input;
	cin >> input;
	return input;
}

// this method loads all the data used for the game from the text files (users, score, etc)
void loading() {
	cout << "\t**          *******        ****         *******      **   ***      **   ********\n";
	cout << "\t**          **   **       *** ***       **    **     **   ****     **   **    **\n";
	cout << "\t**          **   **      ***   ***      **    ***         ** **    **   **    **\n";
	cout << "\t**          **   **      ***   ***      **    ***    **   **  **   **   ********\n";
	cout << "\t**          **   **      *********      **    **     **   **   **  **         **\n";
	cout << "\t*******     *******      ***   ***      ********     **   **    ** **   **    **     **\n";
	cout << "\t*******     *******      ***   ***      ******       **   **     ****   ********     **\n";
	// this block loads the list of users and passwords from the text file
	ifstream fileIn;
	{
	fileIn.open("UserList.txt");
	// if not there we'll tell the user a particular error code for debugging before exiting
	if (fileIn.fail()) {
		system("cls"); // clears the console
		cout << "ERROR WITH GAME FILES\n";
		cout << "ERROR CODE: UL0001\n";
		system("pause");
		exit(1);
	}
	
	// using a temporary variable to store values into the users vector
	User user;
	while (!fileIn.eof()) {
		// getting in the user names
		string input;
		fileIn >> input;
		user.setName(input);
		// and passwords
		fileIn >> input;
		user.setPassword(input);
		// adding it to the users vector
		users.push_back(user);
	}
	// closing that file
	fileIn.close();
	}
	// it ran so fast that you can't see loading so I paused it 
	Sleep(500);

	system("cls"); // clears the console
	cout << "\t**          *******        ****         *******      **   ***      **   ********\n";
	cout << "\t**          **   **       *** ***       **    **     **   ****     **   **    **\n";
	cout << "\t**          **   **      ***   ***      **    ***         ** **    **   **    **\n";
	cout << "\t**          **   **      ***   ***      **    ***    **   **  **   **   ********\n";
	cout << "\t**          **   **      *********      **    **     **   **   **  **         **\n";
	cout << "\t*******     *******      ***   ***      ********     **   **    ** **   **    **     **    **\n";
	cout << "\t*******     *******      ***   ***      ******       **   **     ****   ********     **    **\n";
	// this block loads the rank list
	{
		// open the rank list file
		fileIn.open("RankList.txt");
		// if it can't be opened we display a particular error code before exiting
		if (fileIn.fail()) {
			system("cls"); // clears the console
			cout << "ERROR WITH GAME FILES\n";
			cout << "ERROR CODE: RL0001\n";
			system("pause");
			exit(1);
		}
		// using a temporary variable for filling the rank list vector
		Rank rank;
		while (!fileIn.eof()) {
			int input;
			// first we get the rank
			fileIn >> input;
			rank.setRank(input);
			// then the user
			string inputUser;
			fileIn >> inputUser;
			rank.setUserName(inputUser);
			// then the record info
			fileIn >> input;
			Record rec;
			// like score
			rec.setScore(input);
			fileIn >> input;
			// and step
			rec.setStep(input);
			// before putting it in rank
			rank.setInfo(rec);
			// and putting rank into the vector
			rankList.push_back(rank);
		}
		fileIn.close();
	}
	Sleep(500);

	system("cls"); // clears the console
	cout << "\t**          *******        ****         *******      **   ***      **   ********\n";
	cout << "\t**          **   **       *** ***       **    **     **   ****     **   **    **\n";
	cout << "\t**          **   **      ***   ***      **    ***         ** **    **   **    **\n";
	cout << "\t**          **   **      ***   ***      **    ***    **   **  **   **   ********\n";
	cout << "\t**          **   **      *********      **    **     **   **   **  **         **\n";
	cout << "\t*******     *******      ***   ***      ********     **   **    ** **   **    **     **    **    **\n";
	cout << "\t*******     *******      ***   ***      ******       **   **     ****   ********     **    **    **\n";
	// this block loads the history and records for particular users from their own text files
	{
		// this loops makes sure we go through all entered users from earlier
		for (int i = 0; i < users.size(); i++) {
			string name = users[i].getName();			
			fileIn.open(name + ".txt");
			// if we still can't open it then we display a particular error code before exiting
			if (fileIn.fail()) {
				system("cls"); // clears the console
				cout << "ERROR WITH GAME FILES\n";
				cout << "ERROR CODE: UD0001\n";
				system("pause");
				exit(1);
			}

			// reading in each users data for history
			while (!fileIn.eof()) {					
				int input;
				// using an temporary record variable
				Record inputRecord;
				// getting the score
				fileIn >> input;
				// there can't be an instance of it being just zero
				if (input != 0)					
					inputRecord.setScore(input);
				// getting the step
				fileIn >> input;
				// there can't be an instance of it being just zero
				if (input != 0) {
					inputRecord.setStep(input);
					// and setting th history for that user
					users[i].setHistory(inputRecord);
				}
				// resetting input
				input = NULL;
			}			
			// closing the file
			fileIn.close();
		}		
		Sleep(500);
	}
}

// this method saves the game to the users history and the history on file 
void save() {	
	// declaring my variables
	string name = active.getName();
	Board board = boards.top();
	
	// checking the new save value and adding it to the rank list if necessary
	for (int i = 0; i < rankList.size(); i++) {
		// shifting and putting in the current game before lesser scores
		if (rankList[i].getInfo().getScore() < board.getScore()) {
			// shifting rank list
			for (int j = rankList.size(); j >i+1; j--) {
				rankList[j - 2].setRank((rankList[j - 2].getRank() + 1)); 
				rankList[j - 1] = rankList[j - 2];
			}
			// adding the new value
			rankList[i].setUserName(name);
			Record rec;
			int number = board.getScore();
			rec.setScore(number);
			number = board.getStep();
			rec.setStep(number);
			rankList[i].setInfo(rec);
			rankList[i].setRank(rankList[i].getRank() - 1);
			break;
		}
		// equal setting ranks equal and inputting value
		if (rankList[i].getInfo().getScore() == board.getScore()) {
			// shifting rankList
			for (int j = rankList.size(); j >i+1; j--) {
				rankList[j - 2].setRank((rankList[j - 2].getRank() + 1));
				rankList[j - 1] = rankList[j - 2];
			}
			// adding the new value after the old one
			if (active.getName() > rankList[i].getUserName()) {
				rankList[i + 1].setUserName(name);
				rankList[i + 1].setRank(rankList[i].getRank() - 1);
				rankList[i].setRank(rankList[i].getRank() - 1);

				Record rec;
				int number = board.getScore();
				rec.setScore(number);
				number = board.getStep();
				rec.setStep(number);
				rankList[i+1].setInfo(rec);
			}
			else {
				// adding the new value before the old one
				rankList[i].setUserName(name);
				rankList[i+1].setRank(rankList[i].getRank() - 1);
				rankList[i].setRank(rankList[i].getRank() - 1);

				Record rec;
				int number = board.getScore();
				rec.setScore(number);
				number = board.getStep();
				rec.setStep(number);
				rankList[i].setInfo(rec);
			}
			break;
		}
	}

	// saving the rankList to file
	ofstream fileOut;
	fileOut.open("RankList.txt");
	// putting the old history
	for (int i = 0; i < 9; i++) {
		fileOut << rankList[i].getRank();
		fileOut << "\t";
		fileOut << rankList[i].getUserName();
		fileOut << "\t";
		fileOut << rankList[i].getInfo().getScore();
		fileOut << "\t";
		fileOut << rankList[i].getInfo().getStep();
		fileOut << "\n";
	}
	// putting the last one
	fileOut << rankList[9].getRank();
	fileOut << "\t";
	fileOut << rankList[9].getUserName();
	fileOut << "\t";
	fileOut << rankList[9].getInfo().getScore();
	fileOut << "\t";
	fileOut << rankList[9].getInfo().getStep();
	fileOut.close();



	// opening users file and saving scores to file
	Record record; 
	fileOut.open(name + ".txt");
	// putting the old history
	for (int i = 0; i < active.getHistorySize(); i++) {		
		record = active.getHistory(i);
		fileOut << record.getScore();
		fileOut << "\t";
		fileOut << record.getStep();
		fileOut << "\n";
		}
	// putting the new one
	fileOut << board.getScore();
	fileOut << "\t";
	fileOut << board.getStep();
	fileOut.close();
	// adding the new one to the active user
	record.setScore(board.getScore());
	record.setStep(board.getStep());
	active.setHistory(record);	
}

// this method handles the login of a user, verifying the user exists
void login() {
	string username, password;
	bool exists = false, pass = false;
	// keep looping until they want to exit or succeed in logins
	while (exists == false && pass == false) {
		system("cls"); // clears the console
		// allowing them to exit if mis clicked or something
		cout << "\t\t Enter exit for to return to menu \n";

		cout << "\t\tEnter a User Name: \n";
		cout << "\t\tInput: ";
		cin >> username;
		if (!username.compare("exit"))
			return;

		cout << "\n\t\tEnter a password for this account: \n";
		cout << "\t\tInput: ";		
		cin >> password;

		// checking that the username and password is correct
		for (int i = 0; i < users.size(); i++) {
			// if the username matches
			if (!username.compare(users[i].getName())) {
				exists = true;
				// if the password matches
				if (!password.compare(users[i].getPassword())) {
					pass = true;
					active = users[i];
					advanced = true;
					break;
				}
				// of it does not
				else {
					cout << "\t\t Incorrect username/password\n";
					system("pause");
					break;
				}
			}			
		}
		// unsuccessful login let them try again
		if (pass == false) {
			cout << "\t\t Incorrect username/password\n";
			system("pause");
		}
	}
}

// this method allows the user to create a new profile
void signUp() {
	User user;
	string username, password;
	boolean unique = false;
	// check that the username is unique
	while (unique == false) {
		system("cls"); // clears the console
		// allowing the user to exit if they wish
		cout << "\t\tEnter exit to return to the menu \n";
		cout << "\t\tEnter a User Name: \n";
		cout << "\t\tInput: ";
		cin >> username;
		if (!username.compare("exit"))
			return;
		// checking that the username isn't already used
		for (int i = 0; i < users.size(); i++) {
			if (!username.compare(users[i].getName())) {
				cout << "\t\tUser already exists, please try a different one\n";
				unique = false;
				system("pause");
				break;
			}
			else
				unique = true;
		}
	}
	// if the username is unique enter and save a password for the account
	cout << "\n\t\tEnter a password for this account: \n";
	cout << "\t\tInput: ";
	cin >> password;

	// create user file for their records
	ofstream fileOut;	
	fileOut.open(username + ".txt");	
	fileOut.close();

	// adding the user to the list of user names and passwords on file
	fileOut.open("UserList.txt");
	// reading the old ones
	for (int i = 0; i < users.size(); i++) {
		fileOut << users[i].getName();
		fileOut << "\t";
		fileOut << users[i].getPassword();
		fileOut << "\n";
	}
	// adding the new one
	fileOut << username;
	fileOut << "\t";
	fileOut << password;
	fileOut.close();

	// adding the new user to the users vector
	user.setName(username);
	user.setPassword(password);
	users.push_back(user);

}

//  this method displays the ranking board
void ranking() {

	system("cls"); // clears the console
	cout << "\n\n\n\n\n";
	cout << "\t\t\t\t Rankings: \n";
	cout << "\t\tRank\tUser Name\tScore\tStep Number\n";
	cout << "\t____________________________________________________________\n";
	// going through the rankList vector and displaying it
	for (int i = 0; i < rankList.size(); i++) {
		cout << "\t\t" << rankList[i].getRank() << "\t   " << rankList[i].getUserName() << "\t\t"
			<< rankList[i].getInfo().getScore() << "\t\t" << rankList[i].getInfo().getStep() << "\n";
	}
	system("pause");
}

// this method displays the best record of the active user 
void bestRec() {

	// goes through the users history of games and determines the best score
	Record record;
	for (int i = 0; i < active.getHistorySize(); i++) {
		if (active.getHistory(i).getScore() > record.getScore()) {
			record.setScore(active.getHistory(i).getScore());
			record.setStep(active.getHistory(i).getStep());
		}
	}
	// setting the users best
	active.setBest(record);

	// displaying the best record
	Record best = active.getBest();
	system("cls"); // clears the console
	cout << "\n\n\n\n\n";
	cout << "\t\t\t Best Record: \n";
	cout << "\t\tStep number: " << best.getStep() << "\n";
	cout << "\t\tScore : " << best.getScore() << "\n";	
	
	system("pause");
}

// this method displays the active users game history
void history(){

	Record history;
	// get how many values need to be loaded
	int stop = active.getHistorySize();
	system("cls"); // clears the console
	cout << "\n\n\n\n\n";
	cout << "\t\t\t Game History: \n";
	cout << "\tGame Number\tStep\tScore\n";
	cout << "\t____________________________________\n";
	// run through the history displaying each one
	for (int i = 0; i < stop; i++){
		history = active.getHistory(i);		
		cout << "\t" << i + 1 << "\t\t" << history.getStep() << "\t\t" << history.getScore() << "\n";		
	}
	system("pause");
	
}

// this method is for if the user has won the game
void gameWinner() {
	// tell them they won
	cout << "\n\t\tCongratulations!\n\t\t You have won! \n";
	// save the game to their history and rank list as necessary
	if(advanced == true)
		save();
	system("pause");
	// clearing the last games data
	boards.empty();
}

// this method is for if the user has lost the game
void gameLoser() {
	// tell them the game is over
	cout << "\n\t\t\t Game Over\n";
	// // save the game to their history and rank list as necessary
	if(advanced == true)
		save();
	system("pause");
	// clearing the stack
	boards.empty();
}

// this method generates new values for the zero every round 
Board generate(Board board) { 
	
	// count to decide how many numbers to generate
	int count;
	
	// we don't generate
	if (zeroinfo.numberOf == -1)
		return board;
	// if we have more than 2 zeros randomly decide how many to make
	else if(zeroinfo.numberOf > 2)
		count = rand() % 2 + 1;
	// otherwise more directly on how many zeros we have
	else
		count = rand() % zeroinfo.numberOf + 1;

	// loop through generating random location and random value for that location
	while (count > 0) {
		// random x value
		int randomX = rand() % 4;
		// random y value
		int randomY = rand() % 4;
		// random value
		int randomValue = 0;	
		randomValue = rand() % 4 + 1;
		// just to make sure we don't get any weird values
		if (randomValue < 4) 
				randomValue = 2;		
		// check if that spot is zero is it is then assign value otherwise we loop again
		if (board.getLayout(randomX, randomY) == 0) {
			board.setLayout(randomX, randomY, randomValue);
			count--;
		}
	}
	return board;
}

// this method handles the game play and user inputs there
void game() {

	// first declaring variables used
	Board board;
	bool combined = false;
	vector<int> numbers;
	int step = 0;
	int score = 0;
	
	// initially gonna need to generate numbers
	zeroinfo.numberOf = 2;

	while (1){
		// calls the generator class to generate new numbers for the board
		board = generate(board);

		// if we didn't generate don't save the board
		if (zeroinfo.numberOf != -1)
			boards.push(board);
		
		zeroinfo.numberOf = 0;
		zeroinfo.zero = false;
		// displays the board and gets the user inputs
		char select = displayGame(board);

		// depending on the users input shifts the board
		switch (select){
		case 'w':
		{
			// up
			// running through each variable in the array starting at the top
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 3; j++) {
					// getting the value at specific locations on the board
					int current = board.getLayout(j, i);
					int next = board.getLayout(j + 1, i);
					// if current value location is zero
					if (current == 0) {
						// and next is alo zero, here were going through looking
						// for the next non zero number to move it here
						if (next == 0 && j < 2) {
							next = board.getLayout(j + 2, i);
							if (next == 0 && j == 0) {
								next = board.getLayout(j + 3, i);
								if (next == 0)
									// all zeros so we move on
									break;
								else {
									// we reached the last value in this spot so we move it and break to next column
									board.setLayout(j + 3, i, current);
									board.setLayout(j, i, next);
									break;
								}

							}
							else {
								if (j == 0)
								{
									// if not zero checking if any more of the same value and combining as necessary
									if (next == board.getLayout(j + 3, i)) {
										board.setLayout(j + 3, i, 0);
										next *= 2;
									}
								}
								board.setLayout(j + 2, i, current);
								board.setLayout(j, i, next);
							}
						}
						if (next != 0) {
							// if not zero checking if any more of the same value and combining as necessary
							if (j < 2) {
								if (next == board.getLayout(j + 2, i) && combined == false) {
									next *= 2;
									board.setLayout(j + 2, i, 0);
									combined = true;
								}
								else if (j == 0) {
									if (next == board.getLayout(j + 3, i) && combined == false && board.getLayout(j + 2, i) == 0) {
										next *= 2;
										board.setLayout(j + 3, i, 0);
										combined = true;
									}
								}
							}
							board.setLayout(j + 1, i, current);
							board.setLayout(j, i, next);
						}
					}
					else if (current == next && combined == false) {
						next *= 2;
						board.setLayout(j, i, next);
						board.setLayout(j + 1, i, 0);
						combined = true;
					}
					else if (next == 0 && j < 2) {
						next = board.getLayout(j + 2, i);
						if (next == 0 && j == 0) {
							next = board.getLayout(j + 3, i);
							if (next == current && combined == false) {
								current *= 2;
								board.setLayout(j + 3, i, 0);
								board.setLayout(j, i, current);
							}
						}
						if (next == current && combined == false) {
							current *= 2;
							board.setLayout(j + 2, i, 0);
							board.setLayout(j, i, current);
						}

					}
				}
				// resetting combined for next column
				combined = false;
			}
			// searching through the board to determine this boards score
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					int value = board.getLayout(i, j);
					if (value > score) {
						score = value;
					}
					// checking if they won
					if (score == 2048) {
						gameWinner();
						return;
					}
					// checking that theres still zeros remaining
					if (value == 0) {
						zeroinfo.zero = true;
						zeroinfo.numberOf++;
					}
				}
			}
			// setting the boards score and step 
			board.setScore(score);
			step++;
			board.setStep(step);			
			break;
		}
		case 'a':
		{
			// left
			// running through each variable starting from the left side
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 3; j++) {
					// getting the values at current spot on board
					int current = board.getLayout(i, j);
					int next = board.getLayout(i, j + 1);
					if (current == 0) {
						// if zero checking the next value looking for a non zero value to move to this position
						if (next == 0 && j < 2) {
							next = board.getLayout(i, j + 2);
							if (next == 0 && j == 0) {
								next = board.getLayout(i, j + 3);
								if (next == 0)
									// all zeros move on to the next row
									break;
								else {
									// only one non zero move and move onto the next row
									board.setLayout(i, j + 3, current);
									board.setLayout(i, j, next);
									break;
								}

							}
							else {
								if (j == 0)
								{ // checking if next and last location same and combining for this row
									if (next == board.getLayout(i, j + 3)) {
										board.setLayout(i, j + 3, 0);
										next *= 2;
										combined = true;
									}
								}
								board.setLayout(i, j + 2, current);
								board.setLayout(i, j, next);
							}
						}
						if (next != 0) {
							// if not zero check to see if any other value is the same to be combined before moving it
							if (j < 2) {
								if (next == board.getLayout(i, j + 2) && combined == false) {
									next *= 2;
									board.setLayout(i, j + 2, 0);
									combined = true;
								}
								else if (j == 0) {
									if (next == board.getLayout(i, j + 3) && combined == false && board.getLayout(i, j + 2) == 0) {
										next *= 2;
										board.setLayout(i, j + 3, 0);
										combined = true;
									}
								}
							}
							board.setLayout(i, j + 1, current);
							board.setLayout(i, j, next);
						}
					}
					else if (current == next && combined == false) {
						next *= 2;
						board.setLayout(i, j, next);
						board.setLayout(i, j + 1, 0);
						combined = true;
					}
					else if (next == 0 && j < 2) {
						next = board.getLayout(i, j + 2);
						if (next == 0 && j == 0) {
							next = board.getLayout(i, j + 3);
							if (next == current && combined == false) {
								current *= 2;
								board.setLayout(i, j + 3, 0);
								board.setLayout(i, j, current);
							}
						}
						if (next == current && combined == false) {
							current *= 2;
							board.setLayout(i, j + 2, 0);
							board.setLayout(i, j, current);
						}

					}
				}
				// resetting combined for the next row
				combined = false;
			}

			// going though the board and finding the score for this board
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					int value = board.getLayout(i, j);
					if (value > score) {
						score = value;
					}
					// checking if they won
					if (score == 2048) {
						gameWinner();
						return;
					}
					// checking that theres still zeros remaining
					if (value == 0) {
						zeroinfo.zero = true;
						zeroinfo.numberOf++;
					}
				}
			}
			// setting the score and the step of this board 
			board.setScore(score);
			step++;
			board.setStep(step);
			break;
		}
		case 's':
		{
			// down
			// going through the entire board shifting the values down starting from the bottom
			for (int i = 0; i < 4; i++) {
				for (int j = 3; j > 0; j--) {
					// getting the current values to test
					int current = board.getLayout(j, i);
					int next = board.getLayout(j - 1, i);
					if (current == 0) {
						// if at a zero on board checking looking for a none zero value to put there
						if (next == 0 && j > 1) {
							next = board.getLayout(j - 2, i);
							if (next == 0 && j == 3) {
								next = board.getLayout(j - 3, i);
								if (next == 0)
									// all zeros move onto the next column
									break;
								else {
									// only one none zero so move it and move onto the next column
									board.setLayout(j - 3, i, current);
									board.setLayout(j, i, next);
									break;
								}

							}
							else {
								if (j == 3)
								{
									if (next == board.getLayout(j - 3, i)) {
										// last two were same value combine and move
										board.setLayout(j - 3, i, 0);
										next *= 2;
									}
								}
								board.setLayout(j - 2, i, current);
								board.setLayout(j, i, next);
							}
						}
						if (next != 0) {
							// if next is not zero compare to the rest of the column looking to see if it can be combined before the move
							if (j > 1) {
								if (next == board.getLayout(j - 2, i) && combined == false) {
									next *= 2;
									board.setLayout(j - 2, i, 0);
									combined = true;
								}
								else if (j == 3) {
									if (next == board.getLayout(j - 3, i) && combined == false && board.getLayout(j - 2, i) == 0) {
										next *= 2;
										board.setLayout(j - 3, i, 0);
										combined = true;
									}
								}
							}
							board.setLayout(j - 1, i, current);
							board.setLayout(j, i, next);
						}
					}
					else if (current == next && combined == false) {
						next *= 2;
						board.setLayout(j, i, next);
						board.setLayout(j - 1, i, 0);
						combined = true;
					}
					else if (next == 0 && j > 1) {
						next = board.getLayout(j - 2, i);
						if (next == 0 && j == 3) {
							next = board.getLayout(j - 3, i);
							if (next == current && combined == false) {
								current *= 2;
								board.setLayout(j - 3, i, 0);
								board.setLayout(j, i, current);
							}
						}
						if (next == current && combined == false) {
							current *= 2;
							board.setLayout(j - 2, i, 0);
							board.setLayout(j, i, current);
						}

					}
				}
				// resetting combined for the next column
				combined = false;
			}

			// going through the board and getting the score for this board
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					int value = board.getLayout(i, j);
					if (value > score) {
						score = value;
					}
					// checking if they won
					if (score == 2048) {
						gameWinner();
						return;
					}
					// checking that theres still zeros remaining
					if (value == 0) {
						zeroinfo.zero = true;
						zeroinfo.numberOf++;
					}
				}
			}
			// setting the score and the step for this board before pushing it onto the stack
			board.setScore(score);
			step++;
			board.setStep(step);
			break;
		}
		case 'd':
		{
			// right
			// moving values to the right starting from the right side
			for (int i = 0; i < 4; i++) {
				for (int j = 3; j > 0; j--) {
					// getting the current values
					int current = board.getLayout(i, j);
					int next = board.getLayout(i, j - 1);
					if (current == 0) {
						// if the current location is zero checking for a non zero next value
						if (next == 0 && j > 1) {
							next = board.getLayout(i, j - 2);
							if (next == 0 && j == 3) {
								next = board.getLayout(i, j - 3);
								// all zeros break and move onto the next row
								if (next == 0)
									break;
								else {
									// last value not zero moving and then moving onto the next row
									board.setLayout(i, j - 3, current);
									board.setLayout(i, j, next);
									break;
								}

							}
							else {
								if (j == 3)
								{
									// the last two values were the same so combine and move
									if (next == board.getLayout(i, j - 3)) {
										board.setLayout(i, j - 3, 0);
										next *= 2;
									}
								}
								board.setLayout(i, j - 2, current);
								board.setLayout(i, j, next);
							}
						}
						if (next != 0) {
							// next wasn't zero so check if it can be combined with another value on this row and then move it
							if (j > 1) {
								if (next == board.getLayout(i, j - 2) && combined == false) {
									next *= 2;
									board.setLayout(i, j - 2, 0);
									combined = true;
								}
								else if (j == 3) {
									if (next == board.getLayout(i, j - 3) && combined == false && board.getLayout(i, j - 2) == 0) {
										next *= 2;
										board.setLayout(i, j - 3, 0);
										combined = true;
									}
								}
							}
							board.setLayout(i, j - 1, current);
							board.setLayout(i, j, next);
						}
					}
					else if (current == next && combined == false) {
						next *= 2;
						board.setLayout(i, j, next);
						board.setLayout(i, j - 1, 0);
						combined = true;
					}
					else if (next == 0 && j > 1) {
						next = board.getLayout(i, j - 2);
						if (next == 0 && j == 3) {
							next = board.getLayout(i, j - 3);
							if (next == current && combined == false) {
								current *= 2;
								board.setLayout(i, j - 3, 0);
								board.setLayout(i, j, current);
							}
						}
						if (next == current && combined == false) {
							current *= 2;
							board.setLayout(i, j - 2, 0);
							board.setLayout(i, j, current);
						}

					}
				}
				// resetting the combine for the next row
				combined = false;
			}
			// searching though the board finding the score
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					int value = board.getLayout(i, j);
					if (value > score) {
						score = value;
					}
					// checking if they won
					if (score == 2048) {
						gameWinner();
						return;
					}
					// checking that theres still zeros remaining
					if (value == 0) {
						zeroinfo.zero = true;
						zeroinfo.numberOf++;
					}
				}
			}
			// setting the value of the score and step of this board before pushing it on the stack
			board.setScore(score);
			step++;
			board.setStep(step);
			break;
		}
		case 'b':
			// go back
			// checking that a user is logged in
			if (advanced == true) {
				// checking if empty
				if (!boards.empty()) {
					// if they are popping last board off and using the last one
					boards.pop();
					board = boards.top();
					zeroinfo.zero = true;
					zeroinfo.numberOf = -1;
				}
				else {
					// if empty 
					cout << "\t\t CAN'T GO BACK \n";
					system("pause");
					zeroinfo.zero = true;
					zeroinfo.numberOf = -1;
				}
			}
			else{
				cout << "\t\tINCORRECT INPUT\n";
				system("pause");
				zeroinfo.zero = true;
				zeroinfo.numberOf = -1;
			}
			break;
		case 'p':
			// exit
			return;
		default:
			cout << "\t\tINCORRECT INPUT\n";
			system("pause");
			zeroinfo.zero = true;
			zeroinfo.numberOf = -1;
		}
		// if they can't shift anymore then lose
		if (zeroinfo.zero == false) {
			gameLoser();
			return;
		}		

	}


}

// this method is the menu for selecting game, score, etc
void gameMenus() {
	// variable
	int select;
	// switch for if trial or advanced user
	switch (advanced) {
	case true:
		while (1) {
			// needs formating
			system("cls"); // clears the console
			cout << "\n\n\n\n\n";
			cout << "\t\t\tAdvanced User\n";
			cout << "\t__________________________________________________________\n";
			cout << "\t\t 1 ->> Start Game\n";
			cout << "\t\t 2 ->> Score History\n";
			cout << "\t\t 3 ->> Best Record\n";
			cout << "\t\t 4 ->> Exit\n";
			cout << "\t\t Input : ";
			cin >> select;
			switch (select) {
			case 1:
				game();
				break;
			case 2:
				history();
				break;
			case 3:
				bestRec();
				break;
			case 4:
				return;
			}
		}
		break;
	case false:
		while (1) {
			system("cls"); // clears the console
			cout << "\n\n\n\n\n";
			cout << "\t\t\t   Trial User\n";
			cout << "\t_____________________________________________________\n";
			cout << "\t\t\t 1 ->> Start Game\n";
			cout << "\t\t\t 2 ->> Exit\n";
			cout << "\t\t\t Input : ";
			cin >> select;
			switch (select) {
			case 1:
				game();
				break;
			case 2:
				return;
			}
		}
		break;
	}
}

// this is just a little method asking for confirmation of exiting
void exitPage() {
	while (1) {
		system("cls"); // clears the console
		cout << "\t\tAre you sure you want to exit? (y/n)\n";
		cout << "\t\tInput: ";
		char input;
		cin >> input;
		switch (input) {
			// check for capitals too
		case 'y':
			exit(1);
		case 'Y':
			exit(1);
		case 'n':
			return;
		case 'N':
			return;
		}
	}
	

}

// this method handles from the input from the main game menu
void run() {
	// what was clicked
	int startSelect;	

	// switching through to the appropriate case
	while (1) {
		startSelect = startMenu();
		switch (startSelect) {
		case 1:
			gameMenus();
			break;
		case 2:
			login();
			break;
		case 3:
			signUp();
			break;
		case 4:
			ranking();
			break;
		case 5:
			exitPage();
		default:
			cout << "\n\t\t\t INCORRECT INPUT\n";
			system("pause");
			break;
		}
	}
}

// our main driver for the program
void main() {
	loading();
	run();
	
}