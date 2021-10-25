/* --------------------------------------------------------------------------------- *\
    CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)               Enrico Betolazzi

    Esempio: Fattorizzazione LU
\* --------------------------------------------------------------------------------- */

#include "LU.h"
#include <iostream>
#include <algorithm>    // std::swap

using namespace std;

Integer
LU_factorize( Mat & A, VecI & p, bool verbose ) {
  // controllo matrice in ingresso
  Integer n = A.rows();
  Integer m = A.cols();
  if ( n != m ) {
    cout 
      << "LU_factorize, matrice in ingresso non quadrata\n"
      << "Dimensione " << n << " x " << m << "\n";
    return 1;
  }
  // inizializzo permutazione [gli indici partono da 0]
  p.resize(n);
  for ( Integer i = 0; i < n; ++i ) p(i) = i;

  // loop fattorizzazione
  for ( Integer i = 0; i < n-1; ++i ) {
    // pivoting, cerco elemento di modulo massimo
    Real    amax = abs(A(i,i));
    Integer imax = i;
    for ( Integer j = i+1; j < n; ++j ) {
      Real absj = abs(A(j,i));
      if ( absj > amax ) { amax = absj; imax = j; }
    }
    // scambio riga i con riga imax
    swap( p(i), p(imax) );      // scambia elementi con libreria STL
    A.row(i).swap(A.row(imax)); // scambia le righe usando la libreria EIGEN
    // calcolo vettore matrice di Frobenius Lk
    m = n-i-1;
    A.col(i).tail(m) /= A(i,i);
    // complemento di Shur
    A.bottomRightCorner(m,m) -= A.col(i).tail(m)*A.row(i).tail(m);
  }
  return 0;
}

Integer
LU_solve( Mat const & A, VecI const & p, Vec const & b, Vec & x ) {
  // controllo dati in ingresso
  Integer n = A.rows();
  Integer m = A.cols();
  if ( n != m ) {
    cout
      << "LU_solve, matrice in ingresso non quadrata\n"
      << "Dimensione " << n << " x " << m << "\n";
    return 1;
  }
  if ( n != p.size() ) {
    cout
      << "LU_solve, dimensione vettore permutazione: |p| = " << p.size() 
      << " mentre mi aspetto " << n << "\n";
    return 2;
  }
  if ( n != x.size() ) {
    cout
      << "LU_solve, dimensione vettore soluzione: |x| = " << x.size() 
      << " mentre mi aspetto " << n << "\n";
    return 2;
  }
  if ( n != b.size() ) {
    cout
      << "LU_solve, dimensione vettore termine noto: |b| = " << b.size() 
      << " mentre mi aspetto " << n << "\n";
    return 2;
  }
  // applico permutazione
  for ( Integer i = 0; i < n; ++i ) x(p(i)) = b(i);

  /*
  // risolvo L*z = P*b
  //
  // / 1               \ / z1 \   / b1 \
  // | L21 1           | | z2 |   | b2 |
  // | L31 L32 1       | | .  | = | .  |
  // | ....            | | .  |   | .  |
  // \ LN1 LN2 .....  1/ \ zN /   \ bN /
  */
  Integer i = 0;
  while ( ++i < n ) {
    x(i) -= x.head(i).dot(A.row(i).head(i));
  }

  /*
  // risolvo U*x = z
  //
  // / U11 U12       U1N\ / x1 \   / z1 \
  // |     U22       U2N| | x2 |   | z2 |
  // |        U33    U3N| | .  | = | .  |
  // |               ...| | .  |   | .  |
  // \               UNN/ \ xN /   \ zN /
  */
  while ( --i > 0 ) {
    x(i) /= A(i,i);
    x.head(i) -= x(i)*A.col(i).head(i);
  }
  x(0) /= A(0,0);

  return 0;
}