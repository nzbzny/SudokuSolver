#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <string>
#include <ctime>
#include <chrono>

#ifndef SUDOKUSOLVER_H
#define SUDOKUSOLVER_H

class SudokuSolver {

	struct position { //position on the table
		int row;
		int col;
	};

	std::vector< std::vector<int> > puzzle;
	std::vector< std::vector< std::vector<int> > > options;
	std::vector< position > lockedCells;
	position currentCell;
	bool algorithmDone;

public:
	SudokuSolver();
	void tempInit();
	int init(int start);
	bool checkRow(int row, int value);
	bool checkColumn(int column, int value);
	bool checkBox(int row, int column, int value);
	bool checkAll(int row, int column, int value);
	void bruteForce();
	void print();
	void setNextCell(position lastCell);
	void setPreviousCell(position lastCell);
	bool finished();
	bool cellLocked(int row, int col);
};

#endif

//http://www.math.cornell.edu/~mec/Summer2009/meerkamp/Site/Solving_any_Sudoku_I.html

//TODO: still have to actually input the algorithm and run it. Also have to do testing on time to solve.
/*
*
* Try using std::chrono or ctime. My laptop is about to die and I don't have internet so I
* can't implement that right now, but that seems like it would be the easiest
*
*
*
* For the algorithm, the link above gives several different ones. Look at them and try them all,
* then time them, then work on writing your own algorithm for it.
*
*/
