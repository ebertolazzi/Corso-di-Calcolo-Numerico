/* --------------------------------------------------------------------------------- *\
    CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)              Enrico Bertolazzi
\* --------------------------------------------------------------------------------- */

#include "cnum.h"
#include <iomanip>

using namespace std;

using cnum::Real;
using cnum::Integer;

static
Real
fun3( Real x ) {
  return x*(1.1+sin(10*x));
}

static
Real
Dfun3( Real x ) {
  return 1.1 + sin(10*x) + 10*x*cos(10*x);
}

static
Real
DDfun3( Real x ) {
  return 20*cos(10*x) - 100*x*sin(10*x);
}

int
main() {
  Real    a   = -10;
  Real    b   = 10;
  Real    tol = 1e-10;
  Integer flg;
  Integer max_it = 20;
  Real    x0     = 3;
  Real    x1     = 4;
  Real    res;

  cnum::dvec_t a_vec, b_vec, x_vec;

  cout.precision(15);

  res = cnum::zero_bisection( fun3, a, b, tol, flg, &a_vec, &b_vec );
  cout
    << "bisection\n"
    << "flg = " << flg
    << " x = " << res
    << " f(x) = " << setw(22) << fun3(res)
    << " #iter = " << a_vec.size()
    << '\n';

  res = cnum::zero_secant( fun3, x0, x1, tol, max_it, flg, &x_vec );
  cout
    << "secant\n"
    << "flg = " << flg
    << " x = " << res
    << " f(x) = " << setw(22) << fun3(res)
    << " #iter = " << x_vec.size()
    << '\n';

  res = cnum::zero_Newton(
    fun3, Dfun3, x0, tol, max_it, flg, &x_vec
  );
  cout
    << "Newton\n"
    << "flg = " << flg
    << " x = " << res
    << " f(x) = " << setw(22) << fun3(res)
    << " #iter = " << x_vec.size()
    << '\n';

  res = cnum::zero_Halley(
    fun3, Dfun3, DDfun3, x0, tol, max_it, flg, &x_vec
  );
  cout
    << "Halley\n"
    << "flg = " << flg
    << " x = " << res
    << " f(x) = " << setw(22) << fun3(res)
    << " #iter = " << x_vec.size()
    << '\n';

  res = cnum::zero_Newton_for_multiple_roots(
    fun3, Dfun3, DDfun3, x0, tol, max_it, flg, &x_vec
  );
  cout
    << "Newton (m)\n"
    << "flg = " << flg
    << " x = " << res
    << " f(x) = " << setw(22) << fun3(res)
    << " #iter = " << x_vec.size()
    << '\n';

  res = cnum::zero_Steffensen(
    fun3, x0, tol, max_it, flg, &x_vec
  );
  cout
    << "Steffensen\n"
    << "flg = " << flg
    << " x = " << res
    << " f(x) = " << setw(22) << fun3(res)
    << " #iter = " << x_vec.size()
    << '\n';

  res = cnum::zero_Newton_bisection(
    fun3, Dfun3, a, b, tol, max_it, flg, &x_vec
  );
  cout
    << "Newton_bisection\n"
    << "flg = " << flg
    << " x = " << res
    << " f(x) = " << setw(22) << fun3(res)
    << " #iter = " << x_vec.size()
    << '\n';

  cout << "\nAll done folks!\n";
  return 0;
}