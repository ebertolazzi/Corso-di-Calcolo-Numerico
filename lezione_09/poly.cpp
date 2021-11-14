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
    v	    = VectorXd::Zero( n );
    deg	    = n;
}

/*-----------------------------------------------------------------------------------*\
    Costruttore con argomento il vettore dei coefficienti
\*-----------------------------------------------------------------------------------*/
Poly::Poly( const VectorXd c ) {
    v       = c;
    deg	    = c.size();
}

/*-----------------------------------------------------------------------------------*\
    Valuta il polinomio, ovvero sostituisce alle variabili il valore in argomento 
\*-----------------------------------------------------------------------------------*/
double Poly::eval( float x ) {
    double x_pow	= x;
    double y	    = v( 0 );
    for( int i=1; i<deg; i++ ) {
        y	    += v( i ) * x_pow;
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
    if ( p.v[ 0 ] != 0 ) {
        output << p.v[ 0 ];
        empty   = false;
    }

    for( int i=1; i<p.deg; i++ ) {
        // se il coefficiente e` negativo...
        if ( p.v[ i ] < 0 ) {
            // e se i coefficienti precenti erano nulli...
            if ( empty ) {
                s       = "";               // ...non scrive il segno
                c       = p.v[ i ];
                empty   = false;
            } else {
                s       = " - ";            // ...altrimenti scrive il segno come separatore
                c       = -p.v[ i ];        // e inverte il segno del coefficiente
            }

        // se il coefficiente e` positivo...
        } else if ( p.v[ i ] > 0 ) {
            c   = p.v[ i ];
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

	if ( deg > p.deg ) {
		p_has_max   = false;
		max		    = deg;
		min		    =  p.deg;
	} else {
		p_has_max	= true;
		max		    = p.deg;
		min		    = deg;
	}
	Poly sum( max );    // nuovo polinomio contenente la somma

    // somma i coefficieti fino al grado comune ad entrambi i polinomi
	for( int i=0; i<min; i++ ) {
		sum.v[ i ]	= v[ i ] + p.v[ i ];
	}

    // per i gradi successivi controlla ogni volta
	for( int i=min; i<max; i++ ) {
		if ( p_has_max ) {
			sum.v[ i ]	= p.v[ i ];
		} else {
			sum.v[ i ]	= v[ i ];
		}
	}
	return sum;
}

/*-----------------------------------------------------------------------------------*\
    Calcola il prodotto di due polinomi di grado qualsiasi
\*-----------------------------------------------------------------------------------*/
Poly Poly::operator*( const Poly& p ) {
	Poly prd( deg + p.deg - 1 );        // nuovo polinomio contenente il risultato

	for( int i=0; i<deg; i++ ) {
        for( int j=0; j<p.deg; j++ ) {
            prd.v[ i+j ]   += v[ i ] * p.v[ j ];
        }
	}
	return prd;
}

/*-----------------------------------------------------------------------------------*\
    Calcola la derivata del polinomio
\*-----------------------------------------------------------------------------------*/
Poly Poly::derivative() {
	Poly der( deg - 1 );        // nuovo polinomio contenente il risultato

	for( int i=1; i<deg; i++ ) {
		der.v[ i-1 ]	= i * v[ i ];
	}
	return der;
}

/*-----------------------------------------------------------------------------------*\
    Calcola l'integrale del polinomio
\*-----------------------------------------------------------------------------------*/
Poly Poly::integral() {
	Poly der( deg + 1 );        // nuovo polinomio contenente il risultato

	for( int i=0; i<deg; i++ ) {
		der.v[ i+1 ]	= v[ i ] / ( i+1 );
	}
	return der;
}