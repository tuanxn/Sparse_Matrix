// Student ID: 20274909

#include "Sparse_Matrix.h"
#include "Matrix.h"
#include <iostream>

using namespace std;

int main()
{
   Matrix<int> foo(5, 3);
   cout << foo.to_string();

   Matrix<int> test(5, 5);
   cout << test.get_num_rows() << endl;
   cout << test.get_num_cols() << endl;
   test.fill(12345678);
   cout << test.at(3, 3) << endl;
   int& temp = test.at(3, 3);
   temp = 10;
   //cout << test.at(5, 5) << endl;
   cout << test;

   Sparse_Matrix<double> test2(10, 10, 0);
   test2.set(5, 5, 0.93);
   cout << test2.get_slice(0, 0, 10, 10);
   cout << test2.get(1, 2) << endl;
   test2.set(0, 0, 1.99);
   test2.set(0, 4, 2.99);
   test2.set(3, 9, 98.99);
   test2.set(2, 10, 909.99);
   test2.set(2, 2, 21.99);
   test2.set(2, 8, 22.99);
   test2.set(2, 4, 23.99);
   test2.set(2, 1, 24.99);
   cout << test2.get(0, 0);
   cout << test2.get(2, 4) << endl;
   cout << test2.get_slice(1, 3, 5, 15);
   test2.clear();
   cout << test2.get(1, 2) << endl;
   test2.set(1, 2, 1001.99);
   cout<< test2.get(1, 2) << endl;
   Sparse_Matrix<double> too(100000, 100000);
   too.set(43, 50958, 0.934);
   cout << too.get(43, 50958);
}