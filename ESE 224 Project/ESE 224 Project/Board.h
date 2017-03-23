#pragma once
// this class organizes all the information for each stage of the board
#include "Record.h"
class Board {
	// private variables
private:
	int layout[4][4] = {(0,0,0,0),
						(0,0,0,0), 
						(0,0,0,0), 
						(0,0,0,0) };
	Record info;
	// public variables
public:	
	// constructors
	Board(){}
	void setScore(int score) {
		info.setScore(score);
	}
	// getters and setters
	int getScore() {
		return info.getScore();
	}
	void setStep(int step) {
		info.setStep(step);
	}
	int getStep() {
		return info.getStep();
	}
	void setLayout(int x, int y, int value) {
		layout[x][y] = value;
	}
	int getLayout(int x, int y) {
		return layout[x][y];
	}
};