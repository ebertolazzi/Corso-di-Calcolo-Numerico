/* --------------------------------------------------------------------------------- *\
    CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)                  Alice Plebe

    Classe per rappresentare un poligono
\* --------------------------------------------------------------------------------- */

#include "poly.h"

using namespace std;
using namespace Eigen;


int main() {
    Vector4d    c1( 2, -2, 2, 3 );
    Vector3d    c2( 4, 0, 1 );

    Poly        p1( c1 );
    Poly        p2( c2 );
    Poly        p3( 10 );

    cout << "Il grado di p1: " << p1.get_degr() << endl;
    cout << "Il grado di p2: " << p2.get_degr() << endl;
    cout << endl;

    cout << "p1" << endl;
    cout << p1 << endl;

    cout << "p2" << endl;
    cout << p2 << endl;
    cout << "p2( 3 ) = " << p2.eval( 3 ) << endl;

    p3  = p1.derivative();
    cout << "derivata di p1" << endl;
    cout << p3 << endl;

    p3  = p1.integral();
    cout << "integrale di p1" << endl;
    cout << p3 << endl;

    p3  = p1 + p2;
    cout << "somma di p1 e p2" << endl;
    cout << p3 << endl;

    p3  = p1 * p2;
    cout << "prodotto di p1 e p2" << endl;
    cout << p3 << endl;

    return 0;
}