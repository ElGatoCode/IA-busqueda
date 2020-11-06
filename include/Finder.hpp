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

  
   bool find_path(int row1, int col1, int row2, int col2);
   void draw_path(Node* goal);

 private:
   Board* board_;
};
