/* --------------------------------------------------------------------------------- *\
    CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)                  Alice Plebe

    Interpolazione polinomiale
\* --------------------------------------------------------------------------------- */

#include <iostream>
#include <fstream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

#define     VERBOSE     true            // attiva print opzionali
#define     PREC        3               // precisione per la stampa dei decimali

const int   DEGREE      = 3;            // grado del polinomio interpolatore
const int   N_DATA      = 10;           // numero di dati originali
const int   N_FITS      = 50;           // numero di dati fittati

// informazioni per generazione file gnuplot
const string fname      = "pol_fit.txt";
const string head       = "# --------------------------\n# data generated for gnuplot\n# --------------------------\n";


/*-----------------------------------------------------------------------------------*\
    Calcola i coefficienti del polinomio interpolatore.
    Il problema si esprime in forma matriciale come:
            y = V a
    dove 'y' e` un vettore di lunghezza 'N_DATA', 'V' e` la matrice di Vandermonde,
    e 'a' e` un vettore di lunghezza 'DEGREE+1'.
    Il sistema di equazioni e` sovradimensionato, quindi si calcola la
    Singular Value Decomposition di V.
\*-----------------------------------------------------------------------------------*/
int pfit( VectorXd &x, VectorXd &y, VectorXd &a, int degree ) {
    int     n_data  = x.size();         // lunghezza dei vettori x e y
    int     n_coef  = degree + 1;       // lunghezza del vettore a

    if ( y.size() != n_data ) {         // un check minimo di sicurezza
        return 0;
    }

    // crea la matrice di Vandermonde
    MatrixXd    V( n_data, n_coef );
    for ( int r=0; r<n_data; r++ ) {
        for ( int c=0; c<n_coef; c++ ) {
            V( r, c )   = pow( x( r ), c );
        }
    }

    // calcola la decomposizione SVD di V
    // https://eigen.tuxfamily.org/dox/classEigen_1_1JacobiSVD.html
    JacobiSVD<MatrixXd>     svd( V, ComputeThinU | ComputeThinV );
    if ( VERBOSE ) {
        cout << "\nMatrice di Vandermonde\n";
        cout << V << endl;
        cout << "\nValori singolari SVD\n";
        cout << svd.singularValues() << endl;
        cout << "\nMatrice U (vettore singolari sinistri)\n";
        cout << svd.matrixU() << endl;
        cout << "\nMatrice V (vettore singolari destri)\n";
        cout << svd.matrixV() << endl;
    }

    // calcola i coefficienti del polinomio
    // (il vettore 'a' non viene restituito, ma e` passato per riferimento)
    a   = svd.solve( y );
    return 1;
}


/*-----------------------------------------------------------------------------------*\
    Usa il coefficienti del polinomio per fittare un nuovo punto per una qualunque x
\*-----------------------------------------------------------------------------------*/
double do_fit( VectorXd &a, double x ) {
    double  y   = a( 0 );       // il primo coefficiente per la potenza zero di x

    for ( int i=0; i<a.size(); i++ ) {
        y   += a( i ) * pow( x, i );
    }
    return y;
}


/*-----------------------------------------------------------------------------------*\
    Genera casualmente dei dati x e y di partenza
\*-----------------------------------------------------------------------------------*/
void data_gen( VectorXd &x, VectorXd &y, int n_data ) {
    x   = M_PI * VectorXd::Random( n_data );    // x random tra -Pi e Pi
    y.resize( n_data );                         // fissa la dimensione di y

    // una funzione tanto per...
    for ( int i=0; i<n_data; i++ ) {
        y( i )  = i * sin( x( i ) ) + 0.2 * sin( 2* x( i ) );
    }
}


/*-----------------------------------------------------------------------------------*\
    Scrive su file i dati originali e i nuovi dati fittati dal polinomio
\*-----------------------------------------------------------------------------------*/
void dump_fit( VectorXd &x_0, VectorXd &y_0, VectorXd &x, VectorXd &y ) {
    ofstream    f( fname );                 // stream di output
    f << head;                              // linea di intestazione per gnuplot
    f << fixed << setprecision( PREC );     // fissa la precisione

    // scrive i dati originali su due colonne
    for ( int i=0; i<x_0.size(); i++ ) {
        f << x_0( i ) << "\t" << y_0( i ) << endl;
    }

    f << "\n\n";        // due righe vuote indicano a gnuplot una nuova serie di dati

    // scrive i nuovi dati fittati su due colonne
    for ( int i=0; i<x.size(); i++ ) {
        f << x( i ) << "\t" << y( i ) << endl;
    }
}


int main() {
    cout.precision( PREC );

    VectorXd    x_0;                    // valori x originali
    VectorXd    y_0;                    // valori y originali
    data_gen( x_0, y_0, N_DATA );       // genera i valori originali

    VectorXd    a;                      // vettore dei coefficienti
    pfit( x_0, y_0, a, DEGREE );        // calcola i coefficienti

    if ( VERBOSE ) {
        cout << "\nCoefficienti del polinomio interpolatore\n";
        cout << a << endl;
    }

    // nuovi valori x in un vettore lungo 'N_FITS'
    // generati in modo equidistante tra -Pi e Pi
    VectorXd    x       = VectorXd::LinSpaced( N_FITS, -M_PI, M_PI );
    VectorXd    y( N_FITS );    // nuovi valori y in un vettore lungo 'N_FITS'

    // interpola i nuovi valori di y
    for ( int i=0; i<N_FITS; i++ ) {
        y( i )  = do_fit( a, x( i ) );
    }

    // scrive il file per gnuplot
    dump_fit( x_0, y_0, x, y );

    return 0;
}