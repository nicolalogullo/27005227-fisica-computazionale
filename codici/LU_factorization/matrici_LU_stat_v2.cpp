#include <iostream>
using namespace std;

const int dim=4;

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

void prodotto(double A[dim][dim], double B[dim][dim], double C[dim][dim])
{
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {	
		C[i][j]=0.0;
            for (int k = 0; k < dim; k++) C[i][j] += A[i][k] * B[k][j];
        }
    }
}


void printM(double M[dim][dim], char name)
{
    cout << "La matrice   "<< name  <<"   e':" << "\n";
    for (int i = 0; i < dim; i++)
    {
        cout << endl;
        for (int j = 0; j < dim; j++)
        {
             cout << M[i][j] << "\t" ;

        }
        cout << endl;
    }        
}    

int main()
{
    // Matrice A
/*    double A[dim][dim]= {{1, 2, 1},
                 {0, 1, 2},
                 {1, 1, 2}};
*/
    double A[dim][dim]= {{1, 2, 1, -3},
                 {0, 1, 2, 1},
                 {1, 0, -1, 3},
                 {1, 1, 2, 5}};

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
    
    
    double prod[dim][dim];

	prodotto(L,U,prod);


// Stampa
  printM(L,'L');
  printM(U,'U');  
  cout << endl;
  cout << endl;
  cout << endl;
  printM(A,'A'); 
  printM(prod,'P');  

return 0;
}
