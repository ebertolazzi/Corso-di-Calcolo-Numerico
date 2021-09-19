/* --------------------------------------------------------------------------------- *\
    CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)                  Alice Plebe

    Scope e lifetime di variabili
\* --------------------------------------------------------------------------------- */

#include <iostream>
using namespace std;


// variabile globale
// scope    = intero programma
// lifetime = termine del programma
int     var_g   = 83;

void func1() {
    // variabile locale
    // scope    = interno della funzione func1()
    // lifetime = termine della funzione func1()
    int     var_l   = 903;
    ++var_l;
    cout << var_l << endl;
}

void func2() {
    // variabile statica locale
    // scope    = interno della funzione func2()
    // lifetime = termine del programma
    static int  var_s   = 402;
    ++var_s;
    cout << var_s << endl;
}

int main() {
    // 'var_l' viene creata e distrutta ad ogni chiamata di func1()...
    func1();
    func1();
    // ...quindi viene sempre stampato 904

    // 'var_s' non viene distrutta dopo la prima chiamata di func2()...
    func2();
    func2();
    // ...quindi alla seconda chiamata viene stampato 404

    return 0;
}