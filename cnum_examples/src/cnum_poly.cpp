/* --------------------------------------------------------------------------------- *\
    CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)                  Alice Plebe
\* --------------------------------------------------------------------------------- */

#include "cnum.h"

using namespace std;
using namespace Eigen;

namespace cnum {

  /*-----------------------------------------------------------------------------------*\
      Costruttore con argomento solo ordine del polinomio
  \*-----------------------------------------------------------------------------------*/
  Poly::Poly( int order ) {
    this->resize(order);
    this->setZero();
    m_order = order;
  }

  /*-----------------------------------------------------------------------------------*\
      Costruttore con argomento il vettore dei coefficienti
  \*-----------------------------------------------------------------------------------*/
  Poly::Poly( dvec_t const & c ) {
    this->resize( c.size() );
    // per evitare la ricorsione devo chiamare esplicitamente
    // l'operatore = della classe di base.
    this->dvec_t::operator = (c);
    m_order = c.size();
  }

  /*-----------------------------------------------------------------------------------*\
      Valuta il polinomio, ovvero sostituisce alle variabili il valore in argomento 
  \*-----------------------------------------------------------------------------------*/
  Real
  Poly::eval( Real x ) const {
    Real x_pow = x;
    Real y	   = (*this)( 0 );
    for( Integer i=1; i < m_order; ++i ) {
      y     += (*this)( i ) * x_pow;
      x_pow *= x;
    }
    return y;
  }

  /*-----------------------------------------------------------------------------------*\
      Permette di stampare il polinomio su "cout" con l'operatore <<
  \*-----------------------------------------------------------------------------------*/
  ostream &
  operator<< ( ostream & output,  Poly const & p ) {
    bool   empty = true; // true indica che i coefficienti finora sono nulli
    string s     = "";   // segno
    double c     = 0;    // coefficiente
    string e     = "";   // esponente

    // controlla se esiste il primo coefficiente (grado 0)
    if ( p(0) != 0 ) {
      output << p(0);
      empty = false;
    }

    for ( Integer i=1; i < p.m_order; ++i ) {
      // se il coefficiente e` negativo...
      if ( p(i) < 0 ) {
        // e se i coefficienti precenti erano nulli...
        if ( empty ) {
          s     = ""; // ...non scrive il segno
          c     = p(i);
          empty = false;
        } else {
          s = " - "; // ...altrimenti scrive il segno come separatore
          c = -p(i); // e inverte il segno del coefficiente
        }

        // se il coefficiente e` positivo...
      } else if ( p(i) > 0 ) {
        c = p(i);
        // e se i coefficienti precenti erano nulli...
        if ( empty ) {
          s     = ""; // ...non scrive il segno
          empty = false;
        } else {
          s = " + "; // ...altrimenti scrive il segno come separatore
        }

        // se il coefficiente e` zero...
      } else {
        continue; // ...procede al prossimo
      }

      // se il grado e` 1 non scrive l'esponente
      if ( i == 1 ) e = "x";
      else          e = "x^" + to_string( i );
      output << s << c << e; // stampa
    }
    return output;
  }

  /*-----------------------------------------------------------------------------------*\
      Somma due polinomi di grado qualsiasi
  \*-----------------------------------------------------------------------------------*/
  Poly
  Poly::operator + ( Poly const & p ) const {
    Integer max_order, min_order;
    bool    p_has_max;

    if ( m_order > p.m_order ) {
      p_has_max = false;
      max_order	= m_order;
      min_order = p.m_order;
    } else {
      p_has_max	= true;
      max_order	= p.m_order;
      min_order	= m_order;
    }
    Poly sum( max_order ); // nuovo polinomio contenente la somma

    // somma i coefficieti fino al grado comune ad entrambi i polinomi
    for( Integer i=0; i < min_order; ++i )
      sum(i) = (*this)(i) + p(i);

    // per i gradi successivi controlla ogni volta
    if ( p_has_max ) {
      for( Integer i=min_order; i<max_order; ++i ) sum(i) = p(i);
    } else {
      for( Integer i=min_order; i<max_order; ++i ) sum(i) = (*this)(i);
    }
    return sum;
  }

  /*-----------------------------------------------------------------------------------*\
    Calcola il prodotto di due polinomi di grado qualsiasi
  \*-----------------------------------------------------------------------------------*/
  Poly
  Poly::operator * ( Poly const & p ) const {
    Poly prd( m_order + p.m_order - 1 ); // nuovo polinomio contenente il risultato
    for( Integer i=0; i<m_order; ++i )
      for( Integer j=0; j<p.m_order; ++j )
        prd(i+j) += (*this)(i) * p(j);
    return prd;
  }

  /*-----------------------------------------------------------------------------------*\
      Calcola la derivata del polinomio
  \*-----------------------------------------------------------------------------------*/
  Poly Poly::derivative() const {
    Poly der( m_order-1 ); // nuovo polinomio contenente il risultato
    for( int i=1; i<m_order; ++i )
      der(i-1) = i * (*this)(i);
    return der;
  }

  /*-----------------------------------------------------------------------------------*\
      Calcola l'integrale del polinomio
  \*-----------------------------------------------------------------------------------*/
  Poly
  Poly::integral() const {
    Poly itg( m_order+1 ); // nuovo polinomio contenente il risultato
    for ( int i=0; i < m_order; ++i )
      itg(i+1) = (*this)(i)/(i+1);
    return itg;
  }
}