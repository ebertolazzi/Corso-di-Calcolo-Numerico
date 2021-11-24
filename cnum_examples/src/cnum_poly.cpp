/* --------------------------------------------------------------------------------- *\
  CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22) Alice Plebe + Enrico Bertolazzi
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
      Costruisce il polinomio a 
  \*-----------------------------------------------------------------------------------*/
  Poly &
  Poly::set_scalar( Real a ) {
    this->resize(1);
    (*this)(0) = a;
    m_order    = 1;
    return *this;
  }

  /*-----------------------------------------------------------------------------------*\
      Costruisce il monomio x + a 
  \*-----------------------------------------------------------------------------------*/
  Poly &
  Poly::set_monomial( Real a ) {
    this->resize(2);
    (*this)(0) = a;
    (*this)(1) = 1;
    m_order    = 2;
    return *this;
  }

  /*-----------------------------------------------------------------------------------*\
      Valuta il polinomio, ovvero sostituisce alle variabili il valore in argomento 
  \*-----------------------------------------------------------------------------------*/
  Real
  Poly::eval( Real x ) const {
    // Calcolo il polinomio usando il metodo di Horner
    Integer n = m_order-1;
    Real res = (*this)(n);
    while ( n-- > 0 ) res = res*x+(*this)(n);
    return res;
  }

  /*-----------------------------------------------------------------------------------*\
      Permette di stampare il polinomio su "cout" con l'operatore <<
  \*-----------------------------------------------------------------------------------*/
  ostream &
  operator << ( ostream & output,  Poly const & p ) {
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

      // se il coeff è 1 non lo stampo
      if ( c == 1 ) output << s << e; // stampa
      else          output << s << c << e; // stampa
    }
    return output;
  }

  /*-----------------------------------------------------------------------------------*\
      Somma due polinomi di grado qualsiasi
  \*-----------------------------------------------------------------------------------*/
  Poly
  operator + ( Poly const & a, Poly const & b ) {
    Integer max_order = max( a.m_order, b.m_order );
    Integer min_order = min( a.m_order, b.m_order );
    Poly sum( max_order ); // nuovo polinomio contenente la somma

    // somma i coefficienti fino al grado comune ad entrambi i polinomi
    sum.head( min_order ).noalias() = a.head(min_order) + b.head(min_order);
    Integer n_tail = max_order - min_order;
    if ( n_tail > 0 ) {
      if ( a.m_order > b.m_order ) sum.tail( n_tail ).noalias() = a.tail(n_tail);
      else                         sum.tail( n_tail ).noalias() = b.tail(n_tail);
    }
    return sum;
  }

  Poly
  operator + ( Poly const & a, Real b ) {
    Integer max_order = max( a.m_order, 1 );
    Poly sum( max_order ); // nuovo polinomio contenente la somma

    // somma i coefficienti fino al grado comune ad entrambi i polinomi
    if ( a.m_order > 0 ) {
      sum(0) = a(0) + b;
      if ( a.m_order > 1 ) sum.tail( a.m_order-1 ).noalias() = a.tail(a.m_order-1);
    } else {
      sum(0) = b;
    }
    return sum;
  }

  Poly
  operator + ( Real a, Poly const & b ) {
    Integer max_order = max( b.m_order, 1 );
    Poly sum( max_order ); // nuovo polinomio contenente la somma

    // somma i coefficienti fino al grado comune ad entrambi i polinomi
    if ( b.m_order > 0 ) {
      sum(0) = a + b(0);
      if ( b.m_order > 1 ) sum.tail( b.m_order-1 ).noalias() = b.tail(b.m_order-1);
    } else {
      sum(0) = a;
    }
    return sum;
  }

  /*-----------------------------------------------------------------------------------*\
      Differenza tra due polinomi di grado qualsiasi
  \*-----------------------------------------------------------------------------------*/
  Poly
  operator - ( Poly const & a, Poly const & b ) {
    Integer max_order = max( a.m_order, b.m_order );
    Integer min_order = min( a.m_order, b.m_order );
    Poly sum( max_order ); // nuovo polinomio contenente la somma

    // somma i coefficienti fino al grado comune ad entrambi i polinomi
    sum.head( min_order ).noalias() = a.head(min_order) - b.head(min_order);
    Integer n_tail = max_order - min_order;
    if ( n_tail > 0 ) {
      if ( a.m_order > b.m_order ) sum.tail( n_tail ).noalias() = a.tail(n_tail);
      else                         sum.tail( n_tail ).noalias() = -b.tail(n_tail);
    }
    return sum;
  }

  Poly
  operator - ( Poly const & a, Real b ) {
    Integer max_order = max( a.m_order, 1 );
    Poly sum( max_order ); // nuovo polinomio contenente la somma

    // somma i coefficienti fino al grado comune ad entrambi i polinomi
    if ( a.m_order > 0 ) {
      sum(0) = a(0) - b;
      if ( a.m_order > 1 ) sum.tail( a.m_order-1 ).noalias() = a.tail(a.m_order-1);
    } else {
      sum(0) = -b;
    }
    return sum;
  }

  Poly
  operator - ( Real a, Poly const & b ) {
    Integer max_order = max( b.m_order, 1 );
    Poly sum( max_order ); // nuovo polinomio contenente la somma

    // somma i coefficienti fino al grado comune ad entrambi i polinomi
    if ( b.m_order > 0 ) {
      sum(0) = a - b(0);
      if ( b.m_order > 1 ) sum.tail( b.m_order-1 ).noalias() = -b.tail(b.m_order-1);
    } else {
      sum(0) = a;
    }
    return sum;
  }

  /*-----------------------------------------------------------------------------------*\
    Calcola il prodotto di due polinomi di grado qualsiasi
  \*-----------------------------------------------------------------------------------*/
  Poly
  operator * ( Poly const & a, Poly const & b ) {
    Poly prd( a.m_order + b.m_order - 1 ); // nuovo polinomio contenente il risultato
    for( Integer i=0; i<a.m_order; ++i )
      for( Integer j=0; j<b.m_order; ++j )
        prd(i+j) += a(i) * b(j);
    return prd;
  }

  Poly
  operator * ( Real a, Poly const & b ) {
    Poly prd( b.m_order ); // nuovo polinomio contenente il risultato
    prd.noalias() = a*b.to_eigen();
    return prd;
  }

  Poly
  operator * ( Poly const & a, Real b ) {
    Poly prd( a.m_order ); // nuovo polinomio contenente il risultato
    prd.noalias() = a.to_eigen()*b;
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

  /*-----------------------------------------------------------------------------------*\
      Somma un polinomio
  \*-----------------------------------------------------------------------------------*/
  Poly &
  Poly::operator += ( Poly const & b ) {
    Integer max_order = max( m_order, b.m_order );
    Integer min_order = min( m_order, b.m_order );

    // ridimensiona vettore coefficienti senza distruggere il contenuto
    this->conservativeResize( max_order );

    // somma i coefficienti fino al grado comune ad entrambi i polinomi
    this->head( min_order ).noalias() += b.head(min_order);
    Integer n_tail = b.m_order - m_order;
    if ( n_tail > 0 ) this->tail( n_tail ).noalias() = b.tail(n_tail);
    m_order = max_order;
    return *this;
  }

  Poly &
  Poly::operator += ( Real b ) {
    if ( m_order > 0 ) (*this)(0) += b;
    else {
      this->resize(1);
      (*this)(0) = b;
      m_order = 1;
    }
    return *this;
  }

  /*-----------------------------------------------------------------------------------*\
      Differenza due polinomi di grado qualsiasi
  \*-----------------------------------------------------------------------------------*/
  Poly &
  Poly::operator -= ( Poly const & b ) {
    Integer max_order = max( m_order, b.m_order );
    Integer min_order = min( m_order, b.m_order );

    // ridimensiona vettore coefficienti senza distruggere il contenuto
    this->conservativeResize( max_order );

    // somma i coefficienti fino al grado comune ad entrambi i polinomi
    this->head( min_order ).noalias() -= b.head(min_order);
    Integer n_tail = b.m_order - m_order;
    if ( n_tail > 0 ) this->tail( n_tail ).noalias() = -b.tail(n_tail);
    m_order = max_order;
    return *this;
  }

  Poly &
  Poly::operator -= ( Real b ) {
    if ( m_order > 0 ) (*this)(0) -= b;
    else {
      this->resize(1);
      (*this)(0) = -b;
      m_order = 1;
    }
    return *this;
  }

  /*-----------------------------------------------------------------------------------*\
    Calcola il prodotto di due polinomi di grado qualsiasi
  \*-----------------------------------------------------------------------------------*/
  Poly &
  Poly::operator *= ( Poly const & b ) {
    dvec_t a(this->to_eigen()); // fa una copia dei coefficienti del vettore
    Integer new_order = m_order + b.m_order - 1;
    this->resize( m_order + b.m_order - 1 ); // nuovo polinomio contenente il risultato
    this->setZero();
    for( Integer i=0; i<m_order; ++i )
      for( Integer j=0; j<b.m_order; ++j )
        (*this)(i+j) += a(i) * b(j);
    m_order = new_order;
    return *this;
  }

  Poly &
  Poly::operator *= ( Real b ) {
    this->to_eigen() *= b;
    return *this;
  }
}
