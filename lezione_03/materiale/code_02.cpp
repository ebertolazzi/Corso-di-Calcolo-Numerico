/* --------------------------------------------------------------------------------- *\
    CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)                  Alice Plebe

    Esempio: algoritmi di ordinamento
\* --------------------------------------------------------------------------------- */

#include <iostream>
using namespace std;


// funzione per stampare gli elementi di un array
// i parametri sono il puntatore al primo elemento dell'array, e la lunghezza dell'array
void print_arr( int *a, int l ) {
    for ( int i = 0; i < l; ++i, ++a ) {
        cout << *a << " ";      // usa lo stesso puntatore 'a' per scorrere gli elementi
    }
    cout << endl;
}

// funzione per scambiare i valori tra due puntatori
void swap_val( int *n1, int *n2 ) {
    int tmp = *n1;
    *n1     = *n2;     
    *n2     = tmp;
}

// ordina l'array 'a' usando l'algoritmo bubble sort (https://youtu.be/lyZQPjUT5B4)
void bubble_sort( int *a, int l ) {
    for ( int i = 0; i < l; ++i ) {
        for ( int j = 0; j < l-i-1; ++j ) {
            // confronta elementi adiacenti, se non sono in ordine...
            if ( a[ j ] > a[ j + 1 ] ) {
                swap_val( &a[ j ], &a[ j + 1 ] );     // ...vengono scambiati
            }
        }
    }
}

// funzione di supporto usata dentro selection_sort() 
// restituisce l'indice dell'elemento piu` piccolo nella porzione di array tra 'indx' e 'l'
int smallest( int *a, int l, int indx ) {
    int small       = a[ indx ];        // valore minore corrente
    int new_indx    = indx;             // indice del valore minore corrente

    for ( int i = indx+1; i < l; ++i ) {
        if ( a[ i ] < small ) {         // se trova un numero piu` piccolo del minore corrente...
            small       = a[ i ];       // ...aggiorna il valore minore corrente...
            new_indx    = i;            // ...e l'indice del valore minore corrente
        }
    }
    return new_indx;
}

// ordina l'array 'a' usando l'algoritmo algoritmo selection sort (https://youtu.be/Ns4TPTC8whw)
void selection_sort( int *a, int l ) {
    int j;
    for ( int i = 0; i < l; ++i ) {
        // trova il valore minore nella porzione di array ancora non scansionata...
        j       = smallest( a, l, i );
        // e lo scambia con il valore alla posizione corrente
        swap_val( &a[ i ], &a[ j ] );
    }
}


int main() {
    const int   len_a       = 7;
    const int   len_b       = 6;
    int         arr_a[]     = { 34, 7, 19, 3, 102, 32, 12 };
    int         arr_b[]     = { 1, -19, 703, 0, 62, -3 };

    cout << "Before:\t";
    print_arr( arr_a, len_a );
    bubble_sort( arr_a, len_a );
    cout << "After:\t";
    print_arr( arr_a, len_a );

    cout << endl;

    cout << "Before:\t";
    print_arr( arr_b, len_b );
    selection_sort( arr_b, len_b );
    cout << "After:\t";
    print_arr( arr_b, len_b );

    return 0;
}