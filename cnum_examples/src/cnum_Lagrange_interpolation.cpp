/* --------------------------------------------------------------------------------- *\
    CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)               Enrico Betolazzi
\* --------------------------------------------------------------------------------- */

#include "cnum.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>    // std::swap

namespace cnum {

  using namespace std;

  // dati i punti (x[i], y[i]) calcola il corrispondente polinomio interpolante
  Poly
  Lagrange_interpolation( dvec_t const & x, dvec_t const & y ) {
    Integer nx = x.size();
    Integer ny = y.size();
    if ( nx != ny ) {
      cerr
        << "Errore nella chiamata di interpolazione_di_Lagrange(x,y):\n"
        << "dimensione x = " << nx
        << " e dimensione y = " << ny
        << " devono essere uguali\n";
      exit(0);
    }
    return Lagrange_interpolation( x.data(), y.data(), nx );
  }

  Poly
  Lagrange_interpolation( Real const x[], Real const y[], Integer npts ) {
    Poly res( npts ), lk(0), tmp(0);

    for ( Integer k = 0; k < npts; ++k ) {
      // azzero polinomio
      lk.set_scalar(1);
      for ( Integer j = 0; j < npts; ++j ) {
        // skip j == k
        if ( j != k ) lk *= tmp.set_monomial( -x[j] );
      }
      // somma (y(k)/lk(x(k))*lk al polinomio res
      res += (y[k]/lk.eval(x[k])) * lk;
    }
    return res;
  };

}
