/*

   Programma Eq_lin.cpp:

   risolve l'equazione lineare: dv/dt = -k*v
   (con k costante assegnata) con lo schema
   di Eulero forward, backward e Runge-Kutta 
   al secondo ordine. Calcola anche la soluzione
   esatta e l'errore.

*/

#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

main()
{

  cout << "Risoluzione di una equazione: dv/dt = -k*v" << endl;
  cout << "con Eulero-Forward e Backward e RK2" << endl;

  cout << "Inserire dt, Tend, Tprint: ";
  double dt, Tend, Tprint;
  cin >> dt >> Tend >> Tprint;

  long Nend   = long( Tend / dt );
  long Nprint = long( Tprint / dt );

  cout << "Inserire costanti k, v0: ";
  double k, v0;
  cin >> k >> v0;

  cout << "Nome del file di output: ";
  char nfile[256];
  cin >> nfile;

  cout << "Inserisci il tipo di schema da utilizzare:" << endl;
  cout << "  1 - Eulero forward" << endl;
  cout << "  2 - Eulero backward" << endl;
  cout << "  3 - Runge-Kutta al 2o ordine" << endl;
  int schema;
  cin >> schema;

  // Condizioni iniziali

  double t_n, v_n, v_np1, v_star, v_ex, err;
  t_n  = 0.0;
  v_n  = v0;
  v_ex = v0;
  err = abs( v_n - v_ex );

  // Apertura del file di output e scrittura condizioni iniziali

  ofstream fout;
  fout.open( nfile );
  fout.precision( 15 );
  fout << "#   t     v    v_ex    err" << endl;
  fout << t_n << "   " << v_n << "   " << v_ex << "   " << err << endl;

  // Ciclo temporale

  for ( long n = 1; n <= Nend; n++ )
    {

      t_n = n * dt;

      // Calcola v al passo successivo a seconda dello schema da usare

      switch ( schema )
	{
	case 1:
	  v_np1 = v_n * ( 1.0 - k * dt );
	  break;
	case 2:
	  v_np1 = v_n / ( 1.0 + k * dt );
	  break;
	case 3:
	  v_star = v_n + 0.5 * dt * ( -k * v_n );
	  v_np1  = v_n + dt * ( -k * v_star );
	  break;
	}

      v_n = v_np1;

      // Stampa ogni Tprint intervalli di stampa

      if ( ( n % Nprint ) == 0 )
	{
	  v_ex = v0 * exp( - k * t_n );
	  err = abs( v_n - v_ex );
	  fout << t_n << "   " << v_n << "   " << v_ex << "   " << err << endl;
	}

    }

  fout.close();

}
