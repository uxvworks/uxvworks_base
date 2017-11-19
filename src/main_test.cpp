/*
 * Copyright (c) <year> <author> (<email>)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "cppbase/factorial.hpp"
#include "module1/factorial1.h"

int main_test( void /*const int numberOfInputs, const char* inputArguments[ ] */)
{
	try
	{
		const int factorial = cppbase::computeFactorial( 10 );
		std::cout << "10! = " << factorial << std::endl;
	}
	catch( std::exception& error )
	{
		std::cout << error.what( ) << std::endl;
	}

	try
	{
		const int factorial = cppbase::computeFactorial( -5 );
		std::cout << "5! = " << factorial << std::endl;
	}
	catch( std::exception& error )
	{
		std::cout << error.what( ) << std::endl;
	}

   try
	{
		const int factorial1 = computeFactorial1( 15 );
		std::cout << "15! = " << factorial1 << std::endl;
	}
	catch( std::exception& error )
	{
		std::cout << error.what( ) << std::endl;
	}

	return EXIT_SUCCESS;
}
