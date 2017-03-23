#pragma once
//	This class creates the record object used to store the 
//	score and step for a particular game or user
class Record{
	// private variables
private:
	int score = 0;
	int step = 0;
	// public variables
public:
	// constructors
	Record() {}

	// getters and setters
	void setScore(int score) {
		this -> score = score;
	}
	int getScore() {
		return score;
	}
	void setStep(int step) {
		this->step = step;
	}
	int getStep() {
		return step;
	}

};