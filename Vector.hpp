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
			typedef	T	value_type;
			typedef Alloc allocator_type;
			typedef size_t	size_type;
			typedef	ft::iterator_op<T> iterator;
			//typedef ft::reverse_iterator<iterator>	reverse_iterator;
			typedef	ft::iterator_op<const value_type>			const_iterator;
			//typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			typedef typename	allocator_type::pointer	pointer;
			typedef typename	allocator_type::const_pointer	const_pointer;
			typedef typename	allocator_type::reference	reference;
			typedef typename	allocator_type::const_reference const_reference;
			typedef typename	std::ptrdiff_t							difference_type;


		Vector()
		{
			_data = _alloc.allocate(1);
			_capacity = 1;
			_size =0;
		}
		Vector(unsigned int cap)
		{
			_capacity = cap;
			_size =0;
			_data = _alloc.allocate(_size);
			
		}
		~Vector()
		{}

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
		
		void			push_back(T const & value)
		{
			// _data[_size] = value;
			_alloc.construct(_data + _size, value);
			++_size;
		}
		void			pop_back()
		{
			_alloc.destroy(_data + _size - 1);
			--_size;
		}
		void			print(void) const
		{
			for (unsigned int i = 0; i < _size; i++)
				std::cout << _data[i] << std::endl;
		}

	private:
		T *				_data;
		unsigned int	_size;
		unsigned int	_capacity;
		allocator_type	_alloc;
};


}
#endif
