/*

  File 02_arthm.ccp:
  Exercises on how to use pointers in C++

*/

#include <iostream>
using std::printf;
using std::cout;

/*
  Main program
*/

int main()
{
  int a; // Declaring a new variable a
  int *p0; // Declaring a pointer variable, one can use int* p0

  a=5; // Setting value of a
  p0=&a; // Setting the value of pa to the memory address of a

  printf("%s: A new variable a has been set. It takes %d bytes of memory \n", __func__,(int) sizeof(a));
  printf("%s: a= %d \n", __func__,a);
  
  printf("%s: The variable a is stored at address p0= %ld \n", __func__,(long) p0);
  printf("%s: At address p0  = %ld the value %d is stored \n", __func__,(long) p0, a);

//  printf("%s: At address p0+1= %ld the value %d is stored \n", __func__,(long) (p0+1), *(p0+1));


  //Trying to set the value at a memory address which has not been allocated by the program

  *(p0+1)=10; // Does not raise an error because the p0+1 memordy address has not been allocated to the program!
  printf("%s: At address p0+1= %ld the value %d is stored \n", __func__,(long) p0, *p0);
  printf("%s: At address p0  = %ld the value %d is stored \n", __func__,(long) (p0+1), *(p0+1));

  
  //Using another pointer to check and modify p0+1
//  int *p1;
//  p1=(p0+1);
//
//  printf("%s: At address p0+1= %ld the value %d is stored \n", __func__,(long) (p0+1), *(p0+1));
//  printf("%s: At address p1= %ld the value %d is stored \n", __func__,(long) (p1), *p1);
//  
//  //*(p0+1)=15; // Raise an error because the p0+1 address is not in use!
//
//  *p1=10; // Does not raise an error because the p1 has been declared!
//  cout << "I have set a value at p1 \n";
//	  
//  printf("%s: At address p1= %ld the value %d is stored \n", __func__,(long) (p1), *p1);
//  printf("%s: At address p0  = %ld the value is stored \n", __func__,(long) (p0));
//  printf("%s: The address of a is stored at  %ld \n", __func__,(long) &a);
//  printf("%s: At address p0+1= %ld the value %d is stored \n", __func__,(long) (p0+1), *(p0+1));

  return 0;
}
