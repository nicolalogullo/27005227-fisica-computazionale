/*

  File 06_dynamic.ccp:
  Exercises on how to use pointers in C++

*/

#include <iostream>
#include <typeinfo>
using std::printf;
using std::cout;

/*
  Main program
*/

/*
  C:
  malloc
  calloc
  realloc
  free

  C++:
  new
  delete
  But C++ has backward compatibility, therefore it will accept the C functions 
*/



int main()
{
  int a; // Declaring a new variable a
  int *p0; // Declaring a pointer variable, one can use int* p0

  a=5; // Setting value of a on the stack
  // malloc by default returns a void pointer
  //p0=(int*)malloc(sizeof(int)); // Setting the value of pa to the memory address of a
  p0= new int[5];

  printf("A new memory slot of type %s has been allocated of size %ld \n", typeid(p0).name(), sizeof(p0) );
  printf("A new memory slot of type %s has been allocated of size %ld \n", typeid(p0).name(), sizeof(p0) );

  //free(p0) // Empty the memory
  delete[] p0
  //p0=(int*)malloc(sizeof(int));
  printf("A new memory slot of type %s has been allocated of size %ld \n", typeid(p0).name(), sizeof(p0) );

  return 0;
}
