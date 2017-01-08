#include "SudokuSolver.h"

SudokuSolver::SudokuSolver() {
  std::vector<int> temp = {0,0,0,0,0,0,0,0,0};
  for (int i = 0; i < 9; i++) {
    puzzle.push_back(temp);
  }
  std::vector< std::vector<int> > tempMultiVector;
  tempMultiVector.push_back(temp);
  for (int i = 0; i < 9; i++) {
    options.push_back(tempMultiVector);
  }
}

void SudokuSolver::tempInit() { //for testing
  puzzle[0][0] = 8;
  puzzle[0][1] = 3;
  puzzle[0][4] = 6;
  puzzle[0][6] = 4;
  puzzle[0][7] = 7;

  puzzle[1][1] = 5;
  puzzle[1][3] = 3;

  puzzle[2][3] = 5;
  puzzle[2][4] = 4;
  puzzle[2][5] = 8;
  puzzle[2][8] = 9;

  puzzle[3][0] = 2;
  puzzle[3][2] = 3;
  puzzle[3][3] = 6;
  puzzle[3][5] = 4;
  puzzle[3][7] = 9;

  puzzle[4][1] = 9;
  puzzle[4][4] = 2;
  puzzle[4][7] = 6;

  puzzle[5][1] = 6;
  puzzle[5][3] = 9;
  puzzle[5][5] = 7;
  puzzle[5][6] = 3;
  puzzle[5][8] = 4;

  puzzle[6][0] = 5;
  puzzle[6][3] = 7;
  puzzle[6][4] = 8;
  puzzle[6][5] = 1;

  puzzle[7][5] = 6;
  puzzle[7][7] = 5;

  puzzle[8][1] = 4;
  puzzle[8][2] = 1;
  puzzle[8][4] = 9;
  puzzle[8][7] = 8;
  puzzle[8][8] = 7;
}

int SudokuSolver::init(int start) {
  std::string row;
  for (int i = start; i < 9; i++) {
    std::cout << "Row " << i + 1 << ":\n";
    std::cin >> row;
    while (row.size() != 9) {
      std::cout << "Input the 9 digits for the row (a blank space is 0).\n";
      return i;
    }
    for (int j = 0; j < 9; j++) {
      if (row[j] < 48 || row[j] > 57) {
        std::cout << "Values must be between 0 and 9. Try again.\n";
        return i;
      }
      puzzle.at(i).at(j) = row[j] - 48;
    }
  }
  return 10;
}

bool SudokuSolver::checkRow(int row, int value) {
  for (int j = 0; j < 9; j++) {
    if (puzzle[row][j] == value) {
      return false;
    }
  }
  return true;
}

bool SudokuSolver::checkColumn(int column, int value) {
  for (int i = 0; i < 9; i++) {
    if (puzzle[i][column] == value) {
      return false;
    }
  }
  return true;
}

bool SudokuSolver::checkBox(int row, int column, int value) {
  int boxRowStart = row / 3;
  int boxColStart = column / 3;
  for (int i = boxRowStart * 3; i < boxRowStart * 3 + 3; i++) { //uses rounding error from integer division to find the start position
    for (int j = boxColStart * 3; j < boxColStart * 3 + 3; j++) {
      if (puzzle[i][j] == value) {
        return false;
      }
    }
  }
  return true;
}

void SudokuSolver::print() {
  std::cout << "\n\t";
  std::cout << "-------------------------------";
  std::cout << "\n\t|";
  for (int i = 0; i < 9; i++) {  //rows
    //std::cout << "|";
    for (int j = 0; j < 9; j++) { //columns
      std::cout << " ";
      if (puzzle[i][j] == 0) { //blank spaces
        std::cout << " ";
      } else {
        std::cout << puzzle[i][j];
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

int main() {
  SudokuSolver solver;
/*  int initStart = 0;
  while (initStart != 10) {
    initStart = solver.init(initStart);
  }*/ //TODO: uncomment when finished
  solver.tempInit();
  solver.print();
}
