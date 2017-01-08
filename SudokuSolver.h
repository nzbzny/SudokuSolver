#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string.h>

#ifndef SUDOKUSOLVER_H
#define SUDOKUSOLVER_H

class SudokuSolver {

std::vector< std::vector<int> > puzzle;
std::vector< std::vector< std::vector<int> > > options;

public:
  SudokuSolver();
  void tempInit();
  int init(int start);
  bool checkRow(int row, int value);
  bool checkColumn(int column, int value);
  bool checkBox(int row, int column, int value);
  void print();
};

#endif

//http://www.math.cornell.edu/~mec/Summer2009/meerkamp/Site/Solving_any_Sudoku_I.html
