/* --------------------------------------------------------------------------------- *\
    CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)                  Alice Plebe

    Classe per rappresentare un poligono
\* --------------------------------------------------------------------------------- */

#pragma once
#include <iostream>
#include <Eigen/Dense>

class Poly : public Eigen::VectorXd {
	private:
		Eigen::VectorXd     v;              // vettore dei coefficienti
		int		            deg;            // grado del polinomio
                                            // (o meglio, la lunghezza del vettore v)

	public:
        // costruttori
		Poly( int );
		Poly( const Eigen::VectorXd );

        // funzioni di supporto
		Eigen::VectorXd get_coef() { return v; }
		int get_deg() { return deg-1; }

        // stampa il polinomio
		friend std::ostream &operator<<( std::ostream&, const Poly& );

		double eval( float );               // valuta il polinomio
        Poly operator+( const Poly& );      // operazione somma
        Poly operator*( const Poly& );      // operazione prodotto
		Poly derivative();                  // operazione derivata
		Poly integral();                    // operazione integrale
};