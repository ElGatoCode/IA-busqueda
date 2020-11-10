#include "../include/Board.hpp"
#include "../include/Finder.hpp"
#include "../include/termcolor/termcolor.hpp"

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
  bool random_obstacles = true;
  int a_row, a_col, b_row, b_col;
 


  if (argc > 1) {
    vector<string> opts;
    string infile = "nonefile";
    for (int i = 1; i < argc; i++)
      opts.push_back(string(argv[i]));

    string argument;
    for (unsigned int i = 0; i < opts.size();i++) {
      if (opts[i] == "-r" || opts[i] == "--rows")
        rows = stoi(opts[++i]);
      else if (opts[i] == "-c" || opts[i] == "--cols")
        cols = stoi(opts[++i]);
      else if (opts[i] == "-o" || opts[i] == "--obstacles")
        obstacles = stoi(opts[++i]);
      else if (opts[i] == "-f" || opts[i] == "--file")
        infile = opts[++i];
    }

    //Desde fichero
    if (infile != string("nonefile")) {
      ifstream in_board(infile);
      if (!in_board.is_open()) {
        cout << "\nError al abrir fichero.\n\n";
        return -1;
      } 
      Board parking_lot;
      parking_lot.load_board(in_board);
      in_board.close();
      Finder finder(&parking_lot);
      cout << endl << parking_lot << endl;
      coordinates A, B;
      A = parking_lot.init_point();
      B = parking_lot.final_point();
      if (finder.find_path(A.row, A.col, B.row, B.col))
        cout << endl << parking_lot << endl;
        else
        cout << endl << "Sin solución." << endl;
      return 0;
    }

    //Desde línea de comandos
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
    if (a_star.find_path(a_row, a_row, b_row, b_col))
      cout << board << endl;
      else 
      cout << endl << "Sin solución" << endl;

    return 0;
  }


  //Interactivo
  char start_search = 'n';
  while (start_search != 's' && start_search != 'S') {

    cout << "\n*Nº de filas    > "; cin >> rows;
    cout << "*Nº de columnas > "; cin >> cols;
    Board parking_lot(rows,cols);
    
    coordinates A, B;
    cout << "\n*Introduzca las coordenadas separadas por un espacio en blanco:\n" ;
    cout << "  Punto inicial > "; cin >> A.row >> A.col;
    parking_lot.set_init_point(A.row,A.col);
    

    cout << "  Punto final   > "; cin >> B.row >> B.col;
    parking_lot.set_final_point(B.row,B.col);

    cout << "\n*Nº Obstáculos  > "; cin >> obstacles;
    if (obstacles > 0) {
      cout << "  0. Manual\n"
          << "  1. Aleatorio\n"; 
      cout << "\n  Seleccione la disposición de los obstáculos > "; cin >> random_obstacles; 
    }


    if (random_obstacles) {
      parking_lot.fill_random_obstacles(obstacles);  
    } else {
      int row, col;
      for (int i = 0; i < obstacles; i++) {
        cout << "\nIntroduzca las coordenadas del\n"
            << "obstáculo separadas por un espacio en blanco> "; cin >> row >> col;
        parking_lot.set_obstacle_at(row,col);
      }
    }

    cout << endl << parking_lot << endl;
    cout << "Comenzar búsqueda? s/n > "; cin >> start_search;
    
    if (start_search != 'n' && start_search != 'N') {
      Finder finder(&parking_lot);
      if (finder.find_path(A.row,A.col,B.row,B.col))
        cout << endl << parking_lot << endl;
        else
        cout << endl << "Sin solución" << endl;
    }
  }


  return 0;
}
