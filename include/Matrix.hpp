/**
 * 
 * @author Miguel Martín
 * @date 20201015
 */


#pragma once

#include <vector>
#include <cassert>
#include <stdio.h>
#include <iostream>

using namespace std;

template <class T>
class Matrix {
 public:
   Matrix(int rows = 0, int cols = 0);
   
   /**
    * \brief Returns number of rows
    */
   int rows_num(void) const;

   /**
    * \brief Returns number of columns
    */
   int cols_num(void) const;

   T get_copy_of(int row, int col) const;
   T operator()(int row, int col) const; //Retorna copia

   T& at(int row, int col);
   
   vector<T>& operator[](int i); //Sirve para acceder de la forma mat[i][j] a una ref  al elemento

   void resize(int rows, int cols);

   bool is_good_pos(int row, int col) const;


 
   
   vector<vector<T>> grid_;
};

template <class T>
Matrix<T>::Matrix(int rows, int cols) {
  grid_.resize(rows);
  for (auto &row : grid_)
    row.resize(cols);
}

template <class T>
int Matrix<T>::rows_num(void) const {
  return grid_.size();
}

template <class T>
int Matrix<T>::cols_num(void) const {
  return grid_.size() == 0 ? 0 : grid_[0].size();  
}

template <class T>
T Matrix<T>::operator()(int row, int col) const {
  return get_copy_of(row,col);
}

template <class T>
T  Matrix<T>::get_copy_of(int row, int col) const {
  assert(is_good_pos(row,col));
  return grid_[row][col];
}

template <class T>
T& Matrix<T>::at(int row, int col) {
  assert(is_good_pos(row,col));
  return grid_[row][col];
}



template <class T>
vector<T>& Matrix<T>::operator[](int row) {
  assert(row >= 0 && row < rows_num());
  return grid_[row];
}


template <class T>
bool Matrix<T>::is_good_pos(int row, int col) const {
  bool row_ok_down = row >= 0;
  bool row_ok_up = row < rows_num();
  bool col_ok_down = col >= 0;
  bool col_ok_up = col < cols_num();

  return row_ok_down && row_ok_up && col_ok_down && col_ok_up;
}

template <class T>
void Matrix<T>::resize(int rows, int cols) {
  grid_.resize(rows);
  grid_.shrink_to_fit();
  for (auto& row : grid_) {
    row.resize(cols);
    row.shrink_to_fit();
  }
}