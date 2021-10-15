/* --------------------------------------------------------------------------------- *\
    CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)                  Alice Plebe

    Definizione della classe Hand per gestire una mano di carte da poker
\* --------------------------------------------------------------------------------- */

#include "hand.h"               // include la header contenente le dichiarazioni per Deck
#include <iostream>

using namespace std;
using namespace poker;          // utilizza il namespace creato negli header files


// funzione per ordinare l'array delle carte usando l'algoritmo bubble sort
void Hand::sort_hand() {
    Card    tmp;
    for ( int i=0; i<N_CARDS; ++i ) {
        for ( int j=0; j<N_CARDS-i-1; ++j ) {
            if ( cards[ j ] > cards[ j+1 ] ) {      // se due carte adiacenti non sono in ordine...
                tmp             = cards[ j ];       // ...esegue uno swap
                cards[ j ]      = cards[ j+1 ];
                cards[ j+1 ]    = tmp;
            }
        }
    }
}


// controlla se la mano contiene una coppia
// l'argomento della funzione (passato per riferimento) serve a salvare la carta vincente
bool Hand::check_pair( Card &c ) {
    for ( int i=0; i<N_CARDS-1; ++i ) {
        // vi e` una coppia se due carte adiacenti hanno lo stesso rank
        if ( cards[ i ].same_rank( cards[ i+1 ] ) ) {
            c   = cards[ i+1 ];     // salva la carta vincente (la piu` alta della coppia)
            return true;
        }
    }
    return false;
}


// controlla se la mano contiene una doppia coppia
// gli argomenti della funzione (passati per riferimento) servono a salvare le carte vincenti
bool Hand::check_two_pair( Card &c1, Card &c2 ) {
    for ( int i=0; i<N_CARDS-2; ++i ) {
        for ( int j=i+2; j<N_CARDS-1; ++j ) {
            // vi e` una doppia coppia se due coppie di carte adiacenti hanno lo stesso rank
            if ( cards[ i ].same_rank( cards[ i+1 ] ) && cards[ j ].same_rank( cards[ j+1 ] ) ) {
                c1  = cards[ j+1 ];     // salva le carte vincenti (le piu` alte delle due coppie)
                c2  = cards[ i+1 ];
                return true;
            }
        }
    }
    return false;
}


// controlla se la mano contiene un tris
// l'argomento della funzione (passato per riferimento) serve a salvare la carta vincente
bool Hand::check_three_kind( Card &c ) {
    for ( int i=0; i<N_CARDS-2; ++i ) {
        // vi e` un tris se tre carte adiacenti hanno lo stesso rank
        if ( cards[ i ].same_rank( cards[ i+1 ] ) && cards[ i+1 ].same_rank( cards[ i+2 ] ) ) {
            c   = cards[ i+2 ];     // salva la carta vincente (la piu` alta del tris)
            return true;
        }
    }
    return false;
}


// controlla se la mano contiene una scala
// l'argomento della funzione (passato per riferimento) serve a salvare la carta vincente
bool Hand::check_straight( Card &c ) {
    // vi e` una scala se le prime 4 carte hanno rank consecutivi e...
    if ( cards[ 0 ].same_rank( cards[ 1 ] ) && cards[ 1 ].same_rank( cards[ 2 ] ) && cards[ 2 ].same_rank( cards[ 3 ] ) ) {
        // ...anche l'ultima carta e` in ordine oppure...
        if ( cards[ 3 ].get_rank() + 1 == cards[ 4 ].get_rank() ) {
            c   = cards[ 4 ];       // salva la carta vincente (la piu` alta del mazzo)
            return true;
        }
        // ...l'ultima carta e` un asso e la prima carta e` un due
        if ( ( cards[ 0 ].get_rank() == 0 ) && ( cards[ 4 ].get_rank() == ace ) ) {
            c   = cards[ 3 ];       // salva la carta vincente (la piu` alta del mazzo a parte l'asso)
            return true;
        }
    }
    return false;
}


// controlla se la mano contiene colore
// l'argomento della funzione (passato per riferimento) serve a salvare la carta vincente
bool Hand::check_flush( Card &c ) {
    // vi e` un colore se tutte e 5 le carte hanno lo stesso seme
    if ( cards[ 0 ].same_suit( cards[ 1 ] ) && cards[ 1 ].same_suit( cards[ 2 ] )
    && cards[ 2 ].same_suit( cards[ 3 ] ) && cards[ 3 ].same_suit( cards[ 4 ] ) ) {
        c   = cards[ 4 ];       // salva la carta vincente (la piu` alta del mazzo)
        return true;
    }
    return false;
}


// controlla se la mano contiene un full
// gli argomenti della funzione (passati per riferimento) servono a salvare le carte vincenti
bool Hand::check_full( Card &c1, Card &c2 ) {
    // vi e` un full se le prime due carte sono una coppia, e le ultime due carte sono una coppia, e...
    if ( cards[ 0 ].same_rank( cards[ 1 ] ) && cards[ 3 ].same_rank( cards[ 4 ] ) ) {
        // ...la carta centrale ha lo stesso rank di una sua adiacente
        if ( cards[ 2 ].same_rank( cards[ 1 ] ) ) {
            c1  = cards[ 2 ];       // salva le carte vincenti (una dal tris e una dalla coppia)
            c2  = cards[ 4 ];
            return true;
        }
        // ...la carta centrale ha lo stesso rank di una sua adiacente
        if ( cards[ 2 ].same_rank( cards[ 3 ] ) ) {
            c1  = cards[ 4 ];       // salva le carte vincenti (una dal tris e una dalla coppia)
            c2  = cards[ 0 ];
            return true;
        }
    }
    return false;
}


// controlla se la mano contiene un poker
// l'argomento della funzione (passato per riferimento) serve a salvare la carta vincente
bool Hand::check_four_kind( Card &c ) {
    // vi e` un poker se le tre carte centrali formano un tris e...
    if ( cards[ 1 ].same_rank( cards[ 2 ] ) && cards[ 2 ].same_rank( cards[ 3 ] ) ) {
        // ...la prima o l'ultima carta ha lo stesso rank del tris
        if ( cards[ 0 ].same_rank( cards[ 1 ] ) || cards[ 3 ].same_rank( cards[ 4 ] ) ) {
            c   = cards[ 1 ];       // salva la carta vincente (una del tris centrale)
            return true;
        }
    }
    return false;
}


// controlla se la mano contiene una scala reale
// l'argomento della funzione (passato per riferimento) serve a salvare la carta vincente
bool Hand::check_straight_flush( Card &c ) {
    // vi e` una scala reale se allo stesso tempo vi e` una scala e colore
    return ( check_flush( c ) && check_straight( c ) );
}


// costruttore della classe che pesca 5 carte casualmente dal mazzo
Hand::Hand( string p, Deck *d ) {
    for ( int i=0; i<N_CARDS; ++i ) {
        cards[ i ]  = d->deal();
    }
    sort_hand();        // ordina le carte nella mano
    player  = p;
}


// costruttore della classe che genera la mano da 5 carte passate in argomento
Hand::Hand( string p, Card &c0, Card &c1, Card &c2, Card &c3, Card &c4 ) {
    cards[ 0 ]  = c0;
    cards[ 1 ]  = c1;
    cards[ 2 ]  = c2;
    cards[ 3 ]  = c3;
    cards[ 4 ]  = c4;
    sort_hand();        // ordina le carte nella mano
    player  = p;
}


// stampa a terminale le carte della mano di un giocatore
void Hand::print() {
    string  out     = "";
    for ( int i=0; i<N_CARDS; ++i ) {
        out     += cards[ i ].to_str() + " ";
    }
    cout << player << ":\t" << out << endl;
}


// verifica il punteggio di una carta
// gli argomenti della funzione (passati per riferimento) servono a salvare le carte vincenti
int Hand::check_hand( Card &c1, Card &c2 ) {
    // la funzione controlla dal punteggio piu` forte al piu` debole,
    // stampa un messaggio visualizzando la carta vincente,
    // e restituisce un valore numerico di punteggio[0-8]
    if ( check_straight_flush( c1 ) ) {
        cout << player << " ha una scala reale al " << c1.to_str() << endl;
        return 8;
    }
    if ( check_four_kind( c1 ) ) {
        cout << player << " ha un poker di " << c1.to_str( true ) << endl;          // stampa solo il rank della carta vincente
        return 7;
    }
    if ( check_full( c1, c2 ) ) {
        cout << player << " ha un full di " << c1.to_str( true ) << " e " << c2.to_str( true ) << endl;
        return 6;
    }
    if ( check_flush( c1 ) ) {
        cout << player << " ha colore di " << c1.to_str( false, true ) << endl;     // stampa solo il seme della carta vincente
        return 5;
    }
    if ( check_straight( c1 ) ) {
        cout << player << " ha una scala al " << c1.to_str( true ) << endl;
        return 4;
    }
    if ( check_three_kind( c1 ) ) {
        cout << player << " ha un tris di " << c1.to_str( true ) << endl;
        return 3;
    }
    if ( check_two_pair( c1, c2 ) ) {
        cout << player << " ha una doppia coppia di " << c1.to_str( true ) << " e " << c2.to_str( true ) << endl;
        return 2;
    }
    if ( check_pair( c1 ) ) {
        cout << player << " ha una coppia di " << c1.to_str( true ) << endl;
        return 1;
    }
    cout << player << " non ha nulla, la carta piu` alta e` ";
    if ( cards[ 0 ].get_rank() == ace ) {
        cout << cards[ 0 ].to_str() << endl;
        c1  = cards[ 0 ];       // la carta vincente e` l'asso
    }
    else {
        cout << cards[ 4 ].to_str() << endl;
        c1  = cards[ 4 ];       // la carta vincente e` l'ultima della mano
    }
    return 0;
}


// overloading dell'operatore minore tra due oggetti Hand
// sfida la mano di due giocatori e determina il vincitore
bool Hand::operator < ( Hand &h ) {
    Card    ca1, ca2, cb1, cb2;
    int     score_a     = check_hand( ca1, ca2 );
    int     score_b     = h.check_hand( cb1, cb2 );

    // se entrambi i giocatori hanno lo stesso score...
    if ( score_a == score_b ) {
        // ...se le prime carte vincenti hanno lo stesso rank e si tratta di una doppia coppia o di un full...
        if ( ca1.get_rank() == cb1.get_rank()
        && ( score_a == 2 || score_a == 6 ) ) {
            // ..confronta le seconde carte vincenti
            return ( ca2 < cb2 );
        }
        // ...altrimenti restituisce il confronto sulle prime carte vincenti
        return ( ca1 < cb1 );
    }
    // ...altrimenti restituisce il confronto sugli score dei due giocatori
    return ( score_a < score_b );
}


// overloading dell'operatore minore tra due oggetti Hand
// sfida la mano di due giocatori e determina il vincitore
bool Hand::operator > ( Hand &h ) {
    Card    ca1, ca2, cb1, cb2;
    int     score_a     = check_hand( ca1, ca2 );
    int     score_b     = h.check_hand( cb1, cb2 );

    // se entrambi i giocatori hanno lo stesso score...
    if ( score_a == score_b ) {
        // ...se le prime carte vincenti hanno lo stesso rank e si tratta di una doppia coppia o di un full...
        if ( ca1.get_rank() == cb1.get_rank()
        && ( score_a == 2 || score_a == 6 ) ) {
            // ...confronta le seconde carte vincenti
            return ( ca2 > cb2 );
        }
        // ...altrimenti restituisce il confronto sulle prime carte vincenti
        return ( ca1 > cb1 );
    }
    // ...altrimenti restituisce il confronto sugli score dei due giocatori
    return ( score_a > score_b );
}