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
fun1( Real x ) {
  return exp(x)+x;
}

static
Real
Dfun1( Real x ) {
  return exp(x)+1;
}

static
Real
DDfun1( Real x ) {
  return exp(x);
}

int
main() {
  Real    a   = -10;
  Real    b   = 10;
  Real    tol = 1e-10;
  Integer flg;
  Integer max_it = 20;
  Real    x0     = 1;
  Real    x1     = 2;
  Real    res;

  cnum::dvec_t a_vec, b_vec, x_vec;

  cout.precision(15);

  res = cnum::zero_bisection( fun1, a, b, tol, flg, &a_vec, &b_vec );
  cout
    << "bisection\n"
    << "flg = " << flg
    << " x = " << res
    << " f(x) = " << setw(22) << fun1(res)
    << " #iter = " << a_vec.size()
    << '\n';

  res = cnum::zero_secant( fun1, x0, x1, tol, max_it, flg, &x_vec );
  cout
    << "secant\n"
    << "flg = " << flg
    << " x = " << res
    << " f(x) = " << setw(22) << fun1(res)
    << " #iter = " << x_vec.size()
    << '\n';

  res = cnum::zero_Newton(
    fun1, Dfun1, x0, tol, max_it, flg, &x_vec
  );
  cout
    << "Newton\n"
    << "flg = " << flg
    << " x = " << res
    << " f(x) = " << setw(22) << fun1(res)
    << " #iter = " << x_vec.size()
    << '\n';

  res = cnum::zero_Halley(
    fun1, Dfun1, DDfun1, x0, tol, max_it, flg, &x_vec
  );
  cout
    << "Halley\n"
    << "flg = " << flg
    << " x = " << res
    << " f(x) = " << setw(22) << fun1(res)
    << " #iter = " << x_vec.size()
    << '\n';

  res = cnum::zero_Newton_for_multiple_roots(
    fun1, Dfun1, DDfun1, x0, tol, max_it, flg, &x_vec
  );
  cout
    << "Newton (m)\n"
    << "flg = " << flg
    << " x = " << res
    << " f(x) = " << setw(22) << fun1(res)
    << " #iter = " << x_vec.size()
    << '\n';

  res = cnum::zero_Steffensen(
    fun1, x0, tol, max_it, flg, &x_vec
  );
  cout
    << "Steffensen\n"
    << "flg = " << flg
    << " x = " << res
    << " f(x) = " << setw(22) << fun1(res)
    << " #iter = " << x_vec.size()
    << '\n';

  res = cnum::zero_Newton_bisection(
    fun1, Dfun1, a, b, tol, max_it, flg, &x_vec
  );
  cout
    << "Newton_bisection\n"
    << "flg = " << flg
    << " x = " << res
    << " f(x) = " << setw(22) << fun1(res)
    << " #iter = " << x_vec.size()
    << '\n';

  cout << "\nAll done folks!\n";
  return 0;
}