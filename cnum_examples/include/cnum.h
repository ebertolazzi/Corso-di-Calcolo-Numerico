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

  public:
    // costruttori
    Poly( int );
    Poly( dvec_t const & );

    // funzioni di supporto
    dvec_t  coeffs() const { return *this; }
    Integer degree() const { return m_order-1; }
    Integer order()  const { return m_order; }

    // stampa il polinomio
    friend std::ostream & operator<<( std::ostream&, Poly const & );

    Real eval( Real ) const;              // valuta il polinomio
    Poly operator+( Poly const & ) const; // operazione somma
    Poly operator*( Poly const & ) const; // operazione prodotto
    Poly derivative() const;              // operazione derivata
    Poly integral() const;                // operazione integrale
  };

  Real dicotomico( PFUN fun, Real a, Real b, Real tol );
  Real Newton( PFUN fun, Real x0, Integer max_it );
  Real Halley( PFUN fun, Real x0, Integer max_it );
  Real secanti( PFUN fun, Real x0, Integer max_it );
}

#endif
