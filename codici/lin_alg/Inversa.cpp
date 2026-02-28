/*

  File Inversa.ccp:

  inverte una matrice 3 x 3
  utilizzando la fattorizzazione LU

*/


#include <iostream>
using namespace std;


// Variabili globali del programma

const int dim = 3;


/*

  LU_fact( A ): effettua la fattorizzazione LU di una matrice A[dim][dim]

*/

void LU_fact( double A[dim][dim] )
{
  int i, j, k;
  double sum;

  for ( j = 1; j <= dim - 1; j++ ) A[0][j] = A[0][j] / A[0][0];

  for ( i = 1; i <= dim - 1; i++ )
    {

      for ( j = 1; j <= i; j++ )
	{
	  sum = 0.0;
	  for ( k = 0; k <= j - 1; k++ ) sum = sum + A[i][k] * A[k][j];
	  A[i][j] = A[i][j] - sum;
	}

      for ( j = i + 1; j <= dim - 1; j++ )
	{
	  sum = 0.0;
	  for ( k = 0; k <= i - 1; k++ ) sum = sum + A[i][k] * A[k][j];
	  A[i][j] = ( A[i][j] - sum ) / A[i][i];
	}

    }
}


/*

  LU_solve( A, b, x ): esegue l'inversione del sistema A*x=b

*/


void LU_solve( double A[dim][dim], double b[dim], double x[dim] )
{
  int i, j;
  double sum;
  double y[dim];    // Vettore temporaneo per la soluzione della Forward substitution


  // Forward substitution: Ly = b

  y[0] = b[0] / A[0][0];

  for ( i = 1; i <= dim - 1; i++ )
    {
      sum = 0.0;
      for ( j = 0; j <= i - 1; j++ ) sum = sum + A[i][j] * y[j];
      y[i] = ( b[i] - sum ) / A[i][i];
    }


  // Backward substitution: Ux = y

  x[dim-1] = y[dim-1];
  for ( i = dim - 2; i >= 0; i-- )
    {
      sum = 0.0;
      for ( j = i + 1; j <= dim - 1; j++ ) sum = sum + A[i][j] * x[j];
      x[i] = y[i] - sum;
      // Nota come u_ii = 1 nell'algoritmo di Crout!
    }
}


/*
  Funzione Prod_Mat_x_Mat( A, B, C ):
  Esegue il prodotto riga per colonna di una matrice A per una matrice B.
  Restituisce il risultato nella matrice C!
*/

void Prod_Mat_x_Mat( double A[dim][dim], double B[dim][dim], double C[dim][dim] )
{
  int i, j, k;
  double sum;

  for ( i = 0; i <= dim - 1; i++ )
    {
      for ( j = 0; j <= dim - 1; j++ )
	{
          sum = 0.0;
          for ( k = 0; k <= dim - 1; k++ ) sum = sum + A[i][k] * B[k][j];
	  C[i][j] = sum;
	}
    }
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
  stampa una matrice A[dim][dim] sullo schermo.
*/

void Stampa_matrice( double A[dim][dim] )
{
  int i, j;

  cout.precision( 15 );
  for ( i = 0; i <= dim - 1; i++ )
    {
      cout << "Mat-Lin-" << i + 1 << ">>>";
      for ( j = 0; j <= dim - 1; j++ )
	{
	  cout << "   " << A[i][j];
	}
      cout << endl;
    }
  cout << endl;
}


/*
  Main program
*/

main()
{
  cout << "Calcolo della soluzione di un sistema tramite fattorizzazione LU" << endl;

  int i,j;

  double A[dim][dim] = { { 3.0, 2.0, 1.0 },
			 { 4.0, 5.0, 2.0 },
			 { 1.0, 2.0, 3.0 } };


  // Poiche' la matrice A viene modificata dalla fattorizzazione, la copiamo in una matrice temporanea
  // che utilizzeremo poi per la verifica della soluzione

  double temp[dim][dim];
  for ( i = 0; i <= dim - 1; i++ )
    {
      for ( j = 0; j <= dim - 1; j++ )
	{
	  temp[i][j] = A[i][j];
	}
    }


  // Alloca la memoria per l'inversa della matrice

  double inv[dim][dim];


  // Stampa sullo schermo la matrice iniziale

  cout << "Matrice iniziale:" << endl;
  Stampa_matrice( A );


  // Esegue la fattorizzazione LU della matrice

  LU_fact( A );


  // Costruisce i secondi membri del sistema e il vettore soluzione per ogni colonna

  double x[dim];
  double b[dim];

  for ( j = 0; j <= dim - 1; j++ )
    {
      // Costruisce i secondi membri (j-esima colonna della matrice Identita'!)

      for ( i = 0; i <= dim - 1; i++ )
	{
	  b[i] = 0.0;
	  if ( j == i ) b[i] = 1.0;
	}

      // Risolve il j-esimo sistema Ax = b

      LU_solve( A, b, x );
 
      // Copia nella j-esima colonna della matrice inversa la soluzione del sistema

      for ( i = 0; i <= dim - 1; i++ ) inv[i][j] = x[i];
    }


  // Stampa della matrice inversa sullo schermo

  cout << "Matrice inversa: " << endl;
  Stampa_matrice( inv );


  // Verifica del risultato
  // Ricorda che la matrice iniziale A viene modificata da LU_fact( A ),
  // quindi utilizziamo la copia temporanea della matrice in temp!

  double P[dim][dim];

  cout << "Prodotto matrice per inversa:" << endl;
  Prod_Mat_x_Mat( temp, inv, P );
  Stampa_matrice( P );

  cout << "Prodotto inversa per matrice:" << endl;
  Prod_Mat_x_Mat( inv, temp, P );
  Stampa_matrice( P );
}
