/* --------------------------------------------------------------------------------- *\
    CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)               Enrico Betolazzi

    Esempio: Fattorizzazione LU
\* --------------------------------------------------------------------------------- */

#include <iostream>
#include "LU.h"

using namespace std;

int
main() {
  Integer ok;
  Mat     A, L, U;
  Vec     x, b;
  VecI    p;

  A.resize(4,4);
  b.resize(4);
  x.resize(4);
  p.resize(4);

  A << 0, 3, 2, 1,
       2, 4, 1, 1,
       1, 0, 0, 1,
       1, 0, 1, 1;

  x << 1, 2, 3, 4;

  b = A*x;

  cout << "Matrice dei coefficienti:\n" << A << "\n";
  cout << "Termine noto (trasposto):\n" << b.transpose() << "\n";
  
  ok = LU_factorize( A, p, true );

  cout << "Matrice contenente LU:\n" << A << "\n";
  L = A.triangularView<Eigen::UnitLower>();
  U = A.triangularView<Eigen::Upper>();
  cout << "Matrice L:\n" << L << "\n";
  cout << "Matrice U:\n" << U << "\n";
  cout << "Matrice LU:\n" << L*U << "\n";
  cout << "Permutazone (trasposta):\n" << p.transpose() << "\n";

  // calcolo soluzione
  ok = LU_solve( A, p, b, x );

  cout << "Soluzione del sistema A*x = b (trasposta):\n" << x.transpose() << "\n";
  cout << "All Done Folks!\n";
  return 0;
}