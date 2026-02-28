/*

  File 05_arrays.ccp:
  Exercises on how to use pointers in C++

*/

#include <iostream>
using std::printf;
using std::cout;

/*
  Main program
*/

int sum_arr(int a[], int size)
{
  int i, tot=0;
  for (i=0;i<size;i++) // Setting value of a
  {
	  tot+=a[i];
  } 
 return tot;
}

void double_arr(int a[], int size)
{
  int i, tot=0;
  for (i=0;i<size;i++) // Setting value of a
  {
	  a[i]=2*a[i];
  } 
}

int main()
{
  int i;
  int a [5]; // Declaring a new variable a
  int tot, size;

  for (i=0;i<5;i++) // Setting value of a
  {
	  a[i]=i+1;
  } 
  
  printf("Printing a; a = %ld \n",(long) a);
  printf("Printing a[0]; a[0] = %d \n", a[0]); 
  printf("Printing the address of a[0]; &a[0] = %ld \n",(long) &a[0]); 

  printf("Printing by dereferencing *a= %d \n", *a);
  printf("Printing by dereferencing *(a+1)= %d \n", *(a+1));
  printf("Printing by dereferencing *(a+2)= %d \n", *(a+2));

  int *p0;
  p0=a;
  printf("Printing the pointer p0=a; p0 = %ld \n",(long) p0); 
  
  printf("Printing the value stored at p0; *p0 = %d \n", *p0); 
  printf("Printing the value stored at p0+1; *p0 = %d \n", *(p0+1)); 


  // Using arrays as argument of functions
  size=sizeof(a)/sizeof(int);
  printf("The number of elements of a is %d \n", size); 

  tot=sum_arr(a,size);

  printf("The sum of elements of a is  %d \n", tot); 


  //2D arrays
  int b[2][3];
  int j;
  for (i=0;i<2;i++) // Setting value of b
  {
	  for (j=0;j<3;j++)
	  {
	    b[i][j]=(i+1)*(j+1);
	  }
  } 

  printf("Printing b; b = %ld \n",(long) b);
  printf("Printing b[0]; b[0] = %ld \n",(long) b[0]);
  printf("Printing b[1]; b[1] = %ld \n",(long) b[1]);
 
  //int *p1;
  int (*p1) [3];
  
  
  p1=b; //Wrong because b is an array of arrays whereas p1 is a simple integer
  printf("Printing p1[0]; p1[0] = %ld \n",(long) p1[0]);
  printf("Printing p1[1]; p1[0] = %ld \n",(long) p1[1]);


  return 0;
}
