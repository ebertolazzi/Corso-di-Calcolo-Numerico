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
  zero_Halley(
    PFUN      fun,
    PFUN      Dfun,
    PFUN      DDfun,
    Real      x0,
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
    flg = -1; // NOT OK
    for ( Integer i = 0; i < max_it; ++i ) {
      if ( keep_trace ) { xh.push_back(x0); ++npts; }
      Real Df0  = Dfun(x0);
      Real DDf0 = DDfun(x0);
      Real x1   = x0 - (f0*Df0)/(Df0*Df0-0.5*f0*DDf0);
      Real f1   = fun(x1);
      if ( abs(f1) < tol || abs(x0-x1) < tol ) {
        flg = 0;
        x0  = x1;
        xh.push_back(x0); ++npts;
        break;
      }
      // shift
      x0 = x1;
      f0 = f1;
    }
    // terminate le iterate, ritorna la soluzione
    if ( keep_trace ) {
      x_history->resize(npts);
      std::copy_n( xh.begin(), npts, x_history->data() );
    }
    return x0;
  }
}
