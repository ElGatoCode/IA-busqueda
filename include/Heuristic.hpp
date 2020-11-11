/**
 * @author: Miguel Alejandro Martín Reyes
 * email : alu0101209777@ull.edu.es
 * @github: github.com/miguel-martinr
 * @date  : 20201110
 * @description: Jerarquía de clases que implementan diferentes heurísticas.
 * 
 * @keywords: heuristic, A*, finder, AI, nodes, boards, game
 */
#pragma once

#include "Node.hpp"

#include <cmath>

using namespace std;

class Heuristic {
 public:
   virtual double calculate(Node* a, Node* b) = 0;
   virtual ~Heuristic(void) {}
 private:
};


class Manhattan : public Heuristic {
 public:
   Manhattan(void) {}
   ~Manhattan(void) {}

   double calculate(Node* a, Node* b) {
     return abs(b->row_ - a->row_) + abs(b->col_ - a->col_);
   }
};

class Pythagorean : public Heuristic {
  public:
    Pythagorean(void) {}
    ~Pythagorean(void) {}

    double calculate(Node* a, Node* b) {
      return sqrt((b->row_ - a->row_) * (b->row_ - a->row_) + (b->col_ - a->col_) * (b->col_ - a->col_));
    }
};