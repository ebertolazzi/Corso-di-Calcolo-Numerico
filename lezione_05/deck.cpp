/* --------------------------------------------------------------------------------- *\
    CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)                  Alice Plebe

    Definizione della classe Deck per gestire un mazzo di carte da poker
\* --------------------------------------------------------------------------------- */

#include "deck.h"               // include la header contenente le dichiarazioni per Deck
#include <iostream>

using namespace std;
using namespace poker;          // utilizza il namespace creato negli header files


// reinserisce tutte le carte nel mazzo
void Deck::reset() {
    for ( int i=0; i<N_RANKS; ++i ) {
        for ( int j=0; j<N_SUITS; ++j ) {
            cards[ i ][ j ]     = true;
        }
    }
}


// costruttore che inizializza la matrice del mazzo
Deck::Deck() {
    reset();
}


// restituisce casualmente una carta nel mazzo
Card Deck::deal() {
    int r   = rand() % N_RANKS;             // estrae casualmente un seme
    int s   = rand() % N_SUITS;             // estrae casualmente un rank

    while ( !cards[ r ][ s ] ) {            // se la carta non e` nel mazzo, riprova
        r   = rand() % N_RANKS;
        s   = rand() % N_SUITS;
    }
    // ATTENZIONE questo loop potrebbe potenzialmente non terminare mai se il mazzo e` vuoto...

    cards[ r ][ s ] = false;                // una volta estratta, segna la carta come fuori dal mazzo
    return Card( r, s );
}