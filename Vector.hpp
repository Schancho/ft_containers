#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <string>
#include <memory>
#include "iterator.hpp"
namespace ft {
template < class T, class Alloc = std::allocator<T> > 
class Vector
{
	public:
			typedef   Alloc allocator_type;
			typedef        T value_type ;
			allocator_type _alloc;
			typedef random_access_iterator<T> iterator;
			typedef random_access_iterator<const T> const_iterator;


		// Vector()
		// {
		// 	_size = 0;
		// 	// _capacity = 0;
		// 	_data = nullptr;
		// }
		Vector(unsigned int cap)
		{
			_capacity = cap;
			_size =0;
			_data = _alloc.allocate(_size);
			
		}

		iterator begin()
		{
			return iterator(_data);
		}
		iterator end()
		{
			return iterator(_data+_size);
		}
		const_iterator begin() const 
		{
			return const_iterator(_data);
		}
		const_iterator end() const
		{
			return const_iterator(_data+_size);
		}
		// Vector(Vector const & src);
		~Vector()
		{}

		// Vector &	operator=(Vector const & rhs);
		// T &			operator[](unsigned int index);
		// T const &	operator[](unsigned int index) const;

		// unsigned int	size(void) const;
		// void			resize(unsigned int size);
		void			push_back(T const & value)
		{
			// _data[_size] = value;
			_alloc.construct(_data + _size, value);
			++_size;
		}
		// void			pop_back(void);
		// void			clear(void);
		// void			erase(unsigned int index);
		// void			insert(unsigned int index, T const & value);
		// void			reverse(void);
		// void			sort(void);
		// void			swap(unsigned int index1, unsigned int index2);
		// void			fill(T const & value);
		void			print(void) const
		{
			for (unsigned int i = 0; i < _size; i++)
				std::cout << _data[i] << std::endl;
		}

	private:
		T *				_data;
		unsigned int	_size;
		unsigned int	_capacity;
};


}
#endif
