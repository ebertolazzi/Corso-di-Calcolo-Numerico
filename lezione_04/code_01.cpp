/* --------------------------------------------------------------------------------- *\
    CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)                  Alice Plebe

    Ereditarieta` multipla
\* --------------------------------------------------------------------------------- */

#include <iostream>
using namespace std;

const int   MAX_FIORI   = 1000;     // numero massimo di fiori su una pianta

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


// un'altra sottoclasse di 'Pianta'
class Albero : public Pianta {
    private:
        int     num_rami;               // numero di rami

    // queste variabili sono 'protected', ovvero accessibili anche alle classi che ereditano 'Albero'
    protected:
        int     num_fiori;              // numero di fiori
        int     fiori[ MAX_FIORI ];     // array per indicare quali fiori sono sbocciati (0=fiore chiuso, 1=fiore sbocciato)

    public:
        // chiama il costruttore di 'Pianta' per inizializzare le foglie
        Albero( int f, int r, int n ) : Pianta( f ) {
            num_rami            = r;

            // controlla che il numero di fiori non superi il massimo valore allocato in memoria
            if ( n > MAX_FIORI ) {
                cout << "ERRORE: superato il massimo numero di fiori possibile" << endl;
                num_fiori       = MAX_FIORI;
            }
            else {
                num_fiori       = n;
            }

            // inizializza tutti i fiori a 0 (ovvero non sbocciati)
            for ( int i = 0; i < num_fiori; ++i ) {
                fiori[ i ]      = 0;
            }
        }

        // fa crescere l'albero aumentando le foglie e i rami
        void cresci( int f, int r ) {
            Pianta::cresci( f );
            if ( r <= 0 ) {
                cout << "ERRORE: devi specificare un numero positivo di rami" << endl;
                return;
            }
            num_rami    += r;
        }

        // fa sbocciare alcuni dei fiori in modo casuale, con la probabilita` passata in argomento
        void sboccia( double thresh = 0.5 ) {
            double  n;
            for ( int i = 0; i < num_fiori; ++i ) {
                n   = ( double ) rand() / RAND_MAX;     // genera un numero random tra 0 e 1
                if ( n < thresh ) {
                    fiori[ i ]  = 1;        // fa sbocciare l'i-esimo fiore con probabilita` 'thresh'
                }
            }
        }

        int get_rami() {
            return num_rami;
        }

        int get_fiori() {
            return num_fiori;
        }

        // restituisce quanti fiori sono sbocciati (ovvero quanti hanno valore = 1)
        int get_fiori_sbocciati() {
            int cnt     = 0;
            for ( int i = 0; i < num_fiori; ++i ) {
                if ( fiori[ i ] == 1 ) {
                    ++cnt;
                }
            }
            return cnt;
        }
};


// sottoclasse di 'Albero' (nonche` di 'Pianta')
class AlberoFrutto : public Albero {
    private:
        int     num_frutti;             // numero di frutti

    public:
        // chiama il costruttore di 'Albero', che a sua volta richiama il costruttore di 'Pianta'
        AlberoFrutto( int f, int r, int n ) : Albero( f, r, n ) {
            num_frutti  = 0;
        }

        // produce tanti frutti quanti fiori risultano sbocciati
        void matura_frutti() {
            int n   = get_fiori_sbocciati();    // chiama la funzione get_fiori_sbocciati() che ha ereditato da 'Albero'
            if ( n == 0 ) {
                cout << "Per maturare frutti, devono prima sbocciare dei fiori!" << endl;
                return;
            }
            num_frutti  += n;
        }

        // restituisce il numero di frutti prodotti, e li rimuove dall'albero insieme ai fiori sbocciati
        int raccogli_frutti() {
            int     n   = num_frutti;
            num_frutti  = 0;
            // e` possibile accedere alle variabili 'num_fiori' e 'fiori[]' poiche`
            // erano state definite come 'static' all'interno della classe 'Albero'
            for ( int i = 0; i < num_fiori; ++i ) {
                fiori[ i ]  = 0;        // riporta tutti i fiori come non sbocciati
            }
            return n;
        }
};


// classe che eredita contemporaneamente 'Cespuglio' e 'Albero' (quindi anche 'Pianta')
class Bonsai : public Cespuglio, public Albero {
    public:
        // richiama entrambi i costruttori delle classi genitori
        Bonsai( int f, double a, double l, int r, int n ) : Cespuglio( f, a, l ), Albero( f, r, n ) {}
};


int main() {
    srand( 1 );     // fissa il seed del generatore di numeri random

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

    Albero      magnolia( 1040, 46, 520 );
    cout << "E` nata una magnolia con " << magnolia.get_rami() << " rami ";
    cout << "e " << magnolia.get_fiori() << " fiori." << endl;
    magnolia.sboccia();
    cout << "Sulla magnolia sono sbocciati " << magnolia.get_fiori_sbocciati() << " fiori.\n\n";

    Bonsai      ginepro_cinese( 68, 25.3, 18.4, 20, 6 );
    cout << "E` nato un ginepro cinese di dimensione " << ginepro_cinese.get_altezza(); // chiama sia funzioni della classe 'Cespiglio'...
    cout << " x " << ginepro_cinese.get_larghezza() << " cm,";
    cout << " con " << ginepro_cinese.get_fiori() << " fiori.\n\n";                     // ...che funzioni della classe 'Albero'

    int             n_mele;
    AlberoFrutto    melo( 600, 30, 50 );
    cout << "E` nato un albero di mele" << endl;
    melo.sboccia( 0.35 );                                                               // chiama una funzione ereditata da 'Albero'
    melo.matura_frutti();
    n_mele  = melo.raccogli_frutti();
    cout << "L'albero di mele ha prodotto " << n_mele << " mele." << endl;

    return 0;
}