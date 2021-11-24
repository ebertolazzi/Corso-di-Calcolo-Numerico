/* --------------------------------------------------------------------------------- *\
  CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)                Enrico Bertolazzi
\* --------------------------------------------------------------------------------- */

#include "cnum.h"
#include <cmath>
#include <vector>

using namespace std;

namespace cnum {

  using std::abs;
  using std::vector;

  Real
  zero_secant(
    PFUN      fun,
    Real      x0,
    Real      x1,
    Real      tol,
    Integer   max_it,
    Integer & flg,
    dvec_t  * x_history
  ) {
    bool keep_trace = x_history != nullptr;
    Integer npts = 0;
    vector<Real> xh;
    xh.reserve(100);
    // -------------
    Real f0 = fun(x0);
    Real f1 = fun(x1);
    flg = -1; // NO OK
    for ( Integer i = 0; i < max_it; ++i ) {
      if ( keep_trace ) { xh.push_back(x0); ++npts; }
      Real D  = (f1-f0)/(x1-x0);
      Real x2 = x1 - f1/D;
      Real f2 = fun(x2);
      if ( abs(f2) < tol || abs(x1-x2) < tol ) {
        flg = 0;
        x1  = x2;
        xh.push_back(x1); ++npts;
        break;
      }
      // shift
      x0 = x1; x1 = x2;
      f0 = f1; f1 = f2;
    }
    // terminate le iterate, ritorna la soluzione
    if ( keep_trace ) {
      x_history->resize(npts);
      std::copy_n( xh.begin(), npts, x_history->data() );
    }
    return x1;
  }
}
