#include "../../include/handlers/interactive.hpp"


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
    cout << input_names_color << "  Punto inicial ([0-" << rows - 1 << "], [0-" << cols - 1 <<  "]) > "; cin >> A.row >> A.col;
    cout << input_names_color << "  Punto final   ([0-" << rows - 1 << "], [0-" << cols - 1 <<  "]) > "; cin >> B.row >> B.col;
    cout << reset; 
    
    bad_point = A.row < 0 || A.col < 0 || A.row >= rows || A.col >= cols;
    bad_point = bad_point || B.row < 0 || B.col < 0 || B.col >= cols || B.col >= cols;
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
  cout << reset;
  

  opt = -1;
  if (num_of_obstacles > 0) {
    while (opt < 0 || opt > 1) {
      cout << "\n  0. Manual"
           << "\n  1. Aleatoria\n"; 
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
            << "  obstáculo " << i + 1 << " separadas por un espacio en blanco > "; cin >> row >> col;
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
      cout << input_names_color << "\n  Seleccione una heurística > "; cin >> opt;
      cout << reset;
    }

    if (opt == 0)
      heuristic = new Manhattan();
      else if (opt == 1)
      heuristic = new Pythagorean();

    cout << endl << parking_lot << endl;
    cout << input_names_color << "Comenzar búsqueda? s/n > "; cin >> start_search;
    cout << reset;
    
    if (start_search == 's' || start_search == 'S') {
      Finder finder(&parking_lot);
      if (finder.a_star(A, B, heuristic)) {
        cout << endl << parking_lot << endl;
        cout << sub_title_color << "\n  Costo de la solución: " << reset << parking_lot.get_node_at(B).g_;
        cout << sub_title_color << "\n  Nodos expandidos    : " << reset << finder.closed_list().size();
        cout << sub_title_color << "\n  Tiempo de búsqueda  : " << reset << finder.search_time() << " segundos ";
        cout << endl;
      } else {
        cout << endl << sub_title_color << "Sin solución" << reset << endl;
      }
    }
  }
}