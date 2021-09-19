/* --------------------------------------------------------------------------------- *\
    CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)                  Alice Plebe

    Overloading e parametri di default
\* --------------------------------------------------------------------------------- */

#include <iostream>
#include <cmath>
using namespace std;


// ===== OVERLOADING CON DIVERSO TIPO DI PARAMETRI =====
// le seguenti due funzioni hanno lo stesso nome, ma diversi parametri e tipi restituiti
 
int give_next( int n ) {        // restituisce il successivo di un numero intero
    return n + 1;
}

char give_next( char c ) {      // restituisce la lettera successiva in ordine alfabetico
    switch ( c ) {
        case 'z':
            return 'a';
        case 'Z':
            return 'A';
        default:
            return ( char )( ( int ) c + 1 );   // i char corrispondono a codici numerici
    }
}


// ===== OVERLOADING CON DIVERSO NUMERO DI PARAMETRI =====
// le seguenti due funzioni hanno lo stesso nome e tipo restituito, ma diverso numero di parametri

void stampa( double n ) {
    cout << "Guarda che gran numero: " << n << endl;
}
 
void stampa( double n, double m ) {
    cout << "Due numeri interessanti: " << n << " e " << m << endl;
}

 
// ===== PARAMETRI DI DEFAULT =====

// il secondo parametro di questa funzione e` opzionale
// se non viene passato, la funzione usa il valore di default 2
double potenza( double b, double e = 2 ) {
    return pow( b, e );                     // funzione in <cmath>
}

// in questa funzione entrambi i parametri sono opzionali
void faccina( char occhi = ':', char bocca = ')' ) {
    cout << "Ecco una faccina  " << occhi << bocca << endl;
}

// questa funzione darebbe errore
// una volta definito un parametro opzionale, tutti i successivi parametri devono pure essere opzionali
/*
void faccina( char occhi = ':', char bocca ) {
    cout << "Ecco una faccina  " << occhi << bocca << endl;
}
*/


int main() {
    int     num;
    char    let;

    cout << "Dammi un intero: ";
    cin >> num;
    cout << "Il successivo e`: " << give_next( num ) << "\n\n";

    cout << "Dammi una lettera: ";
    cin >> let;
    cout << "La successiva e`: " << give_next( let ) << "\n\n";

    cout << "8^2 = " << potenza( 8 ) << endl;
    cout << "8^3 = " << potenza( 8, 3 ) << "\n\n";

    faccina();              // nessun argomento passato, si usa il default per entrambi
    faccina( 'B' );         // primo argomento passato, si usa il default per il secondo
    faccina( ';', 'P' );    // entrambi argomenti passati
    // non e` possibile usare il default per il primo argomento, e passare solo il secondo argomento

    return 0;
}