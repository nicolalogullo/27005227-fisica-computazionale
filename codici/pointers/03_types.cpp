/*

  File 03_types.ccp:
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

  a=2049; // Setting value of a
  p0=&a; // Setting the value of p0 to the memory address of a

  printf("A new variable a has been set. It takes %d bytes of memory \n", (int) sizeof(a));
  printf("a= %d \n", a);
  printf("Variable a is stored at address p0= %ld \n", (long) p0);
  printf("At address p0=&a= %ld the value %d is stored \n", (long) p0, a);
  
  char *p1;
  p1=(char*) p0;

  printf("The new pointer p1 is pointing ad the address memory: %ld \n", (long) p1);
  printf("At the address p1 the the value %d is stored \n", *p1);
  printf("At the address (p1+1) the the value %d is stored \n", *(p1+1));
  
  void *p2;
  p2=p1;
  printf("The new pointer p2 is pointing ad the address memory: %ld \n", (long) p2);
  printf("At the address p2 the the value %d is stored \n", *p2); // Wrong because the compiler does not know the length
  

  return 0;
}
