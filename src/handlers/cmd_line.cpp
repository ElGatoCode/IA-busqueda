#include "../../include/handlers/cmd_line.hpp"
#include <regex>

void help(void) {
  cout << "  Opciones: \n\n" 
       << "-r o --rows num_filas Especifica el número de filas, por defecto es 75\n"
       << "-c o --cols num_columnas Especifica el número de columnas, por defecto es 75\n"
       << "-o o --obstacles num_obstaculos Especifica el número de obstáculos (posiciones aleatorias), por defecto es 0. \n"
       << "Nota: si se especifica un num_obstaculos mayor o igual que el área se colocarán area - 2 obstáculos como máximo. \n"
       << "-f o --file nombre_fichero Especifica un fichero con el tablero a cargar (vea [Formatos](#formatos) para más información) \n"
       << "-fp o --fillp porcentaje Especifica el porcentaje de obstáculos del tablero (posiciones aleatorias), por defecto es 0.0. (0 <= porcentaje <= 1) \n"
       << "Nota: si se especifica un porcentaje mayor o igual que 1 se colocarán area - 2 obstáculos como máximo. \n"
       << "-h o --heuristic heuristica Especifica la heurística a utilizar (vea [Heurísticas](#heuristicas) para más información) \n"
       << "--coord.a row col Especifica las coordenadas del punto inicial (row, col), por defecto son (0, 0) \n"
       << "--coord.b row col Especifica las coordenadas del punto final (row, col), por defecto son (rows -1, cols -1) \n";
}

void cmd_line(vector<string> args) {
  int rows = 75, cols = 75; // Dimensiones
  int num_of_obstacles = 0;
  bool by_percentage = false, print = true;
  bool from_file = false;
  float percentage = 0; // Porcentaje de obstáculos
  string file_name, heuristic_name = "Manhattan";
  coordinates A, B;
  A(0, 0);
  B(-1, -1);

  for (unsigned int i = 0; i < args.size();i++) {
  if (args[i] == "-r" || args[i] == "--rows")
    rows = stoi(args[++i]);
    else if (args[i] == "-c" || args[i] == "--cols")
    cols = stoi(args[++i]);
    else if (args[i] == "-o" || args[i] == "--obstacles")
    num_of_obstacles = stoi(args[++i]);
    else if (args[i] == "-h" || args[i] == "--heuristic")
    heuristic_name = args[++i];
    else if (args[i] == "--no-print")
    print = false;
    else if (args[i] == "--coord.a" || args[i] == "--coord.A") {
      int rowind = ++i;
      int colwind = ++i;
      A(stoi(args[rowind]), stoi(args[colwind]));
    }
    else if (args[i] == "--coord.b" || args[i] == "--coord.B") {
      int rowind = ++i;
      int colwind = ++i;
      B(stoi(args[rowind]), stoi(args[colwind]));
    }
    else if (args[i] == "-f" || args[i] == "--file") {
    from_file = true;
    file_name = args[++i];
    }
    else if (args[i] == "-fp" || args[i] == "--fillp") {
    percentage = stof(args[++i]);
    percentage = abs(percentage);
    percentage > 1 ? percentage = 1 : true;
    } 
  }
  
  // Tablero
  Board parking_lot(rows, cols);

  if (from_file) {
    ifstream inputf(file_name);
    if (!inputf.is_open()) {
      cout << error_color << "\nError al abrir fichero <<" << file_name << ">> :(" << reset << endl;
      return;
    }
    
    parking_lot.load_board(inputf);
    A = parking_lot.init_point();
    B = parking_lot.final_point();
    
    inputf.close();
  } else {

    B.row < 0 ? B.row = rows - 1 : true;
    B.col < 0 ? B.col = cols - 1 : true;

    parking_lot.set_init_point(A);
    parking_lot.set_final_point(B);
  }

  if (by_percentage)
    parking_lot.fill_prandom_obstacles(percentage);
    else
    parking_lot.fill_random_obstacles(num_of_obstacles);
  


  // Heurística
  Heuristic* heuristic = nullptr;
  if (regex_match(heuristic_name.c_str(), regex("(M|m)(anhattan)")))
    heuristic = new Manhattan;
    else if (regex_match(heuristic_name.c_str(), regex("((E|e)(uclidean)|(P|p)(ythagorean))")))
    heuristic = new Pythagorean();
    else {
    cout << error_color << "No se reconoce la heurística <<" << heuristic_name << ">> :(" << reset << endl;
    return;
    }

  if (print)
    cout << endl << parking_lot << endl;

  // Buscando camino
  Finder finder(&parking_lot);
  if (finder.a_star(A, B, heuristic)) {
    if (print)
      cout << parking_lot << endl;
    cout << sub_title_color << "\n  Costo de la solución: " << parking_lot.get_node_at(B).g_ << reset << endl;
    cout << sub_title_color << "\n  Nodos expandidos    : " << finder.closed_list().size() << reset << endl;
  } else {
    cout << error_color << "\n  No hay solución :(" << reset << endl;
  }
}


