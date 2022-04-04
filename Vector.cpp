#include "Vector.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Vector::Vector()
{
}

Vector::Vector( const Vector & src )
{
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Vector::~Vector()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Vector &				Vector::operator=( Vector const & rhs )
{
	//if ( this != &rhs )
	//{
		//this->_value = rhs.getValue();
	//}
	return *this;
}

std::ostream &			operator<<( std::ostream & o, Vector const & i )
{
	//o << "Value = " << i.getValue();
	return o;
}


/*
** --------------------------------- METHODS ----------------------------------
*/


/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */