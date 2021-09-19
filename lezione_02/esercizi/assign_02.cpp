/* --------------------------------------------------------------------------------- *\
    CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)                  Alice Plebe

    Assignment: calcola massimo, minimo, media, varianza, e stdev di un array
\* --------------------------------------------------------------------------------- */

#include <iostream>
#include <cmath>
using namespace std;


// trova l'elemento maggiore dell'array
// i parametri sono il puntatore al primo elemento dell'array, e la lunghezza dell'array
double get_max( double *a, int l ) {
    double  max     = *a;                   // inizializza 'max' al primo elemento dell'array
    for ( int i = 0; i < l; ++i, ++a ) {
        if ( max < *a ) {                   // se trova un elemento ancora piu` grande...
            max     = *a;                   // ...aggiorna il valore di 'max'
        }
    }
    return max;
}

// trova l'elemento minore dell'array
double get_min( double *a, int l ) {
    double  min     = *a;                   // inizializza 'min' al primo elemento dell'array
    for ( int i = 0; i < l; ++i, ++a ) {
        if ( min > *a ) {                   // se trova un elemento ancora piu` piccolo...
            min     = *a;                   // ...aggiorna il valore di 'min'
        }
    }
    return min;
}

// calcola la somma degli elementi dell'array
double get_sum( double *a, int l ) {
    double  sum = 0;
    for ( int i = 0; i < l; ++i, ++a ) {
        sum     += *a;
    }
    return sum;
}

// calcola la media degli elementi dell'array
double get_avg( double *a, int l ) {
    return get_sum( a, l ) / l;
}

// calcola la varianza
double get_var( double *a, int l ) {
    double  var = 0;
    double  avg = get_avg( a, l );
    for ( int i = 0; i < l; ++i, ++a ) {
        var     += pow( *a - avg, 2 );
    }
    var     /= l;
    return var;
}

// calcola la standard deviation
double get_std( double *a, int l ) {
    return sqrt( get_var( a, l ) );
}


int main() {
    int     len     = 7;
    double  arr[]   = { 45.3, -0.465, 12.395, 1095.5, 88.003, -208.501, 401.986 };

    cout << "L'elemento maggiore:\t\t" << get_max( arr, len ) << endl;
    cout << "L'elemento minore:\t\t" << get_min( arr, len ) << endl;
    cout << "La somma degli elementi:\t" << get_sum( arr, len ) << endl;
    cout << "La media degli elementi:\t" << get_avg( arr, len ) << endl;
    cout << "La varianza degli elementi:\t" << get_var( arr, len ) << endl;
    cout << "La deviazione standard:\t\t" << get_std( arr, len ) << endl;

    return 0;
}