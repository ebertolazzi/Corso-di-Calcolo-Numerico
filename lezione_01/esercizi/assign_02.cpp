/* --------------------------------------------------------------------------------- *\
    CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)                  Alice Plebe

    Assignment: stampa i primi N numeri primi
\* --------------------------------------------------------------------------------- */

#include <iostream>
using namespace std;

int main() {
    int     n;
    cout << "Quanti numeri primi vuoi calcolare? ";
    cin >> n;

    bool    prime;                          // booleano, false quando il numero non e` primo
    int     count   = n;                    // contatore per il numero di risultati rimasti da trovare
    int     num     = 2;                    // inizia a cercare numeri primi a partire da 2 (1 non e` primo)

    while ( count > 0 ) {                   // quando il contatore arriva a zero, ha trovato tutti i numeri richiesti
        prime       = true;                 // inizializza il booleano a true

        for ( int i = 2; i < num; ++i ) {   // cerca un divisore di 'num' tra i numeri da 2 a num-1
            if ( ( num % i ) == 0 ) {       // se 'num' e` divisibile per 'i'...
                prime   = false;            // ...non e` primo, e il booleano viene settato a false...
                break;                      // ...ed esce dal for
            }
        }
        if ( prime ) {                      // se il booleano e` rimasto a true...
            cout << num << endl;            // ...il numero e` primo...
            --count;                        // ...e il numero di risultati da trovare diminuisce di 1
        }
        ++num;                              // alla prossima iterazione, controlla se il successivo di 'num' e` primo
    }
    return 0;
}