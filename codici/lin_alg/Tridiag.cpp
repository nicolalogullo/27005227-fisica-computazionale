/*

  File Tridiag.ccp:

  inverte un sistema 3 x 3 di un problema tridiagonale
  utilizzando l'algoritmo di Thomas per la fattorizzazione LU

*/

#include <iostream>
using namespace std;


// Variabili globali del programma

const int dim = 3;


/*

  LU_fact( A ): effettua la fattorizzazione LU di una matrice tridiagonale A[3][dim]
  secondo l'algoritmo di Thomas

*/


void LU_fact( double A[3][dim] )
{
  int i;

  for ( i = 1; i <= dim - 1; i++ )
    {
      A[0][i] = A[0][i] / A[1][i-1];
      A[1][i] = A[1][i] - A[0][i] * A[2][i-1];
    }
}


/*

  LU_solve( A, f, x ): esegue l'inversione di un sistema A*x=f
  secondo l'algoritmo di Thomas.

*/

void LU_solve( double A[3][dim], double f[dim], double x[dim] )
{
  double y[dim];
  int i;

  // Forward substitution per sistema: Ly = f

  y[0] = f[0];
  for ( i = 1; i <= dim - 1; i++ )
    y[i] = f[i] - A[0][i] * y[i-1];

  // Backward substitution per sistema: Ux = y

  x[dim-1] = y[dim-1] / A[1][dim-1];
  for ( i = dim - 2; i >= 0; i-- ) 
    x[i] = ( y[i] - A[2][i] * x[i+1] ) / A[1][i];
}


/*
  Funzione Prod_Mat_x_Vett( A, x, f ):
  esegue il prodotto riga per colonna di una matrice tridiagonale A[3][dim],
  memorizzata per diagonali, con un vettore x[dim]. Il risultato e' fornito
  in uscita nel vettore f[dim]!
*/

void Prod_Mat_x_Vett( double A[3][dim], double x[dim], double f[dim] )
{
  int i;

  f[0] = A[1][0] * x[0] + A[2][0] * x[1];
  for ( i = 1; i <= dim - 2; i++ )
    f[i] = A[0][i] * x[i-1] + A[1][i] * x[i] + A[2][i] * x[i+1];
  f[dim-1] = A[0][dim-1] * x[dim-2] + A[1][dim-1] * x[dim-1];
}


/*
  Funzione Stampa_vettore( v ):
  stampa un vettore v[dim] sullo schermo.
*/

void Stampa_vettore( double v[dim] )
{
  int j;

  cout.precision( 15 );
  for ( j = 0; j <= dim - 1; j++ )
    {
      cout << "Vett-Elem-" << j + 1 << ">   " << v[j] << endl;
    }
  cout << endl;
}


/*
  Funzione Stampa_matrice( A ):
  stampa una matrice tridiagonale A[3][dim] sullo schermo, nel formato classico
  per righe e colonne.
*/

void Stampa_matrice( double A[3][dim] )
{
  int i, j;

  cout.precision( 15 );

  // Stampa prima riga della matrice tridiagonale

  cout << "Mat-Lin-" << 1 << ">>>";
  cout << "   " << A[1][0] << "   " << A[2][0];
  for ( i = 3; i <= dim; i++ )
    {
      cout << "   " << 0.0;
    }
  cout << endl;


  // Stampa righe centrali della matrice tridiagonale

  for ( j = 1; j <= dim - 2; j++ )
    {
      cout << "Mat-Lin-" << j + 1 << ">>>";
      for ( i = 0; i <= j - 2; i++ )
	{
	  cout << "   " << 0.0;
	}
      for ( i = 0; i <= 2; i++ )
	{
	  cout << "   " << A[i][j];
	}
      for ( i = j + 2; i <= dim - 1; i++ )
	{
	  cout << "   " << 0.0;
	}
      cout << endl;
    }


  // Stampa ultima riga della matrice tridiagonale

  cout << "Mat-Lin-" << dim << ">>>";
  for ( i = 0; i <= dim - 3; i++ )
    {
      cout << "   " << 0.0;
    }
  cout << "   " << A[0][dim-1] << "   " << A[1][dim-1];
  cout << endl;

  cout << endl;
}


/*
  Main program
*/

main()
{
  cout << "Calcolo della soluzione di un sistema tridiagonale tramite fattorizzazione LU" << endl;

  // Definizione della matrice A, memorizzata per diagonali

  int i, j;
  double A[3][dim] = { { 0.0, 2.0, 1.0 },
		       { 4.0, 5.0, 2.0 },
		       { 1.0, 2.0, 0.0 } };

  /*
    La matrice originale, memorizzata per righe e colonne e':

    +-                  -+
    |  4.0    1.0   0.0  |
    |                    |
    |  2.0    5.0   2.0  |
    |                    |
    |  0.0    1.0   2.0  |
    +-                  -+
  */

  // Poiche' la matrice iniziale viene modificata da LU_fact, ne salviamo una copia
  // nella matrice temporanea temp[dim][dim], per verifiche successive!

  double temp[3][dim];
  for ( i = 0; i <= 2; i++ )
    {
      for ( j = 0; j <= dim - 1; j++ )
	{
	  temp[i][j] = A[i][j];
	}
    }


  // Stampa sullo schermo la matrice iniziale (per righe e colonne!)

  cout << "Matrice iniziale:" << endl;
  Stampa_matrice( A );


  // Fattorizzazione LU della matrice A

  LU_fact( A );


  // Stampa sullo schermo la matrice fattorizzata LU

  cout << "Matrice fattorizzata LU:" << endl;
  Stampa_matrice( A );


  // Costruisce i secondi membri del sistema

  double x[dim];
  double b[dim];

  for ( j = 0; j <= dim - 1; j++ )
    {
      b[j] = j * 1.0;
    }


  // Stampa sullo schermo il vettore del secondo membro

  cout << "Vettore del secondo membro:" << endl;
  Stampa_vettore( b );


  // Inverte il sistema fattorizzato LU

  LU_solve( A, b, x );


  // Stampa del risultato

  cout << "Vettore soluzione:" << endl;
  Stampa_vettore( x );


  // Verifica della soluzione

  double F[dim];
  Prod_Mat_x_Vett( temp, x, F );
  cout << "Prodotto matrice A per vettore soluzione:" << endl;
  Stampa_vettore( F );
}
