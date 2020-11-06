
#include "../include/Node.hpp"

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
      os << OBSTACLE_SYM;
      break;
    case stepped_:
      os << STEPPED_SYM;
      break;
    case initial_:
      os << INITIAL_SYM;
      break;
    case final_:
      os << FINAL_SYM;
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
      os << OBSTACLE_SYM;
      break;
    case stepped_:
      os << STEPPED_SYM;
      break;
    case initial_:
      os << INITIAL_SYM;
      break;
    case final_:
      os << FINAL_SYM;
      break;
    default:
      os << UNKNOWN_SYM;
  }
  return os;
}


