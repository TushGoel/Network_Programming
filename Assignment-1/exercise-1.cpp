/*
 * [2019] Signet Lab - Programming for ICT
 * [2020] Northeastern University - Network Programming
 *
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
 */

/* The header was missing */
#include <iostream>

struct Trivial {
  int a; 
  Trivial(int aa) : a(aa) { } 
  Trivial() = default; // use the compiler generated 
                       // constructor
};

// do not modify the enumerators, find some other way
enum NotScoped {green, blue, red};
enum class SameEnumerators {green, yellow};

int main(int argc, char* argv[])
{
  /*1) An unsigned is an integer that can never be negative so replacing {-10} --> {10}
    2) The line is not terminated i.e. semi colon was missing at the end of line          */
  unsigned int unsigned_integer_variable {10};
  
  /* 1) The range of short int is -32768 to 32767. So the short int declared is exceeding the range
        i.e. out of range. 
        Replacing {90000} --> {32767}   */
  short short_variable {32767};

  std::cout << "unsigned_integer_variable " << unsigned_integer_variable
    << " short_variable " << short_variable << std::endl;

/* error: ‘void*’ is not a pointer-to-object type.
   Replacing void* --> unsigned int*             */
  unsigned int* pointer {&unsigned_integer_variable};
  std::cout << "pointer content " << pointer 
    << " value pointed by pointer " << *pointer << std::endl;

  /*const char* is a mutable pointer to an immutable character/string
    and also string can be converted to char.
    So replacing constant char *p --> char p[] */
  char p[] = "northeastern";
  std::cout << "before modification " << *p << std::endl;
  (*p) = 'c';
  std::cout << "after modification " << *p << std::endl;

  Trivial structure{10};
  Trivial* ptr_struct{&structure};

  /*To access the struct member we need to use '.' operator and,
    for accessing structure members using structure pointer, we need to use '->' operator   */
  /* Replacing 'structure->a' with 'structure.a'
  and Replacing 'ptr_struct.a' with 'ptr_struct->a'    */
  std::cout << "Value in struct " << structure.a 
    << " with pointer " << ptr_struct->a << std::endl;
 
  return 0;
}
