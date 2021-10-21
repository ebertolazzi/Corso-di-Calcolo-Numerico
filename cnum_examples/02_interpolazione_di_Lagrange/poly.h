/* --------------------------------------------------------------------------------- *\
    CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)               Enrico Betolazzi

    Esempio: Interpolazione di Lagrange, manipolazione di polinomi
\* --------------------------------------------------------------------------------- */

#pragma once

#ifndef POLY_H
#define POLY_H

#include <Eigen/Dense>

typedef int    Integer; // uso alias di int
typedef double Real; // uso alias di double
typedef Eigen::Matrix<Real,Eigen::Dynamic,1> Vec;

/*
  Valuta un polinomio con il metodo di Horn.
  n = grado del polinomio (Vec deve avere dimensione >= n+1)
  p = vettore dei coefficienti del polinomio
  x = punto di valutazione
 */
Real Horner( Integer n, Vec const & p, Real x );

/*
  Moltiplica per (x-alpha) il polinomio q(x) e sovrascrive q(x)
 */
void multiply_by_a_monomial( Integer n, Vec & q, Real alpha );

/*
  Calcolo polinomio interpolante di Lagrange
  x, y = dati in ingresso
  p    = coefficienti del polinomio
 */
void interpola( Integer n, Vec const & x, Vec const & y, Vec & p );

#endif

