/* --------------------------------------------------------------------------------- *\
  CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)                Enrico Bertolazzi
\* --------------------------------------------------------------------------------- */

#include "cnum.h"
#include <vector>

using namespace std;

namespace cnum {

  using std::vector;

  Real
  zero_Newton_bisection(
    PFUN      fun,
    PFUN      Dfun,
    Real      a,
    Real      b,
    Real      tol,
    Integer   max_iter,
    Integer & flg,
    dvec_t  * x_history
 ) {
    bool keep_trace = x_history != nullptr;
    Integer npts = 0;
    vector<Real> xh;
    xh.reserve(100);
    // ------------------------
    Real fa = fun(a);
    Real fb = fun(b);
    // controlla consistenza dati del problema
    if ( a >= b )      { flg = -1; return 0; }
    if ( fa * fb > 0 ) { flg = -2; return 0; }
    flg = -1; // NO OK
    Real x, fx;
    for ( Integer i = 0; i < max_iter; ++i ) {
      if ( keep_trace ) { xh.push_back(x); ++npts; }
      if ( abs(fa) < abs(fb) ) x = a - fa/Dfun(a);
      else                     x = b - fb/Dfun(b);
      // Se Newton fattito uso bisezione
      if ( x <= a || x >= b ) x = (a+b)/2;
      fx = fun(x);
      if ( fa*fx < 0 ) {
        // intervallo [a,x]
        b  = x;
        fb = fx;
      } else if ( fb*fx <= 0 ) {
        // intervallo [c,b]
        a  = x;
        fa = fx;
      }
      if ( abs(fx) < tol ) {
        flg = 0;
        xh.push_back(x); ++npts;
        break;
      }
    }
    // terminate le iterate, ritorna la soluzione
    if ( keep_trace ) {
      x_history->resize(npts);
      std::copy_n( xh.begin(), npts, x_history->data() );
    }
    return x;
  }
}
