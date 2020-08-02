// Student ID: 20274909

#include <string>
#include <sstream>
#include <math.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include <list>
#include <iterator>

using namespace std;

#ifndef Matrix_h
#define Matrix_h

template <typename T>
class Matrix {
protected:
   vector<vector<T> > _rows;

public:
   Matrix(size_t nr = 0, size_t nc = 0) {
      resize(nr, nc);
   }

   size_t get_num_rows() const { return _rows.size(); };
   size_t get_num_cols() const { return (_rows.size() > 0 ? _rows[0].size() : 0); };
   void clear() { _rows.clear(); }

   void resize(size_t nr, size_t nc) {
      _rows.resize(nr);
      for (size_t i = 0; i < _rows.size(); i++) {
         _rows[i].resize(nc);
      }
   }

   void fill(T filler) {
      for (size_t i = 0; i < get_num_rows(); i++) {
         for (size_t j = 0; j < get_num_cols(); j++) {
            _rows[i][j] = filler;
         }
      }
   }

   const T& const_at(size_t r, size_t c) const { // throws OOB
      if (r >= get_num_rows() || c >= get_num_cols()) {
         throw OOB_exception();
      }
      return _rows[r][c];
   }

   T& at(size_t r, size_t c) { // throws OOB
      if (r >= get_num_rows() || c >= get_num_cols()) {
         throw OOB_exception();
      }
      return _rows[r][c];
   }

   string to_string() const {
      string output = "# Matrix\n";
      for (size_t i = 0; i < get_num_rows(); i++) {
         for (size_t j = 0; j < get_num_cols(); j++) {
            string val_str = std::to_string(const_at(i, j));
            int val_len = val_str.length();

            if (val_len <= 6) {
               stringstream ss;
               ss << std::setw(6) << val_str;
               val_str = ss.str();
            }
            else {
               istringstream ss(val_str);
               ss >> std::setw(6) >> val_str;
            }

            if (j == 0) {
               output += val_str;
            }
            else {
               output += " " + val_str;
            }
         }
         output += "\n";
      }
      return output;
   }

   class OOB_exception : public exception {
   public: string what() { return "Out of bounds access"; }
   };

   // Friends -------------------------------------------------------------------

   friend ostream& operator<<(ostream& os, const Matrix<T>& mat) {
      return os << mat.to_string();
   }

   friend bool operator==(const Matrix<T>& m1, const Matrix<T>& m2) {
      if (m1.get_num_rows() != m2.get_num_rows()) return false;
      if (m1.get_num_cols() != m2.get_num_cols()) return false;

      for (size_t i = 0; i < m1.get_num_rows(); i++) {
         for (size_t j = 0; j < m1.get_num_cols(); j++) {
            if (m1.const_at(i, j) != m2.const_at(i, j)) {
               return false;
            }
         }
      }

      return true;
   }

   friend bool operator!=(const Matrix<T>& m1, const Matrix<T>& m2) {
      return !(m1 == m2);
   }

   friend class Tests; // Don't remove this line
};

#endif