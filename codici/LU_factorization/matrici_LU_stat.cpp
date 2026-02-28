#include <iostream>
using namespace std;

const int dim=3;

void fattorizzazioneLU( double A[dim][dim], double L[dim][dim], double U [dim][dim] )

{
	int i, j, k;
	double somma;

	for (i=0; i < dim; i++)
	{
		L[i][0] = A[i][0];
	}
	for (j=1; j < dim; j++)
	{
		U[0][j] = (A[0][j])/L[0][0];
	}


	for (i = 1; i < dim; i++)
	{
		for (j = 1; j <= i; j++)
		{
			somma = 0.0;	 
			for ( k = 0; k < j; k++)
			{
				
				somma = somma + (L[i][k]) * (U[k][j]);
			}
			
			
			L[i][j] = A[i][j] - somma;

		}

		for (j = i+1; j < dim; j++)
		{				
			somma = 0.0;
			for (k = 0; k < i; k++)
			{

				somma = somma + (L[i][k])*(U[k][j]);
			}

			U[i][j] = (A[i][j] - somma)/L[i][i];
		}

	}

}

int main()
{
	// Matrice A
	double A[dim][dim]= { {1, 2, 1},
			  {0, 1, 2},
			  {1, 1, 2}};
	double L[dim][dim];
	double U[dim][dim];
	
	for (int i=0; i<dim; i++)
	{
		for(int j=0; j<dim; j++)
		{
			L[i][j] = 0;
			U[i][j] = 0;
		}
			
	}
	
	for (int i=0; i<dim; i++)
	{
		U[i][i] = 1;
	}
	
	// Calcolo LU
	fattorizzazioneLU ( A, L, U );
	
	// Verifica A=LU
	
	
	double prodotto[dim][dim] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			for (int k = 0; k < dim; k++)
				prodotto[i][j] += L[i][k] * U[k][j];
			
			if (prodotto[i][j] != A[i][j])
				return false;
		}
	
	}
		

	

	// Stampa L e U
	
	cout << "La matrice L e':" << "\n";
	for (int i = 0; i < dim; i++)
	{
		cout << endl;
		for (int j = 0; j < dim; j++)
		{
			 cout << L[i][j] << "\t" ;

		}
		
		cout << endl;
	
	}
	
	cout << "\n" << "La matrice U e':" << "\n";

	for (int i = 0; i < dim; i++)
	{
		cout << endl;
		for (int j = 0; j < dim; j++)
		{
			 cout << U[i][j] << "\t";

		}
		cout << endl;
	}

return 0;
}
