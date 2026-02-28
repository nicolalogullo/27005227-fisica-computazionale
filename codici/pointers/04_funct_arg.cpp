/*

  File func_point.ccp:
  Exercises on how to use pointers in C++

*/

#include <iostream>
using std::printf;

/*
  Main program
*/

void double_var_pntr(int *p)
{
  printf("%s: The variable is stored at address %ld \n", __func__, (long) p);
  *p=2* (*p);
}

void double_var(int a)
{
  //printf("%s: The variable is stored at address %ld \n", __func__, (long) &a);
  a=2*a;
}

int main()
{
  int a; // Declaring a new variable a
  int *pa; // Declaring a pointer variable, one can use int* pa

  a=5; // Setting value of a
  pa=&a; // Setting the value of pa to the memory address of a

  printf("%s: A new variable a has been set. It takes %d bytes of memory \n", __func__,(int) sizeof(a));
  printf("%s: a= %d \n", __func__,a);
  
  printf("%s: The variable a is stored at address pa= %ld \n", __func__,(long) pa);
  printf("%s: At address pa=&a= %ld the value %d is stored \n", __func__,(long) pa, a);
  
  //double_var(a);
  double_var_pntr(&a);

  printf("main: Now a= %d \n", a);
  

  return 0;
}
