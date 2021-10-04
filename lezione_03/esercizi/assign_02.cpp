/* --------------------------------------------------------------------------------- *\
    CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)                  Alice Plebe

    Assignment: crea una classe per gestire i posti in un cinema
\* --------------------------------------------------------------------------------- */

#include <iostream>
using namespace std;

const int   MAX_ROWS    = 32;       // massimo numero di righe consentite in un cinema
const int   MAX_COLS    = 32;       // massimo numero di colonne consentite in un cinema


// classe per la gestione dei posti in una sala cinema
class Theater {
    private:
        int     rows;                               // numero di righe nel cinema
        int     cols;                               // numero di colonne nel cinema
        bool    seats[ MAX_ROWS ][ MAX_COLS ];      // matrice dei posti (false=posto libero, true=posto occupato)

    public:
        Theater( int r, int c ) {
            // verifica che non si superi il max numero di righe consentite
            if ( r > MAX_ROWS ) {
                cout << "WARNING: superato massimo numero di righe" << endl;
                rows    = MAX_ROWS;
            }
            else {
                rows    = r;
            }
            // verifica che non si superi il max numero di colonne consentite
            if ( c > MAX_COLS ) {
                cout << "WARNING: superato massimo numero di colonne" << endl;
                cols    = MAX_COLS;
            }
            else {
                cols    = c;
            }
            // inizializza il cinema con tutti i posti liberi
            for ( int i = 1; i <= rows; ++i ) {
                for ( int j = 1; j <= cols; ++j ) {
                    seats[ i ][ j ]     = false;
                }
            }
        }


        // stampa i posti del cinema
        void view_seats() {
            cout << endl;
            for ( int r = 1; r <= rows; ++r ) {
                for ( int c = 1; c <= cols; ++c ) {
                    cout << seats[ r ][ c ] << " ";
                }
                cout << endl;
            }
            cout << endl;
        }


        // prenota un posto nel cinema
        void book_seat( int r, int c ) {
            // verifica che il numero di riga sia nel range
            if ( r < 1 || r > rows ) {
                cout << "ERRORE: la riga e` fuori dal range [1-" << rows << "]" << endl;
                return;
            }
            // verifica che il numero di colonna sia nel range
            if ( c < 1 || c > cols ) {
                cout << "ERRORE: la colonna e` fuori dal range [1-" << cols << "]" << endl;
                return;
            }
            // verifica che il posto non sia gia` prenotato
            if ( seats[ r ][ c ] ) {
                cout << "Il posto selezionato [" << r << "," << c << "] risulta gia` prenotato" << endl;
                return;
            }
            seats[ r ][ c ]     = true;
        }


        // conta il numero di posti liberi
        int check_seats() {
            int cnt     = 0;

            for ( int r = 1; r <= rows; ++r ) {
                for ( int c = 1; c <= cols; ++c ) {
                    if ( ! seats[ r ][ c ] ) {
                        cnt++;
                    }
                }
            }
            return cnt;
        }
};


int main() {
    Theater     cine( 4, 6 );
    cine.view_seats();
    cine.book_seat( 2, 3 );
    cine.book_seat( 2, 4 );
    cine.book_seat( 4, 5 );
    cine.book_seat( 3, 6 );
    cine.book_seat( 2, 3 );
    cine.view_seats();
    cout << "Restano " << cine.check_seats() << " posti liberi nel cinema" << endl;

    return 0;
}