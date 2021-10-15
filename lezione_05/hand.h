/* --------------------------------------------------------------------------------- *\
    CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)                  Alice Plebe

    Header file contenente la dichiarazione della classe Hand
\* --------------------------------------------------------------------------------- */

// direttiva del preprocessore per assicurare che questo file venga incluso una volta sola durante la compilazione
#pragma once
#include "deck.h"           // include la header contenente Deck

#define N_CARDS     5       // numero di carte in una mano

namespace poker {
    class Hand {
        private:
            std::string     player;                 // nome del giocatore
            Card            cards[ N_CARDS ];       // array di carte rappresentante la mano del giocatore

            void sort_hand();
            bool check_pair( Card& );
            bool check_two_pair( Card&, Card& );
            bool check_three_kind( Card& );
            bool check_straight( Card& );
            bool check_flush( Card& );
            bool check_full( Card&, Card& );
            bool check_four_kind( Card& );
            bool check_straight_flush( Card& );


        public:
            Hand( std::string, Deck* );
            Hand( std::string, Card&, Card&, Card&, Card&, Card& );
            std::string get_player() { return player; }
            void print();
            int check_hand( Card&, Card& );
            bool operator < ( Hand& );
            bool operator > ( Hand& );
    };
}