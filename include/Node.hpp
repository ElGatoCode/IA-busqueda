/**
 * @author: Miguel Alejandro Martín Reyes
 * email : alu0101209777@ull.edu.es
 * @github: github.com/miguel-martinr
 * @date  : 20201110
 * @description: Clase que implementa un nodo.
 * 
 * @keywords: heuristic, A*, finder, AI, nodes, boards, game
 */
#pragma once

#include <iostream>

using namespace std;

enum node_type {free_, obstacle_, stepped_, initial_, final_};

const string FREE_SYM = "·";
const string OBSTACLE_SYM = "█";
const string STEPPED_SYM = "X";
const string INITIAL_SYM = "A";
const string FINAL_SYM = "B";
const string UNKNOWN_SYM = "?";

// Símbolos para cargar desde fichero
const string FREE_IN_SYM = FREE_SYM;
const string OBSTACLE_IN_SYM = "#";
const string STEPPED_IN_SYM = STEPPED_SYM;
const string INITIAL_IN_SYM = INITIAL_SYM;
const string FINAL_IN_SYM = FINAL_SYM;
const string UNKNOWN_IN_SYM = UNKNOWN_SYM;

class Node {
 public:
   Node(int row = 0, int col = 0, node_type type = free_);
   
   ~Node(void);

   bool operator==(Node n);
   Node& operator=(const Node& n);
   int row_;
   int col_;
   double f_; //Costo estimado desde nodo inicial a nodo objetivo (g(n) + h(n))
   double h_; //Costo estimado desde este nodo al nodo objetivo
   double g_; //Coste desde el nodo inicial a este nodo
   node_type type_;
   bool is_closed_;
   bool is_frontier_;


   //ToDo: method char get_sym(type)
   friend ostream& operator<<(ostream& os, const Node* n);
   friend ostream& operator<<(ostream& os, const Node& n);
   Node* parent_;
};

