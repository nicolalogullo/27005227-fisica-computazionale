#include <iostream>
using namespace std;


 
void fattorizzazione_LU(double** a, double** l, double** u, int dim)
{
	
  for(int i=0; i<dim; i++)
  {
   u[i][i] = 1;
  }
  
  for(int i=0; i<dim; i++)
  {
   l[i][0] = a[i][0];
  }
  
  for(int j=1; j<dim; j++)
  {
   u[0][j] = (a[0][j])/(l[0][0]);
  }
  
  double sum;

  for(int i=1; i<dim; i++)
  {
  	
   for(int j=1; j<=i; j++)
   {
    sum = 0.0;
    
    for(int k=0; k<=j-1; k++)
    {
     sum = sum + (l[i][k])*(u[k][j]);
    }
    
    l[i][j] = a[i][j] - sum;
    
    }
   
   for(int j=i+1; j<dim; j++)
   {
    sum = 0;

    for(int k=0; k<=i-1; k++)
    {
     sum = sum + (l[i][k])*(u[k][j]);
    }

    u[i][j] = (a[i][j] - sum)/(l[i][i]);
    }
   }
}


void stampa_mat(double** a, int dim, char nome)
{ 
  cout << "\n" << "la matrice " << nome << ": " << "\n" ;
  for(int i=0; i<dim; i++)
  {
   for(int j=0; j<(dim-1); j++)
   {
    cout << a[i][j] << " ";
   }
   cout << a[i][dim-1] << "\n";
  }

 cout << "\n";
}


 
bool verifica(double** a, double** l, double** u, int dim)
{
  bool b = 1;
 
  int val;
  for(int i=0; i<dim; i++)
  { 
   val = 0;
   
   for(int j=0; j<dim; j++)
   {
    val = val + (l[i][j])*(u[j][i]);
    
	if(val =! a[i][j])
    {
    b=0;
    }
    
   }
   
  } 
  return b;
}


int main()
{
  int dim;

  cout << "inserire la dimensione della matrice" << "\n";
  
  cin >> dim;
  
  double** a = new double*[dim];

  for(int i=0; i<dim; i++)
    {
      a[i] = new double[dim];
    }
  
  double** l = new double*[dim];

  for(int i=0; i<dim; i++)
    {
      l[i] = new double[dim];
    }
  
  double** u = new double*[dim];

  for(int i=0; i<dim; i++)
    {
      u[i] = new double[dim];
    }

  cout << "inserire i valori nella matrice" << "\n";
  
  double val;

  for(int i=0; i<dim; i++)
  {
   for(int j=0; j<dim; j++)
   {
    cin >> val;
    a[i][j] = val;
   }
  }
  
  fattorizzazione_LU(a,l,u,dim);

  if(verifica(a,l,u,dim) == 1)
  {
   stampa_mat(a,dim,'A');
   stampa_mat(l,dim,'L');
   stampa_mat(u,dim,'U');
  }
  else
  {
    cout << "errore";
  }

  return 0;
}

  
  
  
  
  

  
  
