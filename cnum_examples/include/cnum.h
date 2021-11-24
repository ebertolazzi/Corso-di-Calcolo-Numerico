/* --------------------------------------------------------------------------------- *\
    CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)               Enrico Betolazzi
\* --------------------------------------------------------------------------------- */

// uso pragma come "speed up" per evitare doppia inclusione
#pragma once

// se il compilatore non capisce il pragma uso trucco
// standard per evitare doppia inclusione

#ifndef CNUM_dot_H
#define CNUM_dot_H

#include <iostream>
#include <string>
#include <Eigen/Dense>

namespace cnum {

  using namespace std;

  typedef int    Integer;
  typedef double Real;

  typedef Real (*PFUN)( Real x );

  typedef Eigen::VectorXd dvec_t; // vettore lunghezza variabile di double

  class Poly : public dvec_t {
  private:
    // i coefficienti sono nella classe dvec_t da cui deriva
    int m_order; // ordine del polinomio
                 // (o meglio, la lunghezza del vettore v)

    // accesso to the Eigen class
    dvec_t & to_eigen() { return * static_cast<dvec_t*>(this); }

  public:
    // costruttori
    Poly( int );
    Poly( dvec_t const & );

    // accesso to the Eigen class
    dvec_t const & to_eigen() const { return * static_cast<dvec_t const *>(this); }

    Poly & set_scalar( Real a );
    Poly & set_monomial( Real a );

    // funzioni di supporto
    dvec_t  coeffs() const { return *this; }
    Integer degree() const { return m_order-1; }
    Integer order()  const { return m_order; }

    // stampa il polinomio
    friend std::ostream & operator<<( std::ostream&, Poly const & );

    Real eval( Real ) const; // valuta il polinomio
    Poly derivative() const; // operazione derivata
    Poly integral()   const; // operazione integrale

    // +, -, * operazioni esterne alla classe
    friend Poly operator + ( Poly const &, Poly const & ); // operazione somma
    friend Poly operator - ( Poly const &, Poly const & ); // operazione differenza
    friend Poly operator * ( Poly const &, Poly const & ); // operazione prodotto

    friend Poly operator + ( Real, Poly const & ); // operazione somma
    friend Poly operator - ( Real, Poly const & ); // operazione differenza
    friend Poly operator * ( Real, Poly const & ); // operazione prodotto

    friend Poly operator + ( Poly const &, Real ); // operazione somma
    friend Poly operator - ( Poly const &, Real ); // operazione differenza
    friend Poly operator * ( Poly const &, Real ); // operazione prodotto

    friend Poly operator + ( Poly const &, Real ); // operazione prodotto

    Poly & operator += ( Poly const & ); // somma al polinomio
    Poly & operator -= ( Poly const & ); // sottrai al polinomio
    Poly & operator *= ( Poly const & ); // moltiplica il polinomio

    Poly & operator += ( Real ); // somma al polinomio
    Poly & operator -= ( Real ); // sottrai al polinomio
    Poly & operator *= ( Real ); // moltiplica il polinomio
  };

  // dati i punti (x[i], y[i]) calcola il corrispondente polinomio interpolante
  Poly Lagrange_interpolation( dvec_t const & x, dvec_t const & y );
  Poly Lagrange_interpolation( Real const x[], Real const y[], Integer npts );

  Real
  zero_bisection(
    PFUN      fun,
    Real      a,
    Real      b,
    Real      tol,
    Integer & flg,
    dvec_t  * a_history = nullptr,
    dvec_t  * b_history = nullptr
  );

  Real
  zero_secant(
    PFUN      fun,
    Real      x0,
    Real      x1,
    Real      tol,
    Integer   max_it,
    Integer & flg,
    dvec_t  * x_history = nullptr
  );

  Real
  zero_Newton(
    PFUN      fun,
    PFUN      Dfun,
    Real      x0,
    Real      tol,
    Integer   max_it,
    Integer & flg,
    dvec_t  * x_history = nullptr
  );

  Real
  zero_Halley(
    PFUN      fun,
    PFUN      Dfun,
    PFUN      DDfun,
    Real      x0,
    Real      tol,
    Integer   max_it,
    Integer & flg,
    dvec_t  * x_history = nullptr
  );

  Real
  zero_Newton_for_multiple_roots(
    PFUN      fun,
    PFUN      Dfun,
    PFUN      DDfun,
    Real      x0,
    Real      tol,
    Integer   max_it,
    Integer & flg,
    dvec_t  * x_history = nullptr
  );
}

#endif
