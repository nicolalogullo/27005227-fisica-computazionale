/*

  File simpson.ccp:

  Calcola l'integrale di una funzione tramite la regola di Simpson

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

  Funzione int_simp:
  calcola l'integrale di una funzione nota su N+1 punti con la regola di Simpson.
  Nota che N DEVE essere un intero PARI e il vettore dei valori della funzione
  DEVE avere dimensione N+1!

*/

double int_simp( double f[], double h, long int N )
{
  double sump = 0.0, sumd = 0.0;

  for ( long int j = 2; j <= N - 2; j = j + 2 ) sump += f[j];
  for ( long int j = 1; j <= N - 1; j = j + 2 ) sumd += f[j];
  return( ( h / 3.0 ) * ( f[0] + f[N] + 2.0 * sump + 4.0 * sumd ) );
}


// Main program

main()
{
  cout << "Calcolo dell\'integrale definito di una funzione" << endl;

  double a, b;
  cout << "Estremi a, b dell\'intervallo: ";
  cin >> a >> b;

  long int N;
  cout << "Numero di intervalli su cui calcolare l\'integrale: ";
  cin >> N;
  if ( ( N % 2 ) != 0 )
    {
      cout << "Errore! In numero di intervalli DEVE essere PARI!" << endl;
      exit( 0 );
    }

  if ( Nmax < N )
    {
      cout << "Errore! Il valore di Nmax e' piu' piccolo del valore di N scelto!" << endl;
      cout << "Nmax = " << Nmax << endl;
      cout << "N = " << N << endl;
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

  double Inum = int_simp( f, h, N );
  double Iex  = Fint( a, b );


  // Stampa del risultato

  cout.precision(15);
  cout << "Risultato integrazione numerica: I_num = " << Inum << endl;
  cout << "Valore esatto dell\'integrale: I_ex = " << Iex << endl;
  cout << "Errore: | I_ex  - I_num | = " << abs( Iex - Inum ) << endl;
}
