/* --------------------------------------------------------------------------------- *\
    CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)                  Alice Plebe

    Ereditarieta`
\* --------------------------------------------------------------------------------- */

#include <iostream>
using namespace std;

// classe base per rappresentare una pianta
class Pianta {
    private:
        int     num_foglie;                 // numero di foglie

        // funzione friend della classe 'Pianta'
        // che permettere di accedere ai dati private e protected fuori da 'Pianta'
        friend void pota( Pianta*, int );

    public:
        // il costruttore inizializza il numero di foglie
        Pianta( int f ) {
            num_foglie  = f;
        }

        // fa crescere la pianta aumentando il numero di foglie di 'f'
        void cresci( int f ) {
            if ( f <= 0 ) {
                cout << "ERRORE: devi specificare un numero positivo di foglie" << endl;
                return;
            }
            num_foglie  += f;
        }

        // restituisce il numero di foglie
        int get_foglie() {
            return num_foglie;
        }
};


// funzione friend di 'Pianta'
// pota la pianta rimovendo il numero di foglie indicate in argomento
void pota( Pianta *p, int n ) {
    if ( n > p->num_foglie ) {
        cout << "ERRORE: non puoi potare piu` foglie di quelle che la pianta possiede" << endl;
        return;
    }
    p->num_foglie  -= n;
}


// sottoclasse di 'Pianta'
class Cespuglio : public Pianta {
    private:
        double  altezza;            // quanto e` alto il cespuglio in cm
        double  larghezza;          // quanto e` largo il cespuglio in cm

    public:
        // chiama il costruttore di 'Pianta' per inizializzare le foglie
        Cespuglio( int f, double a, double l ) : Pianta( f ) {
            altezza     = a;
            larghezza   = l;
        }

        // fa crescere il cespuglio aumentando le foglie, l'altezza, e la larghezza
        void cresci( int f, double a, double l ) {
            Pianta::cresci( f );        // chiama la funzione cresci() della classe 'Pianta'
            if ( a <= 0 ) {
                cout << "ERRORE: devi specificare un numero positivo di altezza" << endl;
                return;
            }
            if ( l <= 0 ) {
                cout << "ERRORE: devi specificare un numero positivo di larghezza" << endl;
                return;
            }
            altezza     += a;
            larghezza   += l;
        }

        double get_altezza() {
            return altezza;
        }

        double get_larghezza() {
            return larghezza;
        }
};


int main() {
    Pianta      felce( 5 );
    cout << "E` nata una felce con " << felce.get_foglie() << " foglie." << endl;
    felce.cresci( 10 );
    cout << "La felce e` cresciuta, adesso ha " << felce.get_foglie() << " foglie." << endl;
    pota( &felce, 6 );
    cout << "La felce e` stata potata, adesso ha " << felce.get_foglie() << " foglie." << "\n\n";

    Cespuglio   siepe( 120, 45.6, 62.85 );
    cout << "E` nata una siepe larga " << siepe.get_larghezza() << " cm, ";
    cout << "alta " << siepe.get_altezza() << " cm, ";
    cout << "e con " << siepe.get_foglie() << " foglie." << endl;       // chiama una funzione ereditata dalla classe genitore 'Pianta'
    siepe.cresci( 5, 10, 20 );
    cout << "La siepe e` cresciuta, adesso ha dimensione " << siepe.get_altezza() << " x " << siepe.get_larghezza() << " cm.\n\n";

    return 0;
}