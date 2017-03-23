#pragma once
// This creates the rank object used to store ranks for the rank board
#include "record.h"
#include <string>
using namespace std;
class Rank {
	// private variables
private:
	string userName = "DEFAULT";
	Record info;
	int rank;
	// public variables
public:
	// constructors
	Rank() {}
	
	// setters and getters
	void setUserName(string userName) {
		this->userName = userName;
	}
	string getUserName() {
		return userName;
	}
	void setInfo(Record info) {
		this->info = info;
	}
	Record getInfo() {
		return info;
	}
	void setRank(int rank) {
		this->rank = rank;
	}
	int getRank() {
		return rank;
	}
};