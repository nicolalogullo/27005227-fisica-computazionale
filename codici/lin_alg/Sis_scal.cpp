/*

  File Sis_scal.ccp:

  Per vedere se il numero di operazioni e' proporzionale ad n^3
  risolve un generico sistema di dimensione n utilizzando la fattorizzazione LU
  La matrice viene costruita come:
  a_ij = 1                 se i  = j;
  a_ij = 1.0/(1.0+i+j)     se i /= j

  Per testare il tempo di esecuzione del codice, commentare le stampe!

*/


#include <iostream>
using namespace std;


// Variabili globali del programma

const int dim = 100;


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
  Funzione Prod_Mat_x_Vett( A, x, b ):
  Esegue il prodotto riga per colonna di una matrice A per un vettore x.
  Restituisce il risultato nel vettore b!
*/

void Prod_Mat_x_Vett( double A[dim][dim], double x[dim], double b[dim] )
{
  int i, j;
  double sum;

  for ( i = 0; i <= dim - 1; i++ )
    {
      sum = 0.0;
      for ( j = 0; j <= dim - 1; j++ )
	{
	  sum = sum + A[i][j] * x[j];
	}
      b[i] = sum;
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
  cout << "Calcolo della soluzione di un sistema nxn tramite fattorizzazione LU" << endl;


  // Definizione della matrice A

  int i, j;
  double A[dim][dim];
  for ( i = 0; i <= dim - 1; i++ )
    for ( j = 0; j <= dim - 1; j++ )
      {
	if ( i == j )
	  A[i][j] = 1.0;
	else
	  A[i][j]  = 1.0 / ( 1.0 + (i+1) + (j+1) );
      }



  // Poiche' la matrice A viene modificata dalla fattorizzazione, la copiamo in una matrice temporanea
  // che utilizzeremo poi per la verifica della soluzione

  /*
  double temp[dim][dim];
  for ( i = 0; i <= dim - 1; i++ )
    {
      for ( j = 0; j <= dim - 1; j++ )
  	{
  	  temp[i][j] = A[i][j];
  	}
    }
  */


  // Stampa sullo schermo la matrice iniziale

  //cout << "Matrice iniziale: " << endl;
  //Stampa_matrice( A );


  // Esegue la fattorizzazione LU della matrice

  LU_fact( A );


  // Stampa della matrice fattorizzata LU

  //cout << "Matrice fattorizzata LU: " << endl;
  //Stampa_matrice( A );


  // Costruisce i secondi membri del sistema

  double x[dim];
  double b[dim];

  for ( j = 0; j <= dim - 1; j++ )
    {
      b[j] = j * 1.0;
    }


  // Stampa sullo schermo il vettore del secondo membro

  //cout << "Vettore del secondo membro:" << endl;
  //Stampa_vettore( b );


  // Inverte il sistema fattorizzato LU

  LU_solve( A, b, x );


  // Stampa del vettore soluzione

  //cout << "Stampa del risultato." << endl;
  //cout << "Vettore soluzione:" << endl;
  //Stampa_vettore( x );


  // Verifica del risultato

  /*
  cout << "Verifica del risultato." << endl;
  cout << "Prodotto matrice per vettore soluzione:" << endl;

  double bb[dim];
  Prod_Mat_x_Vett( temp, x, bb );
  Stampa_vettore( bb );
  */
}
