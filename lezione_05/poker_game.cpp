/* --------------------------------------------------------------------------------- *\
    CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)                  Alice Plebe

    Main file per eseguire una partita di poker
\* --------------------------------------------------------------------------------- */

#include "hand.h"
#include <iostream>

using namespace std;
using namespace poker;

int main() {
    // setta il seed al tempo corrente
    // ogni partita sara` diversa dall'altra
    srand( time( NULL ) );

    // crea il deck di carte
    Deck    mazzo   = Deck();

    // crea 10 carte manualmente
    Card    c0( 11, 2 );
    Card    c1( 11, 1 );
    Card    c2( 2, 1 );
    Card    c3( 2, 2 );
    Card    c4( 2, 0 );
    Card    c5( 9, 3 );
    Card    c6( 9, 2 );
    Card    c7( 9, 0 );
    Card    c8( 4, 2 );
    Card    c9( 4, 1 );

    // crea la mano di due giocatori manualmente
    Hand    mano_h  = Hand( "Helen", c0, c1, c2, c3, c4 );
    Hand    mano_c  = Hand( "Chris", c5, c6, c7, c8, c9 );
    mano_h.print();
    mano_c.print();
    cout << endl;
    if ( mano_h > mano_c ) {
        cout << "Vince " << mano_h.get_player() << "!\n";
    }
    else {
        cout << "Vince " << mano_c.get_player() << "!\n";
    }
    cout << endl;

    // crea la mano di due giocatori casualmente
    Hand    mano_a  = Hand( "Alice", &mazzo );
    Hand    mano_e  = Hand( "Elisa", &mazzo );
    mano_a.print();
    mano_e.print();
    cout << endl;
    if ( mano_a > mano_e ) {
        cout << "Vince " << mano_a.get_player() << "!\n";
    }
    else {
        cout << "Vince " << mano_e.get_player() << "!\n";
    }

    return 0;
}