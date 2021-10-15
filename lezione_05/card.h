/* --------------------------------------------------------------------------------- *\
    CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)                  Alice Plebe

    Header file contenente la dichiarazione della classe Card
\* --------------------------------------------------------------------------------- */

// direttiva del preprocessore per assicurare che questo file venga incluso una volta sola durante la compilazione
#pragma once                    
#include <string>

#define SPADES      "\u2660"        // codice unicode per il simbolo picche
#define CLUBS       "\u2663"        // codice unicode per il simbolo fiori
#define DIAMONDS    "\u2666"        // codice unicode per il simbolo quadri
#define HEARTS      "\u2665"        // codice unicode per il simbolo cuori
#define ACE         'A'             // carattere per il simbolo asso
#define JACK        'J'             // carattere per il simbolo jack
#define QUEEN       'Q'             // carattere per il simbolo regina
#define KING        'K'             // carattere per il simbolo re

namespace poker {   // definizione di un nuovo namespace
    enum    suits { spades, clubs, diamonds, hearts };              // enumerato per i semi delle carte
    enum    ranks { jack = 9, queen = 10, king = 11, ace = 12 };    // enumerato per le carte vestite

    class Card {
        private:
            int     suit;       // seme di una carta
            int     rank;       // valore di una carta

        public:
            Card() {};          // costruttore vuoto
            Card( int, int );
            std::string to_str( bool = false, bool = false );
            int get_suit() { return suit; }
            int get_rank() { return rank; }
            bool operator < ( const Card& );
            bool operator > ( const Card& );
            bool same_rank( const Card& );
            bool same_suit( const Card& );
    };
}