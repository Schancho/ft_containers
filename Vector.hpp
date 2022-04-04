#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <string>

class Vector
{

	public:

		Vector();
		Vector( Vector const & src );
		~Vector();

		Vector &		operator=( Vector const & rhs );

	private:

		int *_arry;

};

std::ostream &			operator<<( std::ostream & o, Vector const & i );

#endif /* ********************************************************** VECTOR_H */