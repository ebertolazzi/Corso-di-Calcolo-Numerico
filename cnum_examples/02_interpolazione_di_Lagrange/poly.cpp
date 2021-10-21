/* --------------------------------------------------------------------------------- *\
    CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)               Enrico Betolazzi

    Esempio: Fattorizzazione LU
\* --------------------------------------------------------------------------------- */

#include "poly.h"
#include <iostream>
#include <algorithm>    // std::swap

using namespace std;

Real
Horner( Integer n, Vec const & p, Real x ) {
  /*\ 
   mettere controlli di sicurezza
  \*/
  Real res = p(n);
  while ( n-- > 0 ) res = res*x+p(n);
  return res;
}

void
multiply_by_a_monomial( Integer n, Vec & q, Real alpha ) {
  // salvo primo e ultimo elemento
  Real q0 = q(0);
  Real qn = q(n);
  if ( n > 0 ) { // nel caso triviale non serve il loop
    for ( Integer i = n; i > 0; --i )
      q(i) = q(i-1)-alpha*q(i);
    // non funziona per via sovrapposizione
    // q.segment(1,n) e q.head(n)
    // q.segment(1,n) = q.head(n)-alpha*q.segment(1,n);
  }
  q(0)   = -alpha*q0;
  q(n+1) = qn;
}

void
interpola( Integer n, Vec const & x, Vec const & y, Vec & p ) {
  Vec lk;
  lk.resize(n+1);
  p.resize(n+1);
  p.setZero();
  for ( Integer k = 0; k <= n; ++k ) {
    // calcolo lk
    lk.setZero();
    lk(0) = 1;
    Integer dgr = 0;
    for ( Integer j = 0; j <= n; ++j ) {
      // skip j == k
      if ( j == k ) continue;
      multiply_by_a_monomial( dgr, lk, x(j) );
      ++dgr;
    }
    // solo per test controllo lk(x)
    for ( Integer j = 0; j <= n; ++j ) {
      std::cout
        << "l" << k << "(x_" << j << ") = " 
        << Horner(n,lk,x(j)) << '\n';
    }
    // somma y(k)*lk/lk(xk) a p
    Real v = y(k)/Horner(n,lk,x(k));
    p += v*lk;
  }
}
