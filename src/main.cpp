#include "../include/Board.hpp"
#include "../include/Finder.hpp"

#include <iostream>
#include <set>
#include <fstream>
#include <string>
#include <vector>

using namespace std;



int main(int argc, char* argv[]) {


  int rows = 75;
  int cols = 75;
  int obstacles = 0;

  int a_row, a_col, b_row, b_col;



  if (argc > 1) {
    vector<string> opts;
    
    for (int i = 1; i < argc; i++)
      opts.push_back(string(argv[i]));

    string argument;
    for (int i = 0; i < opts.size();i++) {
      if (opts[i] == "-r" || opts[i] == "--rows")
        rows = stoi(opts[++i]);
      else if (opts[i] == "-c" || opts[i] == "--cols")
        cols = stoi(opts[++i]);
      else if (opts[i] == "-o" || opts[i] == "--obstacles")
        obstacles = stoi(opts[++i]);
    }

    a_row = 0;
    a_col = 0;
    b_row = rows - 1;
    b_col = cols - 1;
    
    Board board(rows,cols);
    board.set_init_point(a_row,a_col);
    board.set_final_point(b_row,b_col);
    board.fill_random_obstacles(obstacles);
    cout << board << endl << endl;
    Finder a_star(&board);
    a_star.find_path(a_row, a_row, b_row, b_col);
    cout << board << endl;

    return 0;
  }


  cout << "\nRows > "; cin >> rows;
  cout << "Cols > "; cin >> cols;
  cout << "Obstacles > "; cin >> obstacles;
  coordinates A, B;
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
