/* --------------------------------------------------------------------------------- *\
    CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)                  Alice Plebe

    Assignment: calcola la differenza tra orari
\* --------------------------------------------------------------------------------- */

#include <iostream>
using namespace std;


// struttura che rappresenta un orario
struct orario {
    int     ore;
    int     minuti;
    int     secondi;
};


// visualizza un orario
void print_orario( orario o ) {
    cout << "Orario: " << o.ore << ":" << o.minuti << ":" << o.secondi << endl;
}


// imposta un orario con i numeri passati da terminale
// continua a richiedere il valore se viene passato un numero fuori dal range
void set_orario( orario *o ) {
    cout << "Scrivi le ore (0-24): ";
    cin >> o->ore;
    while ( o->ore < 0 || o->ore > 23 ) {
        cout << "RIPROVA: le ore devono essere comprese tra 0 e 23: ";
        cin >> o->ore;
    }

    cout << "Scrivi i minuti (0-60): ";
    cin >> o->minuti;
    while ( o->minuti < 0 || o->minuti > 59 ) {
        cout << "RIPROVA: i minuti devono essere compresi tra 0 e 59: ";
        cin >> o->minuti;
    }

    cout << "Scrivi i secondi (0-60): ";
    cin >> o->secondi;
    while ( o->secondi < 0 || o->secondi > 59 ) {
        cout << "RIPROVA: i secondi devono essere compresi tra 0 e 59: ";
        cin >> o->secondi;
    }
}


// calcola 'o1 - o2' e salva il risultato in 'o3'
void diff_orario( orario o1, orario o2, orario *o3 ) {
    // se 'o2' e` maggiore di 'o1', esegue uno swap
    // in questo modo il risultato non e` negativo
    if ( o2.ore > o1.ore ) {
        orario  tmp     = o1;
        o1              = o2;
        o2              = tmp;
    }

    // se i secondi di 'o1' sono minori di 'o2', converte un minuto in secondi
    // in questo modo il risultato non e` negativo
    if ( o2.secondi > o1.secondi ) {
        o1.minuti--;
        o1.secondi      += 60;
    }
    o3->secondi         = o1.secondi - o2.secondi;

    // se i minuti di 'o1' sono minori di 'o2', converte un'ora in minuti
    // in questo modo il risultato non e` negativo
    if ( o2.minuti > o1.minuti ) {
        o1.ore--;
        o1.minuti       += 60;
    }
    o3->minuti          = o1.minuti - o2.minuti;

    o3->ore             = o1.ore - o2.ore;
}


int main() {
    orario  o1, o2, o3;

    set_orario( &o1 );
    print_orario( o1 );
    cout << "\n";

    set_orario( &o2 );
    print_orario( o2 );
    cout << "\n";

    // la differenza di orario viene salvata in 'o3'
    diff_orario( o1, o2, &o3 );
    print_orario( o3 );

    return 0;
}