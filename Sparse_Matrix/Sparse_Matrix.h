// Student ID: 20274909

#include <string>
#include <sstream>
#include <math.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include <list>
#include <iterator>
#include "Matrix.h"

using namespace std;

#ifndef Sparse_Matrix_h
#define Sparse_Matrix_h

template <typename T>
class Sparse_Matrix {
private:
   struct Node { // private innner
      size_t _col;
      T _val;

      Node(size_t c = 0, T v = T()) : _col(c), _val(v) {}
      size_t get_col() const { return _col; }
      const T get_value() const { return _val; }
      void set_value(const T& val) { _val = val; }
      virtual const T& operator=(const T& val) { return _val = val; }

      friend ostream& operator<<(ostream& os, const Node& node) {
         return os << "{ C: " << node._col << ", V: " << node._val << " }";
      }
   };

   vector<list<Node> > _rows;
   size_t _num_rows, _num_cols;
   T _default_val;

public:
   Sparse_Matrix(size_t nr = 0, size_t nc = 0, const T& default_val = T()) :
      _num_rows(nr), _num_cols(nc), _default_val(default_val) {
      _rows.resize(nr); // double check
   }
   // is something missing here

   size_t get_num_rows() const { return _num_rows; };
   size_t get_num_cols() const { return _num_cols; };

   bool is_valid(size_t r, size_t c) const {
      if (r < get_num_rows() && c < get_num_cols()) {
         return true;
      }
      return false;
   }

   void clear() {
      for (size_t i = 0; i < get_num_rows(); i++) {
         _rows[i].clear();
      }
   }

   const T get(size_t r, size_t c) const {
      if (is_valid(r, c)) {
         for (auto it = _rows[r].begin(); it != _rows[r].end(); ++it) {
            if (it->get_col() == c)
               return it->get_value();
         }
      }
      return _default_val;
   }

   bool set(size_t row, size_t col, const T& val) {
      if (row >= get_num_rows() || col >= get_num_cols())
         return false;

      int location = 0;

      for (auto i = _rows[row].begin(); i != _rows[row].end(); ++i) {
         if (i->get_col() < col) {
            location++;
            continue;
         }
         else if (i->get_col() > col) {
            break;
         }
         else {
            if (val == _default_val) {
               list<Node> temp;
               int location_counter = 0;
               for (auto it = _rows[row].begin(); it != _rows[row].end(); ++it) {
                  if (location_counter != location) {
                     temp.push_back(*it);
                  }
                  location_counter++;
               }
               _rows[row] = temp;
               return true;
            }
            else {
               i->set_value(val);
               return true;
            }
         }
      }

      if (val != _default_val) {

         if (_rows[row].empty() || location == signed(_rows[row].size())) {
            _rows[row].push_back(Node(col, val));
            return true;
         }

         list<Node> temp;
         int location_counter = 0;
         for (auto it = _rows[row].begin(); it != _rows[row].end(); ++it) {
            if (location_counter == location) {
               temp.push_back(Node(col, val));
            }
            temp.push_back(*it);
            location_counter++;
         }
         _rows[row] = temp;
         return true;
      }
      else {
         return true;
      }

   }

   Matrix<T> get_slice(size_t r1, size_t c1, size_t r2, size_t c2) const {
      size_t rows = r2 - r1 + 1;
      size_t columns = c2 - c1 + 1;
      Matrix<T> slice(rows, columns);
      for (size_t i = 0; i < rows; i++) {
         for (size_t j = 0; j < columns; j++) {
            slice.at(i, j) = this->get(r1 + i,c1 + j);
         }
      }
      return slice;
   }

   friend class Tests; // don't remove

};

#endif