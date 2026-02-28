/*

  File 01_def.ccp:
  Exercises on how to use pointers in C++

*/

#include <iostream>
using std::printf;

/*
  Main program
*/

int main()
{
  int a; // Declaring a new variable a
  int *p0; // Declaring a pointer variable, one can use int* p0

  a=5; // Setting value of a
  p0=&a; // Setting the value of p0 to the memory address of a

  printf("A new variable a has been set. It takes %d bytes of memory \n", (int) sizeof(a));
  printf("a= %d \n", a);
  printf("Variable a is stored at address p0= %ld \n", (long) p0);
  printf("At address p0=&a= %ld the value %d is stored \n", (long) p0, a);

  printf("\n Setting the variable via dereferencing *p0=8 \n");
  *p0=8; //Setting the value stored at p0 (Dereferencing)
  printf("Now a= %d \n", a);
  printf("Via dereferencing (*p0) a= %d \n", *p0);
  
  printf("\n");
  printf("The value of the pointer variable p0 is stored at the address &p0 %ld \n", (long) &p0);

  int b; // Declering a new variable b

  b=23;
  *p0=b;
  printf("\n");
  printf("The value of the new variable b is %d \n", b);
  printf("The value stored at the address &p0= %ld is = %d \n", (long) &p0, b);


  return 0;
}
