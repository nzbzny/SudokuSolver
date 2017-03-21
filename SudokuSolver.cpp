#include "SudokuSolver.h"

SudokuSolver::SudokuSolver() {
	std::vector<int> temp = { 0,0,0,0,0,0,0,0,0 }; //initialize a temporary empty puzzle
	for (int i = 0; i < 9; i++) { //make it a 9 x 9
		puzzle.push_back(temp);
	}
	std::vector< std::vector<int> > tempMultiVector; //create a 2D vector for each row - one of the vectors is for the options that the row has
	tempMultiVector.push_back(temp);
	for (int i = 0; i < 9; i++) { //9 x 9 x 9 (for my own algorithm)
		options.push_back(tempMultiVector);
	}
	currentCell.row = 0;
	currentCell.col = 0;
	algorithmDone = false;
}

void SudokuSolver::tempInit() { //for testing - random sudoku i found and solved to test this program
	puzzle.at(0).at(0) = 8;
	puzzle.at(0).at(1) = 3;
	puzzle.at(0).at(4) = 6;
	puzzle.at(0).at(6) = 4;
	puzzle.at(0).at(7) = 7;

	puzzle.at(1).at(1) = 5;
	puzzle.at(1).at(3) = 3;

	puzzle.at(2).at(3) = 5;
	puzzle.at(2).at(4) = 4;
	puzzle.at(2).at(5) = 8;
	puzzle.at(2).at(8) = 9;

	puzzle.at(3).at(0) = 2;
	puzzle.at(3).at(2) = 3;
	puzzle.at(3).at(3) = 6;
	puzzle.at(3).at(5) = 4;
	puzzle.at(3).at(7) = 9;

	puzzle.at(4).at(1) = 9;
	puzzle.at(4).at(4) = 2;
	puzzle.at(4).at(7) = 6;

	puzzle.at(5).at(1) = 6;
	puzzle.at(5).at(3) = 9;
	puzzle.at(5).at(5) = 7;
	puzzle.at(5).at(6) = 3;
	puzzle.at(5).at(8) = 4;

	puzzle.at(6).at(0) = 5;
	puzzle.at(6).at(3) = 7;
	puzzle.at(6).at(4) = 8;
	puzzle.at(6).at(5) = 1;

	puzzle.at(7).at(5) = 6;
	puzzle.at(7).at(7) = 5;

	puzzle.at(8).at(1) = 4;
	puzzle.at(8).at(2) = 1;
	puzzle.at(8).at(4) = 9;
	puzzle.at(8).at(7) = 8;
	puzzle.at(8).at(8) = 7;

	lockedCells.push_back({ 0, 0 });
	lockedCells.push_back({ 0, 1 });
	lockedCells.push_back({ 0, 4 });
	lockedCells.push_back({ 0, 6 });
	lockedCells.push_back({ 0, 7 });

	lockedCells.push_back({ 1, 1 });
	lockedCells.push_back({ 1, 3 });

	lockedCells.push_back({ 2, 3 });
	lockedCells.push_back({ 2, 4 });
	lockedCells.push_back({ 2, 5 });
	lockedCells.push_back({ 2, 8 });

	lockedCells.push_back({ 3, 0 });
	lockedCells.push_back({ 3, 2 });
	lockedCells.push_back({ 3, 3 });
	lockedCells.push_back({ 3, 5 });
	lockedCells.push_back({ 3, 7 });

	lockedCells.push_back({ 4, 1 });
	lockedCells.push_back({ 4, 4 });
	lockedCells.push_back({ 4, 7 });

	lockedCells.push_back({ 5, 1 });
	lockedCells.push_back({ 5, 3 });
	lockedCells.push_back({ 5, 5 });
	lockedCells.push_back({ 5, 6 });
	lockedCells.push_back({ 5, 8 });

	lockedCells.push_back({ 6, 0 });
	lockedCells.push_back({ 6, 3 });
	lockedCells.push_back({ 6, 4 });
	lockedCells.push_back({ 6, 5 });

	lockedCells.push_back({ 7, 5 });
	lockedCells.push_back({ 7, 7 });

	lockedCells.push_back({ 8, 1 });
	lockedCells.push_back({ 8, 2 });
	lockedCells.push_back({ 8, 4 });
	lockedCells.push_back({ 8, 7 });
	lockedCells.push_back({ 8, 8 });
}

int SudokuSolver::init(int start) { //initialize the puzzle through user input - start is the row to input since this function is called iteratively to allow for user error
	std::string row;
	std::cout << "Input the puzzle. Where there are blank spaces, please input a 0\n";
	for (int i = start; i < 9; i++) {
		std::cout << "Row " << i + 1 << ":\n"; //user inputs rows 1 - 9
		std::cin >> row; //take in the input
		if (row.size() != 9) {
			std::cout << "Input the 9 digits for the row (a blank space is 0).\n"; //user inputs the puzzle row by row
			return i; //return to the current location if they don't input 9 chars
		}
		for (int j = 0; j < 9; j++) { //cycle through the string
			if (row.at(j) < 48 || row.at(j) > 57) { //if they input a non-numerical char
				std::cout << "Values must be between 0 and 9. Try again.\n";
				return i; //exit the function and retry the row
			}
			puzzle.at(i).at(j) = row.at(j) - 48; //else, add / replace the number to the table
			if (row.at(j) > 48 && row.at(j) < 58) { //if it's a nonzero number (initially filled)
				lockedCells.push_back({ i, j }); //this cell can't be changed by the algorithm
			}
		}
	}
	return 10; //success
}

bool SudokuSolver::checkRow(int row, int value) { //check if same number already in the row
	for (int j = 0; j < 9; j++) {
		if (puzzle.at(row).at(j) == value) { //failed
			return false;
		}
	} //else, success
	return true;
}

bool SudokuSolver::checkColumn(int column, int value) { //check if same number already in the column
	for (int i = 0; i < 9; i++) {
		if (puzzle.at(i).at(column) == value) { //failed
			return false;
		}
	} //else, success
	return true;
}

bool SudokuSolver::checkBox(int row, int column, int value) { //check if same number already in the box
	int boxRowStart = row / 3; //integer math to find start row for the box
	int boxColStart = column / 3; //integer math to find start column for the box
	for (int i = boxRowStart * 3; i < boxRowStart * 3 + 3; i++) { //uses rounding from integer division to find the start row
		for (int j = boxColStart * 3; j < boxColStart * 3 + 3; j++) { //uses rounding from integer division to find the start column
			if (puzzle.at(i).at(j) == value) { //failed
				return false;
			}
		}
	} //else, success
	return true;
}

bool SudokuSolver::checkAll(int row, int column, int value) {
	return checkRow(row, value) && checkColumn(column, value) && checkBox(row, column, value);
}

void SudokuSolver::bruteForce() {
	for (int i = currentCell.row; i < 9; i++) { //9 rows in the puzzle
		for (int j = currentCell.col; j < 9; j++) { //9 columns in the puzzle
			if (!cellLocked(i, j)) { //if the cell isn't part of the original puzzle
				if (puzzle.at(i).at(j) == 9) { //if it was already maxed out - so it doesn't just go forward then keep going back to the next cell
					puzzle.at(i).at(j) = 0; //reset the square for going backwards
					setPreviousCell({ i, j }); //go to the last cell
					while (cellLocked(currentCell.row, currentCell.col)) { //while the previous cell is locked and it needs to go back
						setPreviousCell({ currentCell.row, currentCell.col }); //send it back one more
					}
					if (currentCell.row == -1 && currentCell.col == -1) {
						algorithmDone = true; //finished - failed
					}
					return;
				}
				for (int k = puzzle.at(i).at(j) > 0 ? puzzle.at(i).at(j) + 1 : 1; k < 10; k++) { //9 options for the box (1 - 9) - if the box already has a value (reiterating through it) start at one more than that new value. If the box's value is at 0 (empty) then start at 1
					if (i == 1 && j == 2 && k == 9) { //TODO: testing to make a breakpoint - remove
						//std::string temp;
						//std::cin >> temp;
					}
					if (checkAll(i, j, k)) { //if the value k works for the row i and the column j
						std::cout << "\nrow: " << i << "\ncolumn: " << j << "\nattempt: " << k << "\nsucceeded";
						puzzle.at(i).at(j) = k; //set the square to value k
						setNextCell({ i, j }); //go to the next cell
						return;
					}
					else if (k == 9 && !checkAll(i, j, k)) { //if it doesn't work for any value
						std::cout << "\nrow: " << i << "\ncolumn: " << j << "\nfailed";
						puzzle.at(i).at(j) = 0; //set the current cell to 0 - for when going backwards to fix old values so that it gets a fresh start when going to the cell before it
						setPreviousCell({ i, j }); //return to the previous cell
						while (cellLocked(currentCell.row, currentCell.col)) { //if it's going back to a cell that's locked and it can't change
							setPreviousCell({ currentCell.row, currentCell.col }); //go back to the cell before that so it doesn't infinite loop
						}
						if (currentCell.row == -1 && currentCell.col == -1) {
							algorithmDone = true; //finished - failed
						}
						return; //exit the loop and reenter at the previous cell
					}
				}
			}
			setNextCell({ i, j }); //change the current cell to be the next one
		}
	}
	algorithmDone = true; //finished - succeeded
}

void SudokuSolver::print() { //print the puzzle
	std::cout << "\n\t";
	std::cout << "-------------------------------";
	std::cout << "\n\t|";
	for (int i = 0; i < 9; i++) {  //rows
								   //std::cout << "|";
		for (int j = 0; j < 9; j++) { //columns
			std::cout << " ";
			if (puzzle.at(i).at(j) == 0) { //blank spaces
				std::cout << " ";
			}
			else {
				std::cout << puzzle.at(i).at(j);
			}
			std::cout << " ";
			if ((j + 1) % 3 == 0) {
				std::cout << "|";
			}
		}
		std::cout << "\n\t";
		if ((i + 1) % 3 == 0 && i != 8) {
			std::cout << "|";
			for (int j = 0; j < 9; j++) {
				std::cout << "---";
				if ((j + 1) % 3 == 0) {
					std::cout << "|";
				}
			}
			std::cout << "\n\t";
		}
		if (i != 8) {
			std::cout << "|";
		}
	}
	std::cout << "-------------------------------";
	std::cout << "\n";
}

void SudokuSolver::setNextCell(position lastCell) { //to find the next cell value to go to when performing the algorithm
	if (lastCell.col < 8) { //if it's not at the last column
		currentCell.row = lastCell.row; //same row
		currentCell.col = lastCell.col + 1; //next column
	}
	else { //if it's at the last column
		currentCell.row = lastCell.row + 1; //next row
		currentCell.col = 0; //first column
	}
	if (lastCell.row == 8 && lastCell.col == 8) { //if it's at the last row and column (final value)
		currentCell.row = 10; //finished
		currentCell.col = 10; //finished
	}
}

void SudokuSolver::setPreviousCell(position lastCell) {
	if (lastCell.col > 0) { //if it's not at the first column
		currentCell.row = lastCell.row; //same row
		currentCell.col = lastCell.col - 1; //previous column
	}
	else { //if it is at the first column
		currentCell.row = lastCell.row - 1; //previous row
		currentCell.col = 8; //last column
	}
	if (lastCell.col == 0 && lastCell.row == 0) { //if first column and first row
		currentCell.row = -1;
		currentCell.col = -1;
	}
}

bool SudokuSolver::finished() {
	return algorithmDone;
}

bool SudokuSolver::cellLocked(int row, int col) { //determine if the cell is part of the original puzzle or not
	for (int cell = 0; cell < lockedCells.size(); cell++) { //iterate through locked cells
		if ((lockedCells.at(cell).row == row && lockedCells.at(cell).col == col)) { //if the cell is part of the original puzzle
			return true; //that cell cannot be used
		}
	}
	return false;
}

int main() {
	SudokuSolver solver;
	int initStart = 0;
	while (initStart != 10) {
	initStart = solver.init(initStart);
	}
	//solver.tempInit();
	solver.print();
	while (!solver.finished()) {
		solver.bruteForce();
		solver.print();
	}
	system("pause");
}
