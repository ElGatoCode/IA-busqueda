#include "../include/Finder.hpp"

#include <list>


using namespace std;

Finder::Finder(Board* board) {
  board_ = board;
}

Finder::~Finder(void) {

}

bool Finder::find_path(int row1, int col1, int row2, int col2) { // A* search
  if (board_ == nullptr)
    return false;
  
  if (board_->get_node_at(row1,col1).type_ == obstacle_)
    return false;
  
  if (board_->get_node_at(row2,col2).type_ == obstacle_)
    return false;

  list<Node*> open_list;

  Heuristic* heuristic = new Manhattan();
  vector<Node*> neighbors;
  Node* s = board_->get_ptr_at(row1,col1);
  Node* goal = board_->get_ptr_at(row2,col2);

  s->g_ = 0;
  s->h_ = heuristic->calculate(s, goal);
  s->f_ = s->g_ + s->h_;

  open_list.push_front(s);
  s->is_closed_ = false;


  while (!open_list.empty()) {
  list<Node*>::iterator min_index = open_list.begin(), it;

    for (it = min_index; it != open_list.end(); it++)
      if ((*it)->f_ < (*min_index)->f_)
        min_index = it;

    Node* m = *(min_index);

    if (m == goal) {
      draw_path(m);
      delete heuristic;
      return true;
    }

    open_list.erase(min_index);

    m->is_closed_ = true;
    neighbors = board_->get_neighbors_at(m->row_, m->col_);
    for (auto n : neighbors) {
      if(n->is_closed_)
        continue;
      double cost = m->g_ + 1;
      if (!n->is_frontier_ || cost < n->g_) {
        n->g_ = cost;
        n->h_ = heuristic->calculate(n, goal);
        n->f_ = n->g_ + n->h_;
        n->parent_ = m;

        if (!n->is_frontier_) {
          open_list.push_front(n);
          n->is_frontier_ = true;
        } 
      }
    }
  }
  //No solution
  cout << "\nNo solution :(\n";
  delete heuristic;
  return false;
}


void Finder::draw_path(Node* goal) {
  assert(goal != nullptr);

  Node* node = goal->parent_;

  while (node->parent_ != nullptr) {
    node->type_ = stepped_;
    node = node->parent_;
  }
}

