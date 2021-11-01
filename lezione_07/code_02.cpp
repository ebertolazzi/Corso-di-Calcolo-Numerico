/* --------------------------------------------------------------------------------- *\
    CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)                  Alice Plebe

    Sistemi di equazioni lineari
\* --------------------------------------------------------------------------------- */

#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

#define PREC    2               // precisione per la stampa dei decimali

int main() {
    cout.precision( PREC );     // imposta la precisione per la stampa

    /* ---------------------------------------------
        il sistema di equazioni:    A x = b
    --------------------------------------------- */
    Matrix3d    A;
    Vector3d    b;
    Vector3d    x;

	A	<< 2, 6, 2, -3, -8, 0, 4, 9, 2;
    b   << 2, 2, 3;

    cout << "\nA\n";
    cout << A << endl;
    cout << "\nb\n";
    cout << b.transpose() << endl;

    /* ---------------------------------------------
        decomposizione LU della matrice A
    --------------------------------------------- */
    PartialPivLU<Matrix3d>  decomp;         // oggetto decomposition
    decomp          = A.partialPivLu();     // calcola rispetto ad A
    Matrix3d    LU  = decomp.matrixLU();    // ottiene la matrice LU
    cout << "\nLU\n";
    cout << LU << endl;

    // estrae solamente la matrice U
    Matrix3d    U   = LU.triangularView<Upper>();
    cout << "\nU\n";
    cout << U << endl;

    // estrae solamente la matrice L
    Matrix3d    L   = Matrix3d::Identity();
    L.triangularView<StrictlyLower>()   = LU;
    cout << "\nL\n";
    cout << L << endl;

    /* ---------------------------------------------
        verifica la proprieta`:    P A = L U
    --------------------------------------------- */
    cout << "\nP * A\n";
    cout << decomp.permutationP() * A << endl;
    cout << "\nL * U\n";
    cout << L * U << endl;

    /* ---------------------------------------------
        calcola le soluzioni del sistema
    --------------------------------------------- */
    x   = decomp.solve( b );            // risolve per il vettore b
    cout << "\nx\n";
    cout << x.transpose() << endl;

    return 0;
}