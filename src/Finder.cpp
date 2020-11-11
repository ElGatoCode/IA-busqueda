/**
 * @author: Miguel Alejandro Martín Reyes
 * email : alu0101209777@ull.edu.es
 * @github: github.com/miguel-martinr
 * @date  : 20201110
 * @description: Clase que implementa un 'buscador' de caminos mínimos entre nodos.
 * 
 * @keywords: heuristic, A*, finder, AI, nodes, boards, game
 */
#include "../include/Finder.hpp"

#include <list>


using namespace std;

Finder::Finder(Board* board) {
  board_ = board;
}

Finder::~Finder(void) {

}

bool Finder::find_path(coordinates start_pos, coordinates goal_pos, Heuristic* heuristic) { // A* search
  if (board_ == nullptr)
    return false;
  
  if (board_->get_node_at(start_pos.row, start_pos.col).type_ == obstacle_)
    return false;
  
  if (board_->get_node_at(start_pos.row, start_pos.col).type_ == obstacle_)
    return false;
  
  if (heuristic == nullptr)
    Heuristic* heuristic = new Manhattan();



  list<Node*> open_list;

  vector<Node*> neighbors;

  Node* s = board_->get_ptr_at(start_pos.row, start_pos.col);
  Node* goal = board_->get_ptr_at(goal_pos.row, goal_pos.col);

  s->g_ = 0;
  s->h_ = heuristic->calculate(s, goal);
  s->f_ = s->g_ + s->h_;

  open_list.push_front(s);

  while (!open_list.empty()) {

  list<Node*>::iterator min_index = open_list.begin(), it;
    for (it = min_index; it != open_list.end(); it++) //Buscar nodo con mínimo f
      if ((*it)->f_ < (*min_index)->f_)
        min_index = it;

    Node* m = *(min_index);

    if (m == goal) {
      draw_path(m);
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

