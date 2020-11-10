#include "../include/Board.hpp"
#include "../include/termcolor/termcolor.hpp"

#include <stdlib.h>
#include <time.h>
#include <cmath>

void coordinates::operator()(int r, int c) {
  row = r;
  col = c;
}


Board::Board(int rows, int cols) {
  assert(rows >= 0 && cols >= 0 && "Bad board dimensions:(");
  //asserta para tamanio maximo
  grid_ = new Matrix<Node>(rows, cols);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++)
      grid_->at(i,j) = Node(i,j);
  num_of_obstacles_ = 0;
  init_point_(-1,-1);
  final_point_(-1,-1);
}


Board::Board(const Board& board) {
  grid_ = new Matrix<Node>(board.num_of_rows(), board.num_of_cols());
  for (int i = 0; i < num_of_rows(); i++)
    for (int j = 0; j < num_of_cols(); j++)
      grid_->at(i,j) = board.get_node_at(i,j);
}

Board::~Board(void) {
  delete grid_;
}

int Board::num_of_rows(void) const {
  return grid_->rows_num();
}

int Board::num_of_cols(void) const {
  return grid_->cols_num();
}

int Board::num_of_obstacles(void) const {
  return num_of_obstacles_;
}

coordinates Board::init_point(void) const {
  return init_point_;
}

coordinates Board::final_point(void) const {
  return final_point_;
}

bool Board::is_obstacle_at(int row, int col) {
  return get_node_at(row,col).type_ == obstacle_ || !grid_->is_good_pos(row,col);
}

Node& Board::get_node_at(int row, int col) {
  return grid_->at(row,col);
}

Node& Board::get_node_at(int row, int col) const {
  return grid_->at(row,col);
}

Node* Board::get_ptr_at(int row, int col) {
  assert(grid_->is_good_pos(row,col));
  vector<vector<Node>>::iterator it = grid_->grid_.begin() + row;
  return &(*(it->begin() + col));
}

void Board::set_obstacle_at(int row, int col) {
  get_node_at(row,col).type_ = obstacle_;
  num_of_obstacles_++;
}

void Board::set_stepped_at(int row, int col) {
  if (get_node_at(row,col).type_ == obstacle_)
    num_of_obstacles_--;
  get_node_at(row,col).type_ = stepped_;
}

vector<Node*> Board::get_neighbors_at(int row, int col) {
  vector<Node*> neighbors;
  //up 
  if(grid_->is_good_pos(row-1,col) && get_node_at(row-1,col).type_ != obstacle_) 
    neighbors.push_back(get_ptr_at(row-1,col));
  
  //right
  if (grid_->is_good_pos(row,col+1) && get_node_at(row,col+1).type_ != obstacle_)
    neighbors.push_back(get_ptr_at(row,col+1));

  //down
  if (grid_->is_good_pos(row+1,col) && get_node_at(row+1,col).type_ != obstacle_)
    neighbors.push_back(get_ptr_at(row+1,col));

  //left
  if (grid_->is_good_pos(row,col-1) && get_node_at(row,col-1).type_ != obstacle_)
    neighbors.push_back(get_ptr_at(row,col-1));

  return neighbors;
}
  
Board& Board::operator=(const Board& board) {
  grid_ = new Matrix<Node>(board.num_of_rows(), board.num_of_cols());
  for (int i = 0; i < num_of_rows(); i++)
    for (int j = 0; j < num_of_cols(); j++)
      grid_->at(i,j) = board.get_node_at(i,j);
  return *this;
}

void Board::load_board(istream& is) {
  int rows_num, cols_num;
  is >> rows_num >> cols_num;
  Board aux_board(rows_num, cols_num);
  *this = aux_board;
  for (int row = 0; row < num_of_rows(); row++)
    for (int col = 0; col < num_of_cols(); col++) {
      string sym;
      is >> sym;

      if (sym == OBSTACLE_SYM)
        set_obstacle_at(row,col);
      else if (sym == STEPPED_SYM)
        set_stepped_at(row,col);   
      else if (sym == INITIAL_SYM)
        set_init_point(row,col);
      else if (sym == FINAL_SYM)
        set_final_point(row,col);
      //else free o unknown
      
    } 
}


// void Board::resize(int rows, int cols) {
//   grid_->resize(rows, cols);
// }




void Board::set_init_point(int row, int col) {
  if(get_node_at(row,col).type_ != final_) {
    if(grid_->is_good_pos(init_point_.row, init_point_.col))
      get_node_at(init_point_.row, init_point_.col).type_ = free_;
    get_node_at(row,col).type_ = initial_;
    init_point_.row = row;
    init_point_.col = col;
  } 
}

void Board::set_final_point(int row, int col) {
  if(get_node_at(row,col).type_ != initial_) {
    if(grid_->is_good_pos(final_point_.row, final_point_.col))
      get_node_at(final_point_.row, final_point_.col).type_ = free_;
    get_node_at(row,col).type_ = final_;
    final_point_.row = row;
    final_point_.col = col;
  } 
}




/**
 * \brief Cambia el type_ de "num_of" nodos (aleatoriamente posicionados) a "obstacle_". 
 *        Se cambiarán todos los nodos posibles (excepto A y B) hasta llegar a num_of o 
 *        hasta quedarse sin nodos free_
 * \param num_of_cells Número de nodos a cambiar 
 */
void Board::fill_random_obstacles(int num_of) {  
  int row, col;
  srand(time(NULL));
  int area = num_of_rows() *  num_of_cols();

  num_of >= area - 2 ? num_of = area - 2 : num_of = num_of;

  while (num_of_obstacles() < num_of ) {
    row = rand() % num_of_rows();
    col = rand() % num_of_cols(); 
    node_type current_type = get_node_at(row,col).type_;
    if (current_type == free_ || current_type == stepped_)
        set_obstacle_at(row, col); 
  }
}



/**
 * \brief Igual que fill_random_obstacles pero usando porcentaje respecto al área 
 *        para calcular los nodos a cambiar. Si percentaje >= 1 entonces se cambiarán
 *        todos los nodos posibles (excepto A y B).
 * \param percentage Porcentaje de nodos a camnbiar 
 */ 
void Board::fill_prandom_obstacles(float percentage) {
  int num_of_obstacles = 0;
  int area = num_of_rows() * num_of_cols();
  percentage >= 1 ? num_of_obstacles = area - 2 : num_of_obstacles = percentage * area;
  fill_random_obstacles(num_of_obstacles);
}

  
   


ostream& Board::print(ostream& os) const {
  for (int i = 0; i < num_of_rows(); i++) {
    for (int j = 0; j < num_of_cols(); j++) {
      os << grid_->get_copy_of(i,j) << ' ';
    }
    os << '\n';
  }
  return os;
}



ostream& operator<<(ostream& os, const Board& board) {
   return board.print(os);
}
