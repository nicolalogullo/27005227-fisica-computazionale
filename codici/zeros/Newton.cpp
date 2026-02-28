/*
  Programma Newton.cpp:
  utilizza il metodo di Newton per calcolare lo zero della funzione:
  f( x ) = exp( x ) - 1.5.
*/

#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;


// Funzione f(x) di cui trovare lo zero e sua derivata

/*
double f( double x )
{
  double ff = exp( x ) - 1.5;
  return( ff );
}
*/

double f( double x )
{
  double pi = acos( -1.0 );
  double ff = x / ( 1.5 + sin( pi * x ) ) - 0.5;
  return( ff );
}

/*
double fp( double x )
{
  double ff = exp( x );
  return( ff );
}
*/

double fp( double x )
{
  double pi = acos( -1.0 );
  double ff = ( ( 1.5 + sin( pi * x ) ) - pi * x * cos( pi * x ) ) /
    ( ( 1.5 + sin( pi * x ) ) * ( 1.5 + sin( pi * x ) ) );
  return( ff );
}


// Main program

int main()
{
  cout << "Soluzione dell'equazione: exp(x)-1.5 = 0 col metodo di Newton..." << endl;

  double a, b, x0, eps, xk, xkp1, largh, xz;
  int cont, num_max_iter;

  // Parametri iniziali

  cout << "Inserire l\'estremo sinistro dell\'intervallo (a): ";
  cin >> a;
  cout << "Inserire l\'estremo destro dell\'intervallo (b): ";
  cin >> b;
  cout << "Stima iniziale dello zero x0: ";
  cin >> x0;
  cout << "Numero massimo di iterazioni: ";
  cin >> num_max_iter;
  cout << "Tolleranza nel calcolo dello zero (eps): ";
  cin >> eps;

  // Check sull'intervallo iniziale

  if ( f( a ) * f( b ) > 0.0 )
    {
      cout << "Errore! L\'intervallo [" << a << "," << b << "] non contiene uno zero!" << endl;
      exit( 0 );
    }

  // Inizializzazione

  cont = 0;
  xk = x0;
  cout << "Iter." << "\t" << "x_k" << "\t" << "|x_k+1 - x_k|" << endl;
  cout.precision(15);

  // Ciclo per la ricerca col metodo di Newton

  do
    {
      cont++;
      xkp1 = xk - f( xk ) / fp( xk );
      largh = abs( xkp1 - xk );
      xk = xkp1;
      cout << cont << "\t" << xk << "\t" << largh << endl;
    } while ( ( largh > eps ) && ( cont < num_max_iter ) );

  if ( cont < num_max_iter )
    {
      xz = xk;
      cout << "Zero della funzione in: " << xz << " +- " << 0.5 * largh << endl;
      cout << "Valore della funzione nello zero: " << f( xz ) << endl;
      cout << "Numero di iterazioni necessarie per il calcolo dello zero con la tolleranza voluta: " << cont << endl;
    }
  else
    {
      cout << "La successione di valori NON e' arrivata a convergenza entro ";
      cout << num_max_iter << " iterazioni!" << endl;
      cout << "Prova ad aumentare il numero massimo di iterazioni o a scegliere un x0 differente!" << endl;
    }
}
