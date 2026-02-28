/*
   Programma Osc_armonico:

   integra l'equazione differenziale dell'oscillatore armonico.
   Equazione:

   d^2 x / dt^2 = - w^2 * x

   utilizzando gli schemi di Eulero Forward per entrambe le
   equazioni, la prima equazione con EF e la seconda con
   EB (schema Leap Frog), e Runge-Kutta al secondo ordine
*/

#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

main()
{

  cout << "Risoluzione dell\'equazione: d^2 x/dt^2 = -w^2*x" << endl;
  cout << "con Eulero-Forward e Backward e RK2" << endl;

  cout << "Inserire dt, Tend, Tprint: ";
  double dt, Tend, Tprint;
  cin >> dt >> Tend >> Tprint;

  long Nend   = long( Tend / dt );
  long Nprint = long( Tprint / dt );

  cout << "Inserire costanti w, x0, v0: ";
  double w, x0, v0;
  cin >> w >> x0 >> v0;
  double w2 = w * w;

  cout << "Nome del file di output: ";
  char nfile[256];
  cin >> nfile;

  cout << "Inserisci il tipo di schema da utilizzare:" << endl;
  cout << "  1 - Eulero forward" << endl;
  cout << "  2 - Eulero forward-backward" << endl;
  cout << "  3 - Runge-Kutta al 2o ordine" << endl;
  int schema;
  cin >> schema;

  // Condizioni iniziali

  double t_n, x_n, x_np1, x_star, v_n, v_np1, v_star;
  double A, phi, x_ex, Energia, E0;

  t_n  = 0.0;
  x_n  = x0;
  v_n  = v0;

  if ( v0 != 0.0 )
    {
      A = sqrt( pow( x0, 2 ) + pow( ( v0 / w ), 2.0 ) );
      phi = atan( x0 * w / v0 );
    }
  else
    {
      A = x0;
      phi = acos( -1.0 ) / 2.0;
    }
  x_ex = A * sin( w * t_n + phi );

  Energia = 0.5 * ( v_n * v_n + w2 * x_n * x_n );
  E0 = Energia;

  // Apertura del file di output e scrittura condizioni iniziali

  ofstream fout;
  fout.open( nfile );
  fout.precision( 15 );
  fout << "#   t     x     v     x_ex    err    DEn" << endl;
  fout << t_n << "   " << x_n << "    " << v_n << "   " << x_ex <<  "   " << Energia - E0 << endl;

  // Ciclo temporale

  for ( long n = 1; n <= Nend; n++ )
    {

      t_n = n * dt;

      // Calcola v al passo successivo a seconda dello schema da usare

      switch ( schema )
	{
	case 1:
	  x_np1 = x_n + dt * v_n;
	  v_np1 = v_n - w2 * dt * x_n;
	  break;
	case 2:
	  x_np1 = x_n + dt * v_n;
	  v_np1 = v_n - w2 * dt * x_np1;
	  break;
	case 3:
	  x_star = x_n + 0.5 * dt * v_n;
	  v_star = v_n - w2 * 0.5 * dt * x_n;
	  x_np1 = x_n + dt * v_star;
	  v_np1 = v_n - w2 * dt * x_star;
	  break;
	}

      x_n = x_np1;
      v_n = v_np1;

      // Stampa ogni Tprint intervalli di stampa

      if ( ( n % Nprint ) == 0 )
	{
          x_ex = A * sin( w * t_n + phi );
          Energia = 0.5 * ( v_n * v_n + w2 * x_n * x_n );
	  fout << t_n << "   " << x_n << "    " << v_n << "   " << x_ex << "   " << 
                  Energia - E0 << endl;
	}

    }

  fout.close();

}
