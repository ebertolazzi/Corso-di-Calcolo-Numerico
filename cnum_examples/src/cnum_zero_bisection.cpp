/* --------------------------------------------------------------------------------- *\
  CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)                Enrico Bertolazzi
\* --------------------------------------------------------------------------------- */

#include "cnum.h"
#include <vector>

using namespace std;

namespace cnum {

  using std::vector;

  Real
  zero_bisection(
    PFUN      fun,
    Real      a,
    Real      b,
    Real      tol,
    Integer & flg,
    dvec_t  * a_history,
    dvec_t  * b_history
 ) {
    bool keep_trace = a_history != nullptr && b_history != nullptr;
    Integer npts = 0;
    vector<Real> ah, bh;
    ah.reserve(100);
    bh.reserve(100);
    Real fa = fun(a);
    Real fb = fun(b);
    // controlla consistenza dati del problema
    if ( a >= b )      { flg = -1; return 0; }
    if ( fa * fb > 0 ) { flg = -2; return 0; }
    flg = 0; // OK
    while ( b - a > tol ) {
      if ( keep_trace ) {
        ah.push_back(a);
        bh.push_back(a);
        ++npts;
      }
      Real c  = (a+b)/2;
      Real fc = fun(c);
      if ( fa*fc < 0 ) {
        // intervallo [a,c]
        b  = c;
        fb = fc;
      } else if ( fb*fc < 0 ) {
        // intervallo [c,b]
        a  = c;
        fa = fc;
      } else {
        // caso fortunato f(c) = 0;
        flg = 1; // OK
        a = b = c;
        break;
      }
    }
    // terminate le iterate, ritorna la soluzione
    if ( keep_trace ) {
      a_history->resize(npts);
      b_history->resize(npts);
      std::copy_n( ah.begin(), npts, a_history->data() );
      std::copy_n( bh.begin(), npts, b_history->data() );
    }
    return (a+b)/2;
  }
}
