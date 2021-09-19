/* --------------------------------------------------------------------------------- *\
    CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)                  Alice Plebe

    Assignment: calcola il massimo comume divisore e il minimo comune multiplo
\* --------------------------------------------------------------------------------- */

#include <iostream>
using namespace std;


// massimo comune divisore
int mcd( int n, int m ) {
    if ( m != 0 ) {
        return mcd( m, n % m );     // funzione ricorsiva che implementa l'algoritmo di Euclide
    }
    return n;
}

// minimo comune multiplo -- versione naive
int mcm1( int n, int m ) {
    int     max     = ( n > m ) ? n : m;

    while ( true ) {
        if ( ( max % n == 0 ) && ( max % m == 0 ) ) {
            return max;
        }
        ++max;
    }
}

// minimo comune multiplo -- versione con mcd()
int mcm2( int n, int m ) {
    int     max     = mcd( n, m );
    return ( n * m ) / max;
}

int main() {
    int     n1, n2;
    cout << "Scrivi due numeri interi positivi:" << endl;
    cin >> n1 >> n2;

    cout << "Massimo comune divisore di " << n1 << " e " << n2 << " = " << mcd( n1, n2 ) << endl;
    cout << "Minimo comune multiplo di " << n1 << " e " << n2 << " = " << mcm1( n1, n2 ) << endl;
    cout << "Minimo comune multiplo di " << n1 << " e " << n2 << " = " << mcm2( n1, n2 ) << endl;

    return 0;
}