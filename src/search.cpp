/**
 * @author: Miguel Alejandro Martín Reyes
 * email : alu0101209777@ull.edu.es
 * @github: github.com/miguel-martinr
 * @date  : 20201110
 * @description: Programa que inicializa un tablero con obstáculos y encuentra el camino
 *              óptimo entre el punto A y el punto B.
 * @keywords: heuristic, A*, finder, AI, nodes, boards, game
 */

#include "../include/Board.hpp"
#include "../include/Finder.hpp"
#include "../include/termcolor/termcolor.hpp"

#include <iostream>
#include <set>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

using namespace std;





int main(int argc, char* argv[]) {

  int rows = 75;
  int cols = 75;
  int obstacles = 0;
  float fobstacles = 0;
  bool random_obstacles = true;
  coordinates A, B;
  int a_row, a_col, b_row, b_col;
  string heuristic_name = "manhattan";
  Heuristic* heuristic = nullptr;
  


  if (argc > 1) {
    vector<string> opts;
    string infile = "nonefile";
    bool percentage = false;


    for (int i = 1; i < argc; i++)
      opts.push_back(string(argv[i]));


    for (unsigned int i = 0; i < opts.size();i++) {
      if (opts[i] == "-r" || opts[i] == "--rows")
        rows = stoi(opts[++i]);
        else if (opts[i] == "-c" || opts[i] == "--cols")
        cols = stoi(opts[++i]);
        else if (opts[i] == "-o" || opts[i] == "--obstacles")
        obstacles = stoi(opts[++i]);
        else if (opts[i] == "-f" || opts[i] == "--file")
        infile = opts[++i];
        else if (opts[i] == "-h" || opts[i] == "--heuristic")
        heuristic_name = opts[++i];
        else if (opts[i] == "-fp" || opts[i] == "--fillp") {
        percentage = true;
        fobstacles = stof(opts[++i]);
      } 
      
    }

    if (regex_match(heuristic_name.c_str(), regex("(M|m)(anhattan)")))
      heuristic = new Manhattan;
      else if (regex_match(heuristic_name.c_str(), regex("((E|e)(uclidean)|(P|p)(ythagorean))")))
      heuristic = new Pythagorean();
    
      

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

      
      A = parking_lot.init_point();
      B = parking_lot.final_point();

      if (finder.find_path(A, B, heuristic)) {
        cout << endl << parking_lot << endl;
        cout << termcolor::green << "Costo del camino = " << termcolor::reset << parking_lot.get_node_at(B.row, B.col).g_ << endl;
      } else {
        cout << endl << "Sin solución." << endl;
      }
      return 0;
    }













    //Desde línea de comandos
    A.row = 0;
    A.col = 0;
    B.row = rows - 1;
    B.col = cols - 1;
    
    Board board(rows,cols);
    board.set_init_point(A.row, A.col);
    board.set_final_point(B.row, B.col);

    percentage ? board.fill_prandom_obstacles(fobstacles) : board.fill_random_obstacles(obstacles);
    
    cout << board << endl << endl;
    Finder a_star(&board);
    if (a_star.find_path(A, B, heuristic))  {
      cout << board << endl; 
      cout << termcolor::green << "Costo = " << termcolor::reset << board.get_node_at(B.row,B.col).g_ << endl;
      cout << termcolor::green << "Nodos expandidos = " << termcolor::reset << a_star.closed_list().size() << endl;
    } else {
      cout << endl << "Sin solución" << endl;
    }

    return 0;
  }







  //Interactivo
  char start_search = 'n';
  int opt = -1;


  while (start_search != 's' && start_search != 'S') {
    //Dimensiones
    cout << "\n*Nº de filas    > "; cin >> rows;
    cout << "*Nº de columnas > "; cin >> cols;
    Board parking_lot(rows,cols);

    //Puntos inicial y final 
    coordinates A, B;
    cout << "\n*Introduzca las coordenadas separadas por un espacio en blanco:\n" ;
    cout << "  Punto inicial > "; cin >> A.row >> A.col;
    parking_lot.set_init_point(A.row,A.col);
    

    cout << "  Punto final   > "; cin >> B.row >> B.col;
    parking_lot.set_final_point(B.row,B.col);


    //Nº obstáculos
    opt = -1;
    while (opt < 0 || opt > 1) {
      cout << "\n*Obstáculos\n"
          << "  0. Por número\n"
          << "  1. Por porcentaje\n";
      cout << "  Seleccione una opción > "; cin >> opt;
    }

    obstacles = -1;
    while (obstacles < 0) {
      if (opt == 0) {
        cout << "  Nº de obstáculos > "; cin >> obstacles;
      } else if (opt == 1) {
        fobstacles = -1;
        while (fobstacles < 0 || fobstacles > 1) {
          cout << "  Porcentaje de obstáculos [0,1] > "; cin >> fobstacles;
        }
        obstacles = fobstacles * rows * cols;
      }
    }    
      if (obstacles > 0) {
        cout << "\n  0. Manual\n"
            << "  1. Aleatorio\n"; 
        cout << "  Seleccione la disposición de los obstáculos > "; cin >> random_obstacles; 
      }
    if (random_obstacles) {
      parking_lot.fill_random_obstacles(obstacles);  
    } else {
      int row, col;
      for (int i = 0; i < obstacles; i++) {
        cout << "\nIntroduzca las coordenadas del\n"
            << "obstáculo " << i + 1 << " separadas por un espacio en blanco > "; cin >> row >> col;
        parking_lot.set_obstacle_at(row,col);
      }
    }

    
    if (heuristic != nullptr)
      delete heuristic;
    opt = -1;
    while (opt < 0 || opt > 1) {
      cout << "\n*Heurística"
           << "\n  0. Distancia Manhattan"
           << "\n  1. Distancia Euclidea (pitagórica)";
      cout << "\n  Seleccione una heurística >"; cin >> opt;
      if (opt == 0)
        heuristic = new Manhattan();
        else if (opt == 1)
        heuristic = new Pythagorean();
    }

    cout << endl << parking_lot << endl;
    cout << "Comenzar búsqueda? s/n > "; cin >> start_search;
    
    if (start_search != 'n' && start_search != 'N') {
      Finder finder(&parking_lot);
      if (finder.find_path(A, B, heuristic))
        cout << endl << parking_lot << endl;
        else
        cout << endl << "Sin solución" << endl;
    }
  }


  return 0;
}
