/*
 * [2020] Northeastern University - Network Programming
 *
 * All Rights Reserved.
 * 
 * Authors Michele Polese 
 */

// remember to use the relevant #include
#include <iostream>
using namespace std;

// the binary generated from this C++ code should be called
// with at least one extra command line argument
// for example: /path/to/bin/exercise_2 extra_argument
int main (int argc, char* argv[])
{
	if (argc <= 1)
	{
		cout << "No argument has been passed" << endl;
		return 0;
	}
	else
	{
		cout << "Received " << argc << " arguments from the command line." << endl;
		for (int i = 0; i < argc; ++i)
  		{
    		cout << "Argument " << (i+1) << " is " << argv[i] << endl;
  		}
	}

	// declare an array of C-style strings (i.e., string literals) 
	// which should contain the command-line arguments, except for the
	// name of this binary
	// the size of the array should adapt to the number of arguments
	// passed from the command line
	// initialize each entry in the array with the command-line arguments
	// (except for the name of the binary, which is the first entry in argv)
	const int Array_Size = argc-1;
	char* Arg_Array[Array_Size];
	for(int i = 0; i < Array_Size; i++)
	{
		Arg_Array[i] = argv[i+1];
	}

	// print the content of the array to the terminal, one entry for each line
	// (without using argv!)
	cout << "The command line argument: " << endl;
	for(int i = 0; i < Array_Size; i++)
	{
		cout << Arg_Array[i] << endl;
	}
	
	// print the first string literal in the array, one letter for each line
	cout << "Each Letter for first word of the command line argument: " << endl;
	for(const char* ch = Arg_Array[0]; *ch != '\0'; ch++)
	{
		cout << *ch << endl;
	}

	return 0;
}