
/**
 * @author: Miguel Alejandro Martín Reyes
 * email : alu0101209777@ull.edu.es
 * @github: github.com/miguel-martinr
 * @date  : 20201110
 * @description: Clase que implementa un nodo.
 * 
 * @keywords: heuristic, A*, finder, AI, nodes, boards, game
 */
#include "../include/Node.hpp"
#include "../include/termcolor/termcolor.hpp"

#include <cassert>


Node::Node(int row, int col, node_type type) {
  row_ = row;
  col_ = col;
  type_ = type;
  is_closed_ = false;
  is_frontier_ = false;
  f_ = 0;
  g_ = 0;
  h_ = 0;
  parent_ = nullptr;
}

Node::~Node(void) {
  parent_ = nullptr;
}

bool Node::operator==(Node n) {
  return row_ == n.row_ && col_ == n.col_;
}

Node& Node::operator=(const Node& n) {
  row_ = n.row_;
  col_ = n.col_;
  type_ = n.type_;
  is_closed_ = n.is_closed_;
  is_frontier_ = n.is_frontier_;
  f_ = n.f_;
  g_ = n.g_;
  h_ = n.h_;
  parent_ = nullptr;

  return *this;
}

ostream& operator<<(ostream& os, const Node* n) {
  assert(n != nullptr);
  switch(n->type_) {
    case free_:
      os << FREE_SYM;
      break;
    case obstacle_:
      os << termcolor::color<169,169,169> << OBSTACLE_SYM << termcolor::reset;
      break;
    case stepped_:
      os << termcolor::blue << STEPPED_SYM << termcolor::reset;
      break;
    case initial_:
      os << termcolor::green << INITIAL_SYM << termcolor::reset;
      break;
    case final_:
      os << termcolor::green << FINAL_SYM << termcolor::reset;
      break;
    default:
      os << UNKNOWN_SYM;
  }
  return os;
}

ostream& operator<<(ostream& os, const Node& n) {
  switch(n.type_) {
    case free_:
      os << FREE_SYM;
      break;
    case obstacle_:
      os << termcolor::color<169,169,169> << OBSTACLE_SYM << termcolor::reset;
      break;
    case stepped_:
      os << termcolor::blue << STEPPED_SYM << termcolor::reset;
      break;
    case initial_:
      os << termcolor::green << INITIAL_SYM << termcolor::reset;
      break;
    case final_:
      os << termcolor::green << FINAL_SYM << termcolor::reset;
      break;
    default:
      os << UNKNOWN_SYM;
  }
  return os;
}



