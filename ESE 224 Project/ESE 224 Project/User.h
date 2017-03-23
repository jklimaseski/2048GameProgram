#pragma once
// this class organizes all of the data for each particular user
#include <string>
#include <vector>;
#include "Record.h"
using namespace std;
class User {
	// private variables
private:
	string name = "DEFAULT";
	string password = "default";
	Record best;
	vector<Record> history;
	int historySpot = 0;
	// public variables
public:
	// constructor
	User() {};
	// getters and setters
	void setName(string name) {
		this->name = name;
	}
	string getName() {
		return name;
	}
	void setPassword(string password) {
		this->password = password;
	}
	string getPassword() {
		return password;
	}
	void setBest(Record best) {
		this->best = best;
	}
	Record getBest() {
		return best;
	}
	void setHistory(Record history) {
		this -> history.push_back(history);
	}
	Record getHistory(int x) {
		return history[x];
	}
	// this was just to make life easier
	int getHistorySize() {
		return history.size();
	}
};