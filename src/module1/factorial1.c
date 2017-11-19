/*
 * Copyright (c) <year> <author> (<email>)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

//#include <sstream>
//#include <stdexcept>

#include "module1/factorial1.h"


//! Compute factorial.
const int computeFactorial1( const int integerNumber )
{
	if ( integerNumber < 0 )
	{
	//	std::ostringstream errorMessage;
	//	errorMessage << "ERROR: (" << integerNumber << "!) is undefined!" << std::endl;
	//	throw std::runtime_error( errorMessage.str( ) );
	}

	return ( integerNumber == 0 ) ? 1 : integerNumber * computeFactorial1( integerNumber  - 1 );
}


//} // namespace cppbase
