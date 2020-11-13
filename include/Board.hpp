/**
 * @author: Miguel Alejandro Martín Reyes
 * email : alu0101209777@ull.edu.es
 * @github: github.com/miguel-martinr
 * @date  : 20201110
 * @description: Clase que implementa un tablero de nodos.
 * 
 * @keywords: heuristic, A*, finder, AI, nodes, boards, game
 */
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


   vector<Node*> get_neighbors_of(int row, int col);
   Node& get_node_at(int row, int col);
   Node& get_node_at(int row, int col) const;
   Node& get_node_at(coordinates P) const;
   Node* get_ptr_at(int row, int col);


   Board& operator=(const Board& board);
   void load_board(istream& is = cin);




   


   void set_init_point(int row, int col);
   void set_final_point(int row, int col);



  /**
   * \brief Cambia el type_ de "num_of" nodos (aleatoriamente posicionados) a "obstacle_". 
   *        Se cambiarán todos los nodos posibles (excepto A y B) hasta llegar a num_of o 
   *        hasta quedarse sin nodos free_
   * \param num_of_cells Número de nodos a cambiar 
   */
   void fill_random_obstacles(int num_of);

  /**
   * \brief Igual que fill_random_obstacles pero usando porcentaje respecto al área 
   *        para calcular los nodos a cambiar. Si percentaje >= 1 entonces se cambiarán
   *        todos los nodos posibles (excepto A y B).
   * \param percentage Porcentaje de nodos a camnbiar 
   */ 
   void fill_prandom_obstacles(float percentage);


  //  void resize(int rows, int cols);

  ostream& print(ostream& os = cout) const;
  friend ostream& operator<<(ostream& os, const Board& obj);

 private:

   Matrix<Node>* grid_;
   int num_of_obstacles_; 
   coordinates init_point_;
   coordinates final_point_;
};