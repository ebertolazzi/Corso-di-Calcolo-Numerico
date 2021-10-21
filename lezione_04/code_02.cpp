/* --------------------------------------------------------------------------------- *\
    CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)                  Alice Plebe

    Ereditarieta` -- controllo accessibilita`
\* --------------------------------------------------------------------------------- */

#include <iostream>
using namespace std;

class Base {
    private:    // non e` accessibile da nessuna classe al di fuori di 'Base'
        int v_priv  = 1;

    protected:  // non e` accessibile al di fuori di 'Base' e delle classi che la ereditano
        int v_prot  = 2;

    public:     // sono accessibili
        int v_publ  = 3;
        
        int get_priv() {
            return v_priv;
        }
};

// classe che eredita 'Base' in modo public, ovvero:
//      v_priv non e` accessibile
//      v_prot resta protected
//      v_publ e get_priv() restano public
class PublDerived : public Base {
    public:
        int get_prot() {
            return v_prot;
        }
};

// classe che eredita 'Base' in modo protected, ovvero:
//      v_priv non e` accessibile
//      v_prot resta protected
//      v_publ e get_priv() diventano protected
class ProtDerived : protected Base {
    public:
        int get_prot() {
            return v_prot;
        }

        int get_publ() {
            return v_publ;
        }
};

// classe che eredita 'Base' in modo private, ovvero:
//      v_priv non e` accessibile
//      v_prot diventa private
//      v_publ e get_priv() diventano private
class PrivDerived : private Base {
    public:
        int get_prot() {
            return v_prot;
        }

        int get_publ() {
            return v_publ;
        }
};


int main() {
    Base    o_base;
    cout << o_base.v_publ << endl;          // OK
    // cout << o_base.v_prot << endl;       // NOT OK
    // cout << o_base.v_priv << endl;       // NOT OK
    cout << o_base.get_priv() << endl;      // OK

    PublDerived     od_publ;
    cout << od_publ.v_publ << endl;         // OK
    // cout << od_publ.v_prot << endl;      // NOT OK
    // cout << od_publ.v_priv << endl;      // NOT OK
    cout << od_publ.get_prot() << endl;     // OK
    cout << od_publ.get_priv() << endl;     // OK

    ProtDerived     od_prot;
    // cout << od_prot.v_publ << endl;      // NOT OK
    // cout << od_prot.v_prot << endl;      // NOT OK
    // cout << od_prot.v_priv << endl;      // NOT OK
    cout << od_prot.get_publ() << endl;     // OK
    cout << od_prot.get_prot() << endl;     // OK
    // cout << od_prot.get_priv() << endl;  // NOT OK

    PrivDerived     od_priv;
    // cout << od_priv.v_publ << endl;      // NOT OK
    // cout << od_priv.v_prot << endl;      // NOT OK
    // cout << od_priv.v_priv << endl;      // NOT OK
    cout << od_priv.get_publ() << endl;     // OK
    cout << od_priv.get_prot() << endl;     // OK
    // cout << od_priv.get_priv() << endl;  // NOT OK

    return 0;
}