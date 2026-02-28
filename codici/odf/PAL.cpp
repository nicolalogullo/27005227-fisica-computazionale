/*

  File PAL.ccp:
  Risolve l'equazione:

     d^2 Y / dx^2 + f(x) * d Y/dx + g(x) * Y = h(x)

*/


#include <iostream>
#include <fstream>
using namespace std;


// Variabili globali del programma

const int N = 1001;               // Numero di punti griglia, inclusi i bordi


/*

  Le seguenti variabili identificano alcune caratteristiche del
  problema che dipendono delle condizioni al bordo, come la dimensione
  effettiva del problema (dimensione della matrice da invertire),
  l'indice del punto iniziale e finale (j_init, j_end) e le quantita'
  Ya, Yb, Ypa, Ypb che identificano i valori delle condizioni al
  bordo.

  La variabile bct identifica la combinazione di condizioni al bordo note:
     bct = 1 => sono noti sia Y(a) che Y(b);
     bct = 2 => sono noti Y(a) e Y'(b);
     bct = 3 => sono noti Y'(a) e Y(b);
     bct = 4 => sono noti Y'(a) e Y'(b).

  Scommentare di volta in volta la parte di codice interessa, a seconda
  della condizione al bordo scelta!

*/

// Y(a) e Y(b) noti:
/*
  int bct = 1;
  const int dim = N - 2;
  int j_init = 1, j_end = N - 2;
  double Ya  = 0.0;
  double Yb  = 0.0;
  double Ypa = 0.0;   // Nota come Ypa e Ypb debbono comunque essere definiti
  double Ypb = 0.0;   // per evitare errori di compilazione!
*/

// Y(a) e Y'(b) noti
/*
  int bct = 2;
  const int dim = N - 1;
  int j_init = 1, j_end = N - 1;
  double Ya  = 0.0;
  double Ypb = 0.0;
  double Yb  = 0.0;   // Nota come Ypa e Yb debbono comunque essere definiti
  double Ypa = 0.0;   // per evitare errori di compilazione!
*/

// Y'(a) e Y(b) noti
/*
  int bct = 3;
  const int dim = N - 1;
  int j_init = 0, j_end = N - 2;
  double Ypa = 0.0;
  double Yb  = 0.0;
  double Ya  = 0.0;   // Nota come Ya e Ypb debbono comunque essere definiti
  double Ypb = 0.0;   // per evitare errori di compilazione!
*/

// Y'(a) e Y'(b) noti
/*
  int bct = 4;
  const int dim = N;
  int j_init = 0, j_end = N - 1;
  double Ypa = 0.0;
  double Ypb = 0.0;
  double Ya  = 0.0;   // Nota come Ya e Yb debbono comunque essere definiti
  double Yb  = 0.0;   // per evitare errori di compilazione!
*/


// Funzioni che definiscono l'equazione

double f( double x )
{
  return( 0.0 );
}


double g( double x )
{
  return( 0.0 );
}


double h( double x )
{
  return( 0.0 );
}


/*

  LU_fact( A ): effettua la fattorizzazione LU di una matrice tridiagonale
  secondo l'algoritmo di Thomas

*/

void LU_fact( double A[3][dim] )
{
  for ( int i = 1; i <= dim - 1; i++ )
    {
      A[0][i] = A[0][i] / A[1][i-1];
      A[1][i] = A[1][i] - A[0][i] * A[2][i-1];
    }
}


/*

  LU_solve( A, f, x ): esegue l'inversione del sistema a*x=b
  secondo l'algoritmo di Thomas.

*/

void LU_solve( double A[3][dim], double f[dim], double x[dim] )
{
  double y[dim];

  y[0] = f[0];
  for ( int i = 1; i <= dim - 1; i++ )
    y[i] = f[i] - A[0][i] * y[i-1];

  x[dim-1] = y[dim-1] / A[1][dim-1];
  for ( int i = dim - 2; i >= 0; i-- ) 
    x[i] = ( y[i] - A[2][i] * x[i+1] ) / A[1][i];
}


int main()
{
  cout << "Calcolo della soluzione dell\'equazione differenziale:" << endl;
  cout << "d^2 Y / dx^2 + f(x) * d Y / dx + g(x) * Y = h(x)" << endl;


  // Intervallo di definizione di x

  double x[N], a, b;
  a = 0.0;     // Inserire l'estremo sinistro dell'intervallo di definizione
  b = 0.0 ;    // Inserire l'estremo destro dell'intervallo di definizione
  double dx = ( b - a ) / ( N - 1 );     // Nota: il numero di intervalli e' N-1!
  double dx2 = dx * dx;
  double ddx = 2.0 * dx;
  for ( int j = 0; j < N; j++ ) x[j] = a + j * dx;


  // Definizione della matrice D delle derivate e secondo membro

  double D[3][dim];
  double sm[dim];

  // Quello che appare nella prima e nell'ultima riga della matrice,
  // nonche' a secondo membro, dipende dalle condizioni al bordo

  switch ( bct )
    {
    case 1:
      D[0][0] = 0.0;
      D[1][0] = - 2.0 / dx2 + g( x[j_init] );
      D[2][0] = 1.0 / dx2 + f( x[j_init] ) / ddx;
      sm[0]   = h( x[j_init] ) - Ya * ( 1.0 / dx2 - f( x[j_init] ) / ddx );
      D[0][dim-1] = 1.0 / dx2 - f( x[j_end] ) / ddx;
      D[1][dim-1] = - 2.0 / dx2 + g( x[j_end] );
      D[2][dim-1] = 0.0;
      sm[dim-1]   = h( x[j_end] ) - Yb * ( 1.0 / dx2 + f( x[j_end] ) / ddx );
      break;
    case 2:
      D[0][0] = 0.0;
      D[1][0] = - 2.0 / dx2 + g( x[j_init] );
      D[2][0] = 1.0 / dx2 + f( x[j_init] ) / ddx;
      sm[0]   = h( x[j_init] ) - Ya * ( 1.0 / dx2 - f( x[j_init] ) / ddx );
      D[0][dim-1] = 2.0 / dx2;
      D[1][dim-1] = - 2.0 / dx2 + g( x[j_end] );
      D[2][dim-1] = 0.0;
      sm[dim-1]   = h( x[j_end] ) - ddx * Ypb * ( 1.0 / dx2 + f( x[j_end] ) / ddx );
      break;
    case 3:
      D[0][0] = 0.0;
      D[1][0] = - 2.0 / dx2 + g( x[j_init] );
      D[2][0] = 2.0 / dx2;
      sm[0]   = h( x[j_init] ) - ddx * Ypa * ( 1.0 / dx2 - f( x[j_init] ) / ddx );
      D[0][dim-1] = 1.0 / dx2 - f( x[j_end] ) / ddx;
      D[1][dim-1] = - 2.0 / dx2 + g( x[j_end] );
      D[2][dim-1] = 0.0;
      sm[dim-1]   = h( x[j_end] ) - Yb * ( 1.0 / dx2 + f( x[j_end] ) / ddx );
      break;
    case 4:
      D[0][0] = 0.0;
      D[1][0] = - 2.0 / dx2 + g( x[j_init] );
      D[2][0] = 2.0 / dx2;
      sm[0]   = h( x[j_init] ) - ddx * Ypa * ( 1.0 / dx2 - f( x[j_init] ) / ddx );
      D[0][dim-1] = 2.0 / dx2;
      D[1][dim-1] = - 2.0 / dx2 + g( x[j_end] );
      D[2][dim-1] = 0.0;
      sm[dim-1]   = h( x[j_end] ) - ddx * Ypb * ( 1.0 / dx2 + f( x[j_end] ) / ddx );
      break;
    }

  for ( int j = 1; j < dim - 1; j++ )
    {
      D[0][j] = 1.0 / dx2 - f( x[j_init+j] ) / ddx;
      D[1][j] = - 2.0 / dx2 + g( x[j_init+j] );
      D[2][j] = 1.0 / dx2 + f( x[j_init+j] ) / ddx;
      sm[j]   = h( x[j_init+j] );
    }


  // Fattorizzazione LU della matrice D

  LU_fact( D );


  // Inverte il sistema fattorizzato LU

  double Y[dim];
  LU_solve( D, sm, Y );


  // Stampa del risultato

  // Legge in input il nome del file

  char fname[250];
  cout << "Nome del file dei risultati: ";
  cin >> fname;

  // Apre il file e imposta la massima precisione

  ofstream outFile;
  outFile.open( fname );
  outFile.precision( 15 );

  // Se Y(a) e' noto, lo scrive nel file

  if ( ( bct == 1 ) || ( bct == 2 ) ) outFile << x[0] << "\t\t" << Ya << endl;

  // Scrive su file i valori calcolati

  for ( int j = 0; j < dim; j++ )
    outFile << x[j_init+j] << "\t\t" << Y[j] << endl;

  // Se Y(b) e' noto, lo scrive nel file

  if ( ( bct == 1 ) || ( bct == 3 ) ) outFile << x[N-1] << "\t\t" << Yb << endl;

  // Chiude il file e termina il programma

  outFile.close();
  return( 0 );
}
