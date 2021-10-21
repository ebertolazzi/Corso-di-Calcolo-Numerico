/* --------------------------------------------------------------------------------- *\
    CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)               Enrico Betolazzi

    Esempio: Interpolazione di Lagrange
\* --------------------------------------------------------------------------------- */

#include <iostream>
#include "poly.h"

using namespace std;

int
main() {
  Integer n     = 2; 
  Real    alpha = -2;
  Vec  q;
  q.resize(100);
  // 1+ 2*x + 3*x^2
  q(0) = 1;
  q(1) = 2;
  q(2) = 3;
  // q(x)*(x+2) = 2 + 5*x + 11*x^2 + 3*x^3
  multiply_by_a_monomial( n, q, alpha );
  std::cout << q.head(n+2).transpose() << '\n';

  n = 3;
  Vec x, y, p;
  x.resize(n+1);
  y.resize(n+1);
  x << 0, 1, 2, 3;
  y << 0, 1, 4, 9;

  interpola(n,x,y,p);
  std::cout << p.transpose() << '\n';

  return 0;
}