/*
  Programma Bisezione.cpp:
  utilizza il metodo di bisezione per calcolare una approssimazione dello zero
  della funzione: exp( x ) - 1.5.
*/

#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;


// Funzione f(x) di cui trovare lo zero

double f( double x )
{
  double ff = exp( x ) - 1.5;
  return( ff );
}


// Main program

int main()
{
  cout << "Soluzione dell'equazione: exp(x)-1.5 = 0 col metodo di bisezione..." << endl;

  double a, b, ak, bk, xk, fa, fb, fx, largh, eps;
  int cont;

  // Parametri iniziali

  cout << "Inserire l\'estremo sinistro dell\'intervallo (a): ";
  cin >> a;
  cout << "Inserire l\'estremo destro dell\'intervallo (b): ";
  cin >> b;
  cout << "Tolleranza nel calcolo dello zero (eps): ";
  cin >> eps;

  // Check sull'intervallo iniziale

  if ( f( a ) * f( b ) > 0.0 )
    {
      cout << "Errore! L\'intervallo [" << a << "," << b << "] non contiene uno zero!" << endl;
      exit( 0 );
    }

  // Inizializzazione

  ak = a;
  bk = b;
  cont = 0;
  largh = abs( bk - ak );
  cout << "Iter." << "\t" << "a_k" << "\t" << "b_k" << "\t" << "x_k" << "\t" << "|b_k-a_k|" << endl;
  cout.precision(15);

  // Ciclo per la ricerca binaria

  do
    {
      xk = 0.5 * ( ak + bk );
      cout << cont << "\t" << ak << "\t" << bk << "\t" << xk << "\t" << largh << endl;
      fa = f( ak );
      fb = f( bk );
      fx = f( xk );
      if ( fx == 0.0 )
	{
	  cout << "Zero della funzione in: " << xk << "+- 0.0" << endl;
	  cout << "Numero di iterazioni: " << cont << endl;
	  exit( 0 );
	}
      else
	{
	  if ( fa * fx < 0.0 ) bk = xk;
	  if ( fx * fb  < 0.0 ) ak = xk;
	  largh = abs( bk -ak );
	  cont++;
	}
    }  while ( largh > eps );

  xk = 0.5 * ( ak + bk );
  cout << cont << "\t" << ak << "\t" << bk << "\t" << xk << "\t" << largh << endl;
  cout << "Zero della funzione in: " << xk << " +- " << 0.5 * largh << endl;
  cout << "Valore della funzione nello zero: " << f( xk ) << endl;
  cout << "Numero di iterazioni necessarie per il calcolo dello zero con la tolleranza voluta: " << cont << endl;
  cout << "Numero teorico di iterazioni richieste: " << (int)( log( ( b - a ) / eps ) / log( 2.0 ) ) << endl;
}
