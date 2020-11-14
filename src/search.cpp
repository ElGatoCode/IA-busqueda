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
#include "../include/handlers/cmd_line.hpp"
#include "../include/handlers/interactive.hpp"



#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;




// // Handlers
// void interactive(void);
// void cmd_line(vector<string> args);




int main(int argc, char* argv[]) {


  if (argc > 1) {
    // Línea de comandos
    vector<string> args;
    for (int i = 1; i < argc; i++)
      args.push_back(string(argv[i]));

    cmd_line(args);
  } else {
    // Interactivo
    interactive();
  }

  return 0;
}


// void cmd_line(vector<string> args) {
//   int rows = 75, cols = 75; // Dimensiones
//   int num_of_obstacles = 0;
//   bool by_percentage = false;
//   bool from_file = false;
//   float percentage = 0; // Porcentaje de obstáculos
//   string file_name, heuristic_name = "Manhattan";
//   coordinates A, B;
//   A(0, 0);
//   B(-1, -1);

//   for (unsigned int i = 0; i < args.size();i++) {
//   if (args[i] == "-r" || args[i] == "--rows")
//     rows = stoi(args[++i]);
//     else if (args[i] == "-c" || args[i] == "--cols")
//     cols = stoi(args[++i]);
//     else if (args[i] == "-o" || args[i] == "--obstacles")
//     num_of_obstacles = stoi(args[++i]);
//     else if (args[i] == "-h" || args[i] == "--heuristic")
//     heuristic_name = args[++i];
//     else if (args[i] == "--coord.a" || args[i] == "--coord.A") {
//       int rowind = ++i;
//       int colwind = ++i;
//       A(stoi(args[rowind]), stoi(args[colwind]));
//     }
//     else if (args[i] == "--coord.b" || args[i] == "--coord.B") {
//       int rowind = ++i;
//       int colwind = ++i;
//       B(stoi(args[rowind]), stoi(args[colwind]));
//     }
//     else if (args[i] == "-f" || args[i] == "--file") {
//     from_file = true;
//     file_name = args[++i];
//     }
//     else if (args[i] == "-fp" || args[i] == "--fillp") {
//     percentage = stof(args[++i]);
//     percentage = abs(percentage);
//     percentage > 1 ? percentage = 1 : true;
//     } 
//   }
  
//   // Tablero
//   Board parking_lot(rows, cols);

//   if (from_file) {
//     ifstream inputf(file_name);
//     if (!inputf.is_open()) {
//       cout << error_color << "\nError al abrir fichero <<" << file_name << ">> :(" << reset << endl;
//       return;
//     }
    
//     parking_lot.load_board(inputf);
//     inputf.close();
//   }

//   B.row < 0 ? B.row = rows - 1 : true;
//   B.col < 0 ? B.col = cols - 1 : true;

//   parking_lot.set_init_point(A);
//   parking_lot.set_final_point(B);

//   if (by_percentage)
//     parking_lot.fill_prandom_obstacles(percentage);
//     else
//     parking_lot.fill_random_obstacles(num_of_obstacles);
  


//   // Heurística
//   Heuristic* heuristic = nullptr;
//   if (regex_match(heuristic_name.c_str(), regex("(M|m)(anhattan)")))
//     heuristic = new Manhattan;
//     else if (regex_match(heuristic_name.c_str(), regex("((E|e)(uclidean)|(P|p)(ythagorean))")))
//     heuristic = new Pythagorean();
//     else {
//     cout << error_color << "No se reconoce la heurística <<" << heuristic_name << ">> :(" << reset << endl;
//     return;
//     }

//   cout << endl << parking_lot << endl;

//   // Buscando camino
//   Finder finder(&parking_lot);
//   if (finder.a_star(A, B, heuristic)) {
//     cout << parking_lot << endl;
//     cout << sub_title_color << "\n  Costo de la solución: " << parking_lot.get_node_at(B).g_ << reset << endl;
//     cout << sub_title_color << "\n  Nodos expandidos    : " << finder.closed_list().size() << reset << endl;
//   } else {
//     cout << error_color << "\n  No hay solución :(" << reset << endl;
//   }
// }

// void interactive(void) {
//   int rows = -1, cols = -1;  // Dimensiones de tablero
//   char start_search = 'n';


//   // Dimensiones  
//   while (start_search != 's' && start_search != 'S') {
//     while (rows < 0 || cols < 0) {
//       cout << sub_title_color <<  "\n*Dimensiones" << reset        
//            << input_names_color << "\n  Nº de filas    > "; cin >> rows;
//       cout << "  Nº de columnas > "; cin >> cols;
//       cout << reset;
//     }

//   Board parking_lot(rows,cols);

//   //Puntos inicial y final 
//   coordinates A, B;
//   A.row = -1, A.col = -1;
//   B.row = -1, B.col = -1;
//   bool bad_point = true;
  
//   do {
//     cout << sub_title_color << "\n*Coordenadas puntos A y B\n Introduzca las coordenadas separadas por un espacio en blanco:\n" << reset;
//     cout << input_names_color << "  Punto inicial ([0-" << rows - 1 << "], [0-" << cols - 1 <<  "]) >"; cin >> A.row >> A.col;
//     cout << input_names_color << "  Punto final   ([0-" << rows - 1 << "], [0-" << cols - 1 <<  "]) >"; cin >> B.row >> B.col;
//     cout << reset; 
    
//     bad_point = A.row < 0 || A.col < 0 || A.row >= rows || A.col >= cols;
//     bad_point = bad_point || B.row < 0 || B.col < 0 || B.col >= rows || B.col >= cols;
//   } while (bad_point);
//   parking_lot.set_init_point(A.row,A.col);
//   parking_lot.set_final_point(B.row,B.col);



//   //Nº obstáculos
//   int opt = -1;    // Seleccionador de option
//   while (opt < 0 || opt > 1) {
//     cout << sub_title_color << "\n*Obstáculos\n" << reset
//         << "  0. Por número\n"
//         << "  1. Por porcentaje\n";
//     cout << input_names_color << "  Seleccione una opción > "; cin >> opt;
//     cout << reset;
//   }

//   int num_of_obstacles = -1;
//   float fobstacles = -1;
//   cout << endl;
//   while (num_of_obstacles < 0) {
//     if (opt == 0) { // Por número
//       cout << input_names_color << "  Nº de obstáculos > "; cin >> num_of_obstacles;
//     } else if (opt == 1) { // Por porcentaje
//       fobstacles = -1;
//       while (fobstacles < 0 || fobstacles > 1) {
//         cout << input_names_color << "  Porcentaje de obstáculos [0, 1] > "; cin >> fobstacles;
//       }
//       num_of_obstacles = fobstacles * rows * cols;
//     }
//   }
  

//   opt = -1;
//   if (num_of_obstacles > 0) {
//     while (opt < 0 || opt > 1) {
//       cout << "\n  0. Manual"
//            << "\n  1. Aleatorio\n"; 
//       cout << input_names_color << "  Seleccione la disposición de los obstáculos > "; cin >> opt; 
//       cout << reset;
//     }
//   }
  
//   bool random_obstacles = opt == 1;

//     if (random_obstacles) {
//       parking_lot.fill_random_obstacles(num_of_obstacles);  
//     } else {
//       int row, col;
//       cout << endl;
//       for (int i = 0; i < num_of_obstacles; i++) {
//         cout << input_names_color << "  Introduzca las coordenadas del\n"
//             << "obstáculo " << i + 1 << " separadas por un espacio en blanco > "; cin >> row >> col;
//         parking_lot.set_obstacle_at(row,col);
//       }
//       cout << reset;
//     }


//     // Heurística
//     Heuristic* heuristic = nullptr;

//     opt = -1;
//     while (opt < 0 || opt > 1) {
//       cout << sub_title_color <<  "\n*Heurística" << reset
//            << "\n  0. Distancia Manhattan"
//            << "\n  1. Distancia Euclidea (pitagórica)";
//       cout << input_names_color << "\n  Seleccione una heurística >"; cin >> opt;
//       cout << reset;
//     }

//     if (opt == 0)
//       heuristic = new Manhattan();
//       else if (opt == 1)
//       heuristic = new Pythagorean();

//     cout << endl << parking_lot << endl;
//     cout << "Comenzar búsqueda? s/n > "; cin >> start_search;
    
//     if (start_search == 's' || start_search == 'S') {
//       Finder finder(&parking_lot);
//       if (finder.a_star(A, B, heuristic)) {
//         cout << endl << parking_lot << endl;
//         cout << sub_title_color << "Coste del camino : " << reset << parking_lot.get_node_at(B).g_ << endl;
//         cout << sub_title_color << "Nodos expandidos : " << reset << finder.closed_list().size() << endl;

//       } else {
//         cout << endl << sub_title_color << "Sin solución" << reset << endl;
//       }
//     }
//   }
// }