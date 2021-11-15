/* --------------------------------------------------------------------------------- *\
    CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)                  Alice Plebe

    Classe per rappresentare un poligono
\* --------------------------------------------------------------------------------- */

#include "poly.h"

using namespace std;
using namespace Eigen;


/*-----------------------------------------------------------------------------------*\
    Costruttore con argomento solo il grado del polinomio
\*-----------------------------------------------------------------------------------*/
Poly::Poly( int n ) {
    coef	= VectorXd::Zero( n );
    degr    = n;
}

/*-----------------------------------------------------------------------------------*\
    Costruttore con argomento il vettore dei coefficienti
\*-----------------------------------------------------------------------------------*/
Poly::Poly( const VectorXd c ) {
    coef    = c;
    degr    = c.size();
}

/*-----------------------------------------------------------------------------------*\
    Valuta il polinomio, ovvero sostituisce alle variabili il valore in argomento 
\*-----------------------------------------------------------------------------------*/
double Poly::eval( float x ) {
    double x_pow	= x;
    double y	    = coef( 0 );
    for( int i=1; i<degr; i++ ) {
        y	    += coef( i ) * x_pow;
        x_pow	*= x;
    }
    return y;
}

/*-----------------------------------------------------------------------------------*\
    Permette di stampare il polinomio su "cout" con l'operatore <<
\*-----------------------------------------------------------------------------------*/
ostream &operator<<( ostream &output, const Poly &p ) {
    bool    empty   = true;     // true indica che i coefficienti finora sono nulli
    string  s       = "";       // segno
    double  c       = 0;        // coefficiente
    string  e       = "";       // esponente

    output << "p(x) = ";

    // controlla se esiste il primo coefficiente (grado 0)
    if ( p.coef[ 0 ] != 0 ) {
        output << p.coef[ 0 ];
        empty   = false;
    }

    for( int i=1; i<p.degr; i++ ) {
        // se il coefficiente e` negativo...
        if ( p.coef[ i ] < 0 ) {
            // e se i coefficienti precenti erano nulli...
            if ( empty ) {
                s       = "";               // ...non scrive il segno
                c       = p.coef[ i ];
                empty   = false;
            } else {
                s       = " - ";            // ...altrimenti scrive il segno come separatore
                c       = -p.coef[ i ];        // e inverte il segno del coefficiente
            }

        // se il coefficiente e` positivo...
        } else if ( p.coef[ i ] > 0 ) {
            c   = p.coef[ i ];
            // e se i coefficienti precenti erano nulli...
            if ( empty ) {
                s       = "";               // ...non scrive il segno
                empty   = false;
            } else {
                s       = " + ";            // ...altrimenti scrive il segno come separatore
            }

        // se il coefficiente e` zero...
        } else {
            continue;                       // ...procede al prossimo
        }

        // se il grado e` 1 non scrive l'esponente
        if ( i == 1 ) {
            e   = "x";
        } else {
            e   = "x^" + to_string( i );
        }

        output << s << c << e;              // stampa
    }
    output << endl;
    return output;
}

/*-----------------------------------------------------------------------------------*\
    Somma due polinomi di grado qualsiasi
\*-----------------------------------------------------------------------------------*/
Poly Poly::operator+( const Poly& p ) {
    int     max, min;
    bool    p_has_max;

    if ( degr > p.degr ) {
        p_has_max   = false;
        max		    = degr;
        min		    =  p.degr;
    } else {
        p_has_max	= true;
        max		    = p.degr;
        min		    = degr;
    }
    Poly sum( max );    // nuovo polinomio contenente la somma

    // somma i coefficieti fino al grado comune ad entrambi i polinomi
    for( int i=0; i<min; i++ ) {
        sum.coef[ i ]	= coef[ i ] + p.coef[ i ];
    }

    // per i gradi successivi controlla ogni volta
    for( int i=min; i<max; i++ ) {
        if ( p_has_max ) {
            sum.coef[ i ]	= p.coef[ i ];
        } else {
            sum.coef[ i ]	= coef[ i ];
        }
    }
    return sum;
}

/*-----------------------------------------------------------------------------------*\
    Calcola il prodotto di due polinomi di grado qualsiasi
\*-----------------------------------------------------------------------------------*/
Poly Poly::operator*( const Poly& p ) {
    Poly prd( degr + p.degr - 1 );        // nuovo polinomio contenente il risultato

    for( int i=0; i<degr; i++ ) {
        for( int j=0; j<p.degr; j++ ) {
            prd.coef[ i+j ]   += coef[ i ] * p.coef[ j ];
        }
    }
    return prd;
}

/*-----------------------------------------------------------------------------------*\
    Calcola la derivata del polinomio
\*-----------------------------------------------------------------------------------*/
Poly Poly::derivative() {
    Poly der( degr - 1 );        // nuovo polinomio contenente il risultato

    for( int i=1; i<degr; i++ ) {
        der.coef[ i-1 ]	= i * coef[ i ];
    }
    return der;
}

/*-----------------------------------------------------------------------------------*\
    Calcola l'integrale del polinomio
\*-----------------------------------------------------------------------------------*/
Poly Poly::integral() {
    Poly itg( degr + 1 );        // nuovo polinomio contenente il risultato

    for( int i=0; i<degr; i++ ) {
        itg.coef[ i+1 ]	= coef[ i ] / ( i+1 );
    }
    return itg;
}