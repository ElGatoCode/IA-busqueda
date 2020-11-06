
#pragma once

#include "Matrix.hpp"
#include "Node.hpp"

#include <iostream>
#include <utility>
#include <fstream>

using namespace std;


struct coordinates {
  int row;
  int col;
  void operator()(int r, int co);
};


class Board {

 public:
   Board(int rows = 0, int cols = 0);
   Board(const Board& board);
   ~Board(void);

  
   int num_of_rows(void) const;
   int num_of_cols(void) const;
   int num_of_obstacles(void) const;
   coordinates init_point(void) const;
   coordinates final_point(void) const;
   
   bool is_obstacle_at(int row, int col);
   void set_obstacle_at(int row, int col);
   void set_stepped_at(int row, int col);
   vector<Node*> get_neighbors_at(int row, int col);

   Node& get_node_at(int row, int col);
   Node& get_node_at(int row, int col) const;
   Node* get_ptr_at(int row, int col);


   Board& operator=(const Board& board);
   void load_board(istream& is = cin);
  //  int num_of_obst(void) const;
  //  int num_of_stepped(void) const;
  //  int num_of_free(void) const;
  //  int cells_on_this_state(cell_state state) const;
  //  cell_state get_state_of_cell(int row, int col) const;
  //  bool is_goal(int row, int col);


   

  //  void set_state_of_cell(int row, int col, cell_state state);
  void set_init_point(int row, int col);
  void set_final_point(int row, int col);


  //  Cell& get_init_point(void);
  //  Cell& get_final_point(void);
  //  Cell get_cell(int row, int col) const;

  /**
   * \brief Changes the state of "num_of_cells" cells (randomly placed) to "state"
   * \param num_of_cells Number of cells to fill ( 0 <= num_of_cells < rows * cols)
   * \param state New state of those cells 
   */
  void fill_random_obstacles(int num_of);
  
  //  /**
  //   * \brief Like fill_random but using percentage of cells in board
  //   * \param percentage Percentage of cells to fill (0 <= percentage < 1)
  //   */ 
  //  void fill_prandom(float percentage, cell_state state);


  //  void resize(int rows, int cols);

  ostream& print(ostream& os = cout) const;
  friend ostream& operator<<(ostream& os, const Board& obj);

 private:

   Matrix<Node>* grid_;
   /** \brief Number of obstacles on board */
   int num_of_obstacles_; 
   coordinates init_point_;
   coordinates final_point_;
};