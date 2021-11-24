/* --------------------------------------------------------------------------------- *\
    CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)               Enrico Betolazzi

    Esempio: Interpolazione di Lagrange
\* --------------------------------------------------------------------------------- */

#include <iostream>
#include "cnum.h"

using namespace std;
using cnum::Integer;
using cnum::dvec_t;
using cnum::Poly;

int
main() {
  Integer n = 1;
  dvec_t x, y;

  x.resize(n+1);
  y.resize(n+1);
  x << 0, 1;
  y << 1, 2;

  Poly p = cnum::Lagrange_interpolation(x,y);
  std::cout << p << '\n';

  n = 3;
  x.resize(n+1);
  y.resize(n+1);
  x << 0, 1, 2, 3;
  y << 0, 1, 4, 9;

  p = cnum::Lagrange_interpolation(x,y);
  std::cout << p << '\n';

  return 0;
}