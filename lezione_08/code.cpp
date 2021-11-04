/* --------------------------------------------------------------------------------- *\
    CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)                  Alice Plebe

    Matrici di trasformazione
\* --------------------------------------------------------------------------------- */

#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <Eigen/Geometry>

using namespace std;
using namespace Eigen;

#define         PREC        3           // precisione per la stampa dei decimali

const string    fname1  = "obj1.txt";   // primo file di output
const string    fname2  = "obj2.txt";   // secondo file di output
const string    fname3  = "obj3.txt";   // terzo file di output

// intestazione file per gnuplot
const string    head    = "# --------------------------\n# data generated for gnuplot\n# --------------------------\n";



/* --------------------------------------------------------------------------------- *\
    Genera la matrice di rotazione senza utilizzare le funzioni pronte di Eigen
\* --------------------------------------------------------------------------------- */
MatrixXd basic_rot( double yaw, double pitch, double roll ) {
    Matrix3d    Y, P, R;
    double      c, s;

    c   = cos( yaw );
    s   = sin( yaw );
    Y << c, -s, 0, s, c, 0, 0, 0, 1;

    c   = cos( pitch );
    s   = sin( pitch );
    P << c, 0, s, 0, 1, 0, -s, 0, c;

    c   = cos( roll );
    s   = sin( roll );
    R << 1, 0, 0, 0, c, -s, 0, s, c;

    return Y * P * R;
}


/* --------------------------------------------------------------------------------- *\
    Genera la matrice di rotazione utilizzando le funzioni pronte di Eigen
\* --------------------------------------------------------------------------------- */
Matrix4d eigen_rot( double yaw, double pitch, double roll ) {
    Transform<double, 3, Affine>    T   = Transform<double, 3, Affine>::Identity();
    T.rotate( AngleAxisd ( yaw, Vector3d::UnitX() ) );
    T.rotate( AngleAxisd ( pitch, Vector3d::UnitY() ) );
    T.rotate( AngleAxisd ( roll, Vector3d::UnitZ() ) );

    return T.matrix();
}


/* --------------------------------------------------------------------------------- *\
    Genera la matrice di traslazione utilizzando le funzioni pronte di Eigen
\* --------------------------------------------------------------------------------- */
Matrix4d eigen_transl( double xd, double yd, double zd ) {
    Transform<double, 3, Affine>    T   = Transform<double, 3, Affine>::Identity();
    T.translate( Vector3d( xd, yd, zd ) );

    return T.matrix();
}


/* --------------------------------------------------------------------------------- *\
    Genera la matrice di scaling utilizzando le funzioni pronte di Eigen
\* --------------------------------------------------------------------------------- */
Matrix4d eigen_scale( double xs, double ys, double zs ) {
    Transform<double, 3, Affine>    T   = Transform<double, 3, Affine>::Identity();
    T.scale( Vector3d( xs, ys, zs ) );

    return T.matrix();
}


/* --------------------------------------------------------------------------------- *\
    Scrive i vertici di un parallelepipedo su un file per gnuplot
\* --------------------------------------------------------------------------------- */
void dump_points( const MatrixXd &O, string fname ) {
    Vector3d    V;
    ofstream    f( fname );                 // stream di uscita
    f << head;                              // intestazione
    f << fixed << setprecision( PREC );     // setta la precisione

    // scrive le coordinate della faccia base
    for( int i=0; i<4; i++ ) {
        V   = O.col( i );
        f << V( 0 ) << "\t" << V( 1 ) << "\t" << V( 2 ) << endl;
    }
    // ripete il primo vertice per chiudere il quadrilatero
    V   = O.col( 0 );
    f << V( 0 ) << "\t" << V( 1 ) << "\t" << V( 2 ) << endl;

    f << endl;      // gnuplot richiede una riga vuota per separare due facce

    // scrive le coordinate della faccia in alto
    for( int i=4; i<8; i++ ) {
        V   = O.col( i );
        f << V( 0 ) << "\t" << V( 1 ) << "\t" << V( 2 ) << endl;
    }
    // ripete il primo vertice per chiudere il quadrilatero
    V   = O.col( 4 );
    f << V( 0 ) << "\t" << V( 1 ) << "\t" << V( 2 ) << endl;

    f.close();
}



int main() {
    Matrix<double, 3, 8>    O;                              // parallelepipedo iniziale
    Matrix<double, 3, 8>    O1, O2;                         // parallelepipedi dopo le trasformazioni
    Matrix3d                R;                              // matrice di trasformazione
    Matrix4d                R1;                             // matrice di trasformazione omogenea
    Vector3d                pA, pB, pC, pD, pE, pF, pG, pH; // vertici del parallelepipedo

    // imposta le coordinate dei vertici
    pA << 2.5, 2.0, 0.0;
    pB << 2.5, 5.0, 0.0;
    pC << 5.5, 5.0, 0.0;
    pD << 5.5, 2.0, 0.0;
    pE << 2.5, 2.0, 6.0;
    pF << 2.5, 5.0, 6.0;
    pG << 5.5, 5.0, 6.0;
    pH << 5.5, 2.0, 6.0;

    // imposta i vertici del parallelepipedo
    O << pA, pB, pC, pD, pE, pF, pG, pH;

    cout << "\nO\n";
    cout << O.transpose() << endl;
    dump_points( O, fname1 );

    R   = basic_rot( -0.25 * M_PI, 0, 0.1 * M_PI );         // matrice di rotazione
    O1  = R * O;                                            // applica la trasformazione

    cout << "\nO1\n";
    cout << O1.transpose() << endl;
    dump_points( O1, fname2 );                              // scrive il file per gnuplot

    // R1  = eigen_rot( -0.25 * M_PI, 0, 0.1 * M_PI );      // matrice di rotazione
    // R1  = eigen_transl( 1, 1, 0 );                       // matrice di traslazione
    R1  = eigen_scale( 1.2, 1, 0.4 );                       // matrice di scaling

    // applica la trasformazione prima passando per coordinate omogenee
    O2  = ( R1 * O.colwise().homogeneous() ).colwise().hnormalized();

    cout << "\nO2\n";
    cout << O2.transpose() << endl;

    dump_points( O2, fname3 );                               // scrive il file per gnuplot

    return 0;
}