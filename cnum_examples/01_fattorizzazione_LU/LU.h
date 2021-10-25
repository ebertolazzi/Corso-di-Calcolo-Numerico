/* --------------------------------------------------------------------------------- *\
    CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)               Enrico Betolazzi

    Esempio: Fattorizzazione LU
\* --------------------------------------------------------------------------------- */

#ifndef LU_H
#define LU_H

#include <Eigen/Dense>

typedef double Real;    // uso alias di double
typedef int    Integer; // uso alias di int
typedef Eigen::Matrix<Integer,Eigen::Dynamic,1>           VecI;
typedef Eigen::Matrix<Real,Eigen::Dynamic,1>              Vec;
typedef Eigen::Matrix<Real,Eigen::Dynamic,Eigen::Dynamic> Mat;

Integer LU_factorize( Mat & A, VecI & p, bool verbose = false );
Integer LU_solve( Mat const & A, VecI const & p, Vec const & b, Vec & x );

#endif

