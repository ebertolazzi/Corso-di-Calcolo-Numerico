/* --------------------------------------------------------------------------------- *\
    CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)                  Alice Plebe

    Definizione della classe Card per rappresentare una carta da poker
\* --------------------------------------------------------------------------------- */

#include "card.h"           // include la header contenente le dichiarazioni per Card
#include <iostream>

using namespace std;
using namespace poker;      // utilizza il namespace creato negli header files


// costruttore della classe che inizializza gli attributi 'rank' e 'suit'
Card::Card( int r, int s ) {
    if ( s < 0 || s > 3 ) {
        cout << "ERRORE: il seme deve essere nel range [0-3]" << endl;
        return;
    }
    if ( r < 0 || s > 12 ) {
        cout << "ERRORE: il rank deve essere nel range [0-12]" << endl;
        return;
    }
    rank    = r;
    suit    = s;
}


// funzione per stampare a terminale una Card
// se no_suit=true stampa solamente il rank
// se no_rank=true stampa solamente il seme
string Card::to_str( bool no_suit, bool no_rank ) {
    string  out = "";           // parte da una stringa vuota

    if ( !no_rank ) {
        switch ( rank ) {
            case jack:
                out += JACK;                    // concatena il simbolo del jack
                break;
            case queen:
                out += QUEEN;                   // concatena il simbolo della regina
                break;
            case king:
                out += KING;                    // concatena il simbolo del re
                break;
            case ace:
                out += ACE;                     // concatena il simbolo dell'asso
                break;
            default:
                out += to_string( rank + 2 );   // concatena il numero della carta (shiftato di 2)
        }
    }
    if ( !no_suit ) {
        switch ( suit ) {
            case spades:
                out += SPADES;                  // concatena il simbolo di picche
                break;
            case clubs:
                out += CLUBS;                   // concatena il simbolo di fiori
                break;
            case diamonds:
                out += DIAMONDS;                // concatena il simbolo di quadri
                break;
            case hearts:
                out += HEARTS;                  // concatena il simbolo di cuori
                break;
        }
    }
    return out;
}
    

// overloading dell'operatore minore tra due oggetti Card
bool Card::operator < ( const Card &c ) {
    if ( rank == c.rank ) {             // se due carte hanno lo stesso rank...
        return ( suit < c.suit );       // ...controlla il seme minore
    }
    return ( rank < c.rank );
}


// overloading dell'operatore maggiore tra due oggetti Card
bool Card::operator > ( const Card &c ) {
    if ( rank == c.rank ) {             // se due carte hanno lo stesso rank...
        return ( suit > c.suit );       // ...controlla il seme maggiore
    }
    return ( rank > c.rank );
}


// verifica se due carte hanno lo stesso rank
bool Card::same_rank ( const Card &c ) {
    return ( rank == c.rank );
}


// verifica se due carte hanno lo stesso suit
bool Card::same_suit ( const Card &c ) {
    return ( suit == c.suit );
}