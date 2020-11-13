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

// Colors setup
auto bold_cyan = [](ostream& os) -> ostream& {
  os << termcolor::bold << termcolor::cyan;
  return os;
};

auto bold_weak_red = [](ostream& os) -> ostream& {
  os << termcolor::bold << termcolor::color<255,104,125>;
  return os;
};

auto sub_title_color = bold_cyan;
auto error_color = bold_weak_red;
auto input_names_color = termcolor::color<242,216,164>;
auto reset = termcolor::reset;


// Handlers
void interactive(void);
void cmd_line(vector<string> args);




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

    cmd_line(opts);

    // for (unsigned int i = 0; i < opts.size();i++) {
    //   if (opts[i] == "-r" || opts[i] == "--rows")
    //     rows = stoi(opts[++i]);
    //     else if (opts[i] == "-c" || opts[i] == "--cols")
    //     cols = stoi(opts[++i]);
    //     else if (opts[i] == "-o" || opts[i] == "--obstacles")
    //     obstacles = stoi(opts[++i]);
    //     else if (opts[i] == "-f" || opts[i] == "--file")
    //     infile = opts[++i];
    //     else if (opts[i] == "-h" || opts[i] == "--heuristic")
    //     heuristic_name = opts[++i];
    //     else if (opts[i] == "-fp" || opts[i] == "--fillp") {
    //     percentage = true;
    //     fobstacles = stof(opts[++i]);
    //   } 
      
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
        cout << endl << error_color << "Sin solución." << reset << endl;
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
  interactive();
 


  return 0;
}

void cmd_line(vector<string> args) {

}

void interactive(void) {
  int rows = -1, cols = -1;  // Dimensiones de tablero
  char start_search = 'n';


  // Dimensiones  
  while (start_search != 's' && start_search != 'S') {
    while (rows < 0 || cols < 0) {
      cout << sub_title_color <<  "\n*Dimensiones" << reset        
           << input_names_color << "\n  Nº de filas    > "; cin >> rows;
      cout << "  Nº de columnas > "; cin >> cols;
      cout << reset;
    }

  Board parking_lot(rows,cols);

  //Puntos inicial y final 
  coordinates A, B;
  A.row = -1, A.col = -1;
  B.row = -1, B.col = -1;
  bool bad_point = true;
  
  do {
    cout << sub_title_color << "\n*Coordenadas puntos A y B\n Introduzca las coordenadas separadas por un espacio en blanco:\n" << reset;
    cout << input_names_color << "  Punto inicial ([0-" << rows - 1 << "], [0-" << cols - 1 <<  "]) >"; cin >> A.row >> A.col;
    cout << input_names_color << "  Punto final   ([0-" << rows - 1 << "], [0-" << cols - 1 <<  "]) >"; cin >> B.row >> B.col;
    cout << reset; 
    
    bad_point = A.row < 0 || A.col < 0 || A.row >= rows || A.col >= cols;
    bad_point = bad_point || B.row < 0 || B.col < 0 || B.col >= rows || B.col >= cols;
  } while (bad_point);
  parking_lot.set_init_point(A.row,A.col);
  parking_lot.set_final_point(B.row,B.col);



  //Nº obstáculos
  int opt = -1;    // Seleccionador de option
  while (opt < 0 || opt > 1) {
    cout << sub_title_color << "\n*Obstáculos\n" << reset
        << "  0. Por número\n"
        << "  1. Por porcentaje\n";
    cout << input_names_color << "  Seleccione una opción > "; cin >> opt;
    cout << reset;
  }

  int num_of_obstacles = -1;
  float fobstacles = -1;
  cout << endl;
  while (num_of_obstacles < 0) {
    if (opt == 0) { // Por número
      cout << input_names_color << "  Nº de obstáculos > "; cin >> num_of_obstacles;
    } else if (opt == 1) { // Por porcentaje
      fobstacles = -1;
      while (fobstacles < 0 || fobstacles > 1) {
        cout << input_names_color << "  Porcentaje de obstáculos [0, 1] > "; cin >> fobstacles;
      }
      num_of_obstacles = fobstacles * rows * cols;
    }
  }
  

  opt = -1;
  if (num_of_obstacles > 0) {
    while (opt < 0 || opt > 1) {
      cout << "\n  0. Manual"
           << "\n  1. Aleatorio\n"; 
      cout << input_names_color << "  Seleccione la disposición de los obstáculos > "; cin >> opt; 
      cout << reset;
    }
  }
  
  bool random_obstacles = opt == 1;

    if (random_obstacles) {
      parking_lot.fill_random_obstacles(num_of_obstacles);  
    } else {
      int row, col;
      cout << endl;
      for (int i = 0; i < num_of_obstacles; i++) {
        cout << input_names_color << "  Introduzca las coordenadas del\n"
            << "obstáculo " << i + 1 << " separadas por un espacio en blanco > "; cin >> row >> col;
        parking_lot.set_obstacle_at(row,col);
      }
      cout << reset;
    }


    // Heurística
    Heuristic* heuristic = nullptr;

    opt = -1;
    while (opt < 0 || opt > 1) {
      cout << sub_title_color <<  "\n*Heurística" << reset
           << "\n  0. Distancia Manhattan"
           << "\n  1. Distancia Euclidea (pitagórica)";
      cout << input_names_color << "\n  Seleccione una heurística >"; cin >> opt;
      cout << reset;
    }

    if (opt == 0)
      heuristic = new Manhattan();
      else if (opt == 1)
      heuristic = new Pythagorean();

    cout << endl << parking_lot << endl;
    cout << "Comenzar búsqueda? s/n > "; cin >> start_search;
    
    if (start_search == 's' || start_search == 'S') {
      Finder finder(&parking_lot);
      if (finder.find_path(A, B, heuristic)) {
        cout << endl << parking_lot << endl;
        cout << sub_title_color << "Coste del camino : " << reset << parking_lot.get_node_at(B).g_ << endl;
        cout << sub_title_color << "Nodos expandidos : " << reset << finder.closed_list().size() << endl;

      } else {
        cout << endl << sub_title_color << "Sin solución" << reset << endl;
      }
    }
  }
}