/* --------------------------------------------------------------------------------- *\
    CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)               Enrico Betolazzi

    Esempio: Fattorizzazione LU (solo con EIGEN)
\* --------------------------------------------------------------------------------- */

#include <iostream>
#include "LU.h"

using namespace std;

int
main() {
  Mat A, L, U;
  Vec x, b;

  A.resize(4,4);
  b.resize(4);
  x.resize(4);

  A << 0, 3, 2, 1,
       2, 4, 1, 1,
       1, 0, 0, 1,
       1, 0, 1, 1;

  x << 1, 2, 3, 4;

  b = A*x;

  // Costruisco fattorizzazone LU
  Eigen::PartialPivLU<Mat> LU(A);

  cout << "Matrice dei coefficienti:\n" << A << "\n";
  cout << "Termine noto (trasposto):\n" << b.transpose() << "\n";
  
  // calcolo soluzione
  x = LU.solve( b );

  cout << "Soluzione del sistema A*x = b (trasposta):\n" << x.transpose() << "\n";
  cout << "All Done Folks!\n";
  return 0;
}