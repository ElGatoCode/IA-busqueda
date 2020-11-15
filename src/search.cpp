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


