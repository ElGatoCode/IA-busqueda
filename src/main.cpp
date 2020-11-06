#include "../include/Board.hpp"
#include "../include/Finder.hpp"

#include <iostream>
#include <set>
#include <fstream>

using namespace std;



int main(void) {
  int rows = 15;
  int cols = 15;
  int obstacles = 0;

  cout << "\nRows > "; cin >> rows;
  cout << "Cols > "; cin >> cols;
  cout << "Obstacles > "; cin >> obstacles;
  coordinates A, B;
  int a_row, a_col, b_row, b_col;

  cout << "A coordinates > "; cin >> a_row >> a_col;
  cout << "B coordinates > "; cin >> b_row >> b_col;

  A.row = a_row;
  A.col = a_col;

  B.row = b_row;
  B.col  = b_col;

  Board parking_lot(rows,cols);


  parking_lot.set_init_point(A.row,A.col);
  parking_lot.set_final_point(B.row,B.col);

  cout << parking_lot << endl;

  parking_lot.fill_random_obstacles(obstacles);  
  
  // cout << parking_lot << endl;
  
  Finder finder(&parking_lot);
  finder.find_path(A.row,A.col,B.row,B.col);
  
  cout << parking_lot << endl;


  // Board parking_lot;
  // ifstream input("input/board1.txt");
  // parking_lot.load_board(input);
  // input.close();
  // cout << parking_lot << endl;
  // Finder finder(&parking_lot);
  // coordinates a = parking_lot.init_point();
  // coordinates b = parking_lot.final_point();
  // finder.find_path(a.row, a.col, b.row, b.col);
  // cout << parking_lot << endl;

  return 0;
}
