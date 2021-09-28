/* --------------------------------------------------------------------------------- *\
    CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)                  Alice Plebe

    Overloading di operatori
\* --------------------------------------------------------------------------------- */

#include <iostream>
using namespace std;


class SafeWallet {           // (stessa classe vista in 'code_04.cpp')
    private:
        double  money;                  

    public:
        SafeWallet( double m ) {
            money   = m;
        }

        double get_money() {
            return money;
        }

        void earn( double m ) {
            if ( m < 0 ) {
                cout << "ATTENTIONE! Non puoi guadagnare una quantita` negativa" << endl;
                return;
            }
            money   += m;
        }

        void spend( double m ) {
            if ( m > money ) {
                cout << "ATTENTIONE! Non hai abbastanza denare da spendere" << endl;
                return;
            }
            money   -= m;
        }

        // ridefinisce l'operatore somma (+) tra due oggetti 'SafeWallet'
        SafeWallet operator + ( SafeWallet &wal1 ) {        // parametro passato per riferimento
            // sommare due 'SafeWallet' crea un nuovo 'SafeWallet' dove 'money' equivale alla somma dei due
            double tot  = money + wal1.get_money();
            SafeWallet wal2( tot );
            return wal2;    // restituisce il nuovo oggetto
        }

        // ridefinisce l'operatore prefisso di decremento (--val) di un oggetto 'SafeWallet'
        void operator -- () {
            // decrementare un 'SafeWallet' equivale a svuotare il portafoglio
            money   = 0.0;
        }

        // ridefinisce l'operatore postfisso di decremento (val--) di un oggetto 'SafeWallet'
        void operator -- ( int ) {
            // decrementare un 'SafeWallet' equivale a svuotare il portafoglio
            money   = 0.0;
        }
};


int main() {
    SafeWallet  sw_alice( 1098.35 );
    SafeWallet  sw_elisa( 416.90 );
    cout << "Alice possiede " << sw_alice.get_money() << " euro" << endl;
    cout << "Elisa possiede " << sw_elisa.get_money() << " euro" << endl;

    // adesso si puo` usare il simbolo '+' per sommare due oggetti 'SafeWallet'
    SafeWallet  sw_joined   = sw_alice + sw_elisa;
    cout << "Insieme possiedono " << sw_joined.get_money() << " euro" << endl;

    // questo causa un errore poiche` e` stato ridefinito solo l'operatore '+' e non '-'
    /*
    SafeWallet  s   = sw_alice - sw_elisa;
    */

    // adesso decrementare un 'SafeWallet' equivale a svuotarlo
    sw_alice--;         // vale anche scrivere --sw_alice;
    cout << "Alice adesso possiede " << sw_alice.get_money() << " euro" << endl;

    return 0;
}