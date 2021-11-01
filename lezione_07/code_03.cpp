/* --------------------------------------------------------------------------------- *\
    CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)                  Alice Plebe

    Sistemi lineari sovradimensionati
\* --------------------------------------------------------------------------------- */

#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

#define PREC    2               // precisione per la stampa dei decimali

int main() {
    cout.precision( PREC );     // imposta la precisione per la stampa

    /* ---------------------------------------------
        sistema di 7 equazioni e 3 incognite
    --------------------------------------------- */
    MatrixXd    A   = MatrixXd::Random( 7, 3 );     // matrice 7x3 di valori random
    VectorXd    b   = VectorXd::Random( 7 );        // vettore di 7 valori random
    Vector3d    x;                                  // vettore di 3

    cout << "\nA\n";
    cout << A << endl;
    cout << "\nb\n";
    cout << b << endl;

    /* ---------------------------------------------
        Singular Value Decomposition
    --------------------------------------------- */
    BDCSVD<MatrixXd>    svd     = A.bdcSvd( ComputeThinU | ComputeThinV );
    x       = svd.solve( b );   // risolve per il vettore b

    cout << "\nx\n";
    cout << x << endl;

    return 0;
}