/*

  File Trapezi.ccp:

  Calcola l'integrale di una funzione nota:

  f(x) = exp(x)

  nell'intervallo: [a, b] tramite la regola dei trapezi

*/


#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;


// Numero massimo di sottointervalli in [a,b]

const long int Nmax = 1000000;


// Funzione da integrare

double F( double x )
{
  double ff = exp( x );
  return( ff );
}


// Integrale esatto

double Fint( double a, double b )
{
  double ff = exp( b ) - exp( a );
  return( ff );
}


/*

  Funzione int_trap
  calcola l'integrale di una funzione nota su N+1 punti
  con la regola dei trapezi.
  Nota che il vettore contenente i valori da integrare ha dimensione: f[N+1]!

*/

double int_trap( double f[], double h, long int N )
{
  double sum;

  sum = 0.5 * ( f[0] + f[N] );
  for ( long int i = 1; i < N; i++ ) sum += f[i];
  return( h * sum );
}


// Main program

main()
{
  cout << "Calcolo dell\'integrale definito di una funzione." << endl;

  double a, b;
  cout << "Estremi a, b dell\'intervallo: ";
  cin >> a >> b;

  long int N;
  cout << "Numero di intervalli su cui calcolare l\'integrale: ";
  cin >> N;

  if ( Nmax < N )
    {
      cout << "Errore! Il valore di Nmax e' piu' piccolo del valore di N scelto!";
      cout << "Nmax = " << Nmax;
      cout << "N = " << N;
      exit( 0 );
    }


  // Definisce la funzione sui punti nodali

  double xj;
  double f[Nmax+1];
  double h = ( b - a ) / N;

  for ( long int j = 0; j <= N; j++ )
    {
      xj   = a + j * h;
      f[j] = F( xj );
    }


  // Calcolo dell'integrale definito

  double Inum = int_trap( f, h, N );
  double Iex  = Fint( a, b );


  // Stampa del risultato

  cout.precision( 15 );
  cout << "Risultato integrazione numerica: I_num = " << Inum << endl;
  cout << "Valore esatto dell\'integrale: I_ex = " << Iex << endl;
  cout << "Errore: | I_ex  - I_num | = " << abs( Iex - Inum ) << endl;
}
