/**
 * @author: Miguel Alejandro Martín Reyes
 * email : alu0101209777@ull.edu.es
 * @github: github.com/miguel-martinr
 * @date  : 20201110
 * @description: Clase que implementa un 'buscador' de caminos mínimos entre nodos.
 * 
 * @keywords: heuristic, A*, finder, AI, nodes, boards, game
 */
#pragma once

#include "Board.hpp"
#include "Heuristic.hpp"

#include <queue>
#include <string>

struct compare {
  bool operator()(Node* a, Node* b) {
    return a->f_ > b->f_;
  }
};

typedef priority_queue<Node*, vector<Node*>, compare> min_heap;

class Finder {
 public:
   Finder(Board* board = nullptr);
   ~Finder(void);

  
   bool find_path(coordinates start_pos, coordinates goal_pos, Heuristic* heuristic);
   void draw_path(Node* goal);

 private:
   Board* board_;
};
