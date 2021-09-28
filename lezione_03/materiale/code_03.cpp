/* --------------------------------------------------------------------------------- *\
    CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)                  Alice Plebe

    Strutture
\* --------------------------------------------------------------------------------- */

#include <iostream>
using namespace std;


// ===== STRUTTURE =====

// struttura per tenere una collezione di variabili che insieme definiscono un film
struct movie {
    char    title[ 50 ];
    int     year;
    double  rating;
};      // attenzione serve il punto e virgola

// il parametro di questa funzione e` di tipo 'struct movie'
void print_movie( movie m ) {
    // si usa l'operatore punto per accedere ai membri di una variabile struttura
    cout << "Titolo:\t" << m.title << endl;
    cout << "Anno:\t" << m.year << endl;
    cout << "Voto:\t" << m.rating << endl;
}

// il parametro di questa funzione e` un puntatore a variabile di tipo 'movie'
void fill_movie( movie *m ) {
    cout << "Scrivi il titolo: ";
    // si usa l'operatore freccia per accedere ai membri di un puntatore a struttura
    cin.get( m->title, 50 );
    cin.clear();
    fflush( stdin );

    cout << "Scrivi l'anno: ";
    cin >> m->year;
    cout << "Scrivi il voto (tra 0 e 10): ";
    cin >> m->rating;

    // continua a richiedere 'rating' se viene passato un numero fuori dal range [0,10]
    while ( m->rating < 0 || m->rating > 10 ) {
        cout << "RIPROVA: il voto deve essere compreso tra 0 e 10: ";
        cin >> m->rating;
    }
}


// ===== ENUMERATI =====

// tipo enumerato che definisce i semi delle carte come costanti intere
// spades   = 0
// clubs    = 1
// diamonds = 2
// hearts   = 3
enum suit { spades, clubs, diamonds, hearts };


int main() {
    movie   m1;
    fill_movie( &m1 );
    print_movie( m1 );

    suit    card1   = spades;               // variabile di tipo 'enum suit'
    suit    card2   = hearts;
    cout << ( card1 == spades ) << endl;
    cout << card2 << endl;

    return 0;
}