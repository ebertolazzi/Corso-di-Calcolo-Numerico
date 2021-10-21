/* --------------------------------------------------------------------------------- *\
    CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)                  Alice Plebe

    Header file contenente la dichiarazione della classe Deck
\* --------------------------------------------------------------------------------- */

// direttiva del preprocessore per assicurare che questo file venga incluso una volta sola durante la compilazione
#pragma once
#include "card.h"           // include la header contenente Card

#define N_SUITS     4       // numero di semi delle carte
#define N_RANKS     13      // numero di valori delle carte

namespace poker {
    class Deck {
        private:
            bool    cards[ N_RANKS ][ N_SUITS ];    // matrice rappresentante un mazzo di 52 carte

        public:
            Deck();
            Card deal();
            void reset();
    };
}