#ifndef Vector_HPP
# define Vector_HPP

# include <iostream>
# include <string>
#include <memory>
#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include <algorithm>
#include <iterator>
#include "enable_if.hpp"

namespace ft {

	template <class InputIterator1, class InputIterator2>
  bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2)
{
  while (first1!=last1)
  {
    if (first2==last2 || *first2<*first1) return false;
    else if (*first1<*first2) return true;
    ++first1; ++first2;
  }
  return (first2!=last2);
}



template < class T, class Alloc = std::allocator<T> > 
class Vector
{
	public:
			typedef	T	value_type;
			typedef Alloc allocator_type;
			typedef size_t	size_type;
			typedef	ft::iterator_op<T> iterator;
			typedef ft::reverse_iterator<iterator>	reverse_iterator;
			typedef	ft::iterator_op<const value_type>			const_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			typedef typename	allocator_type::pointer	pointer;
			typedef typename	allocator_type::const_pointer	const_pointer;
			typedef typename	allocator_type::reference	reference;
			typedef typename	allocator_type::const_reference const_reference;
			typedef typename	std::ptrdiff_t							difference_type;


		explicit Vector (const allocator_type& alloc = allocator_type())
			: _alloc(alloc)
		{
			_capacity = 0;
			_size = 0;
			_data = _alloc.allocate(_capacity);
		}

		Vector (size_type n, const value_type& value = value_type(), const allocator_type& alloc = allocator_type())
			: _alloc(alloc)
		{
			_capacity = n;
			_size = n;
			if(n)
				_data = _alloc.allocate(_capacity);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(&_data[i], value);
		}

		Vector (const Vector& other)
			: _alloc(other._alloc)
		{
			_capacity = other._capacity;
			_size = other._size;
			_data = _alloc.allocate(_capacity);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(&_data[i], other._data[i]);
		}

		template <class InputIterator>
		Vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), 
			typename ft::enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type *f = 0)
			: _alloc(alloc)
		{
			_capacity = std::distance(first, last);
			_size = _capacity;
			_data = _alloc.allocate(_capacity);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(&_data[i], *(first + i));
		}
		// 	difference_type n;
		// 	n = std::distance(first, last);
		// 	if (n < 0)
		// 		n = n * (-1);
		// 	_capacity = n;
		// 	_size = n;
		// 	if(n)
		// 		_data = _alloc.allocate(n);
		// 	for (difference_type i = 0; i < _size && first != last ; i++, first++)
		// 		_alloc.construct(&_data[i], *first);
		// }
		
		~Vector ()
		{}


		// template <class T, class Alloc>
	  	friend	bool operator== (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
		{
			if (lhs.size() !=  rhs.size())
				return false;
			for (size_t i = 0; i < lhs.size(); i++)
			{
				if (lhs[i] != rhs[i])
					return false;
			}
			return true;
		}

				// template <class T, class Alloc>
	  	friend	bool operator!= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
		{
			return !(lhs == rhs);
		}

		// template <class T, class Alloc>
		friend bool operator< (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
		{
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}

				// template <class T, class Alloc>
		friend bool operator >(const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
		{
			return  rhs < lhs;
		}

		// template <class T, class Alloc>
		friend bool operator <=(const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
		{
			return  !(rhs < lhs);
		}

				// template <class T, class Alloc>
		friend bool operator >=(const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
		{
			return  !( lhs < rhs);
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
		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}
		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}
		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(end());
		}
		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		}
		size_type size() const
		{
			return _size;
		}

		size_type capacity() const
		{
			return _capacity;
		}
		
		size_type max_size() const
		{
			return _alloc.max_size();
		}
	
		void resize(size_type n, value_type val = value_type())
		{
			if (n > _capacity)
			{
				value_type *tmp = _alloc.allocate(n);
				for (size_type i = 0; i < _size; i++)
					tmp[i] = _data[i];
				for (size_type i = _size; i < n; i++)
					tmp[i] = val;
				_alloc.deallocate(_data, _capacity);
				_data = tmp;
			}
			else if (n < _size)
			{
				for (size_type i = n; i < _size; i++)
					_alloc.destroy(_data + i );
				_alloc.deallocate(_data + n, _size - n);
			}
			else if (n > _size)
			{
				for (size_type i = _size; i < n; i++)
					_data[i] = val;
			}
		}

		void	reserve(unsigned int cap)
		{
			if (cap > _capacity)
			{
				_capacity = cap;
				pointer tmp = _alloc.allocate(_capacity);
				for (unsigned int i = 0; i < _size; i++)
				{
					_alloc.construct(tmp+i, _data[i]);
				}
				for (unsigned int i = 0; i < _size; i++)
				{
					_alloc.destroy(_data+i);
				}
				_alloc.deallocate(_data, _capacity);
				_data = tmp;
			}
		}
		bool empty() const
		{
			return _size == 0;
		}

		reference operator[] (size_type n)
		{
			return _data[n];
		}

		const_reference operator[] (size_type n) const
		{
			return _data[n];
		}

		reference at(size_type n)
		{
			if (n >= _size)
				throw std::out_of_range("out of range");
			return _data[n];
		}

		const_reference at(size_type n) const
		{
			if (n >= _size)
				throw std::out_of_range("out of range");
			return _data[n];
		}

		reference front()
		{
			return _data[0];
		}

		const_reference front() const
		{
			return _data[0];
		}

		reference back()
		{
			return _data[_size-1];
		}

		const_reference back() const
		{
			return _data[_size-1];
		}

		void push_back(const value_type& val)
		{
			if (_size == _capacity)
			{
				_capacity *= 2;
				pointer tmp = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(tmp+i, _data[i]);
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_data+i);
				_alloc.deallocate(_data, _capacity);
				_data = tmp;
			}
			_alloc.construct(_data+_size, val);
			_size++;
		}
		
		void pop_back()
		{
			_alloc.destroy(_data+_size-1);
			_size--;
		}


		void swap(Vector& other)
		{
			std::swap(_data, other._data);
			std::swap(_size, other._size);
			std::swap(_capacity, other._capacity);
		}

		template <class InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			size_type n = last - first;
			if (n > _capacity)
			{
				_capacity = n;
				pointer tmp = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(tmp+i, _data[i]);
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_data+i);
				_alloc.deallocate(_data, _capacity);
				_data = tmp;
			}
			for (size_type i = 0; i < n; i++)
				_alloc.construct(_data+i, *(first+i));
			_size = n;
		}

		void assign(size_type n, const value_type& val)
		{
			if (n > _capacity)
			{
				_capacity = n;
				pointer tmp = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(tmp+i, _data[i]);
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_data+i);
				_alloc.deallocate(_data, _capacity);
				_data = tmp;
			}
			for (size_type i = 0; i < n; i++)
				_alloc.construct(_data+i, val);
			_size = n;
		}


		// void			pop_back()
		// {
		// 	_alloc.destroy(_data + _size - 1);
		// 	--_size;
		// }

		iterator		insert(iterator pos, const value_type& val)
		{
			size_t p = std::distance(this->begin(), pos);
			if (_size == _capacity)
			{
				_capacity *= 2;
				pointer tmp = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(tmp + i, _data[i]);
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_data+i);
				_alloc.deallocate(_data, _capacity);
				_data = tmp;
			}
			for (size_type i = _size; i > p; i--)
				_alloc.construct(_data+i, _data[i-1]);
			_alloc.construct(_data + p, val);
			_size++;
			return iterator(_data + p);
		}

		void 	insert(iterator pos, size_type n, const value_type& val)
		{
			// size_t p = std::distance(this->begin(), pos);
			size_t p = &pos - _data;
						std::cout <<  "==>" <<  p << std::endl;

			if (n > _capacity)
			{
				_capacity = n;
				pointer tmp = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(tmp+i, _data[i]);
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_data+i);
				_alloc.deallocate(_data, _capacity);
				_data = tmp;
			}
			int j = _size;
			for (size_type i = _size + n; i > _size; i--)
				_alloc.construct(_data + i, _data[j--]);
			for (size_type i = 0; i < n; i++)
				_alloc.construct(_data+ p + i, val);
			_size += n;
		}
		template <class InputIterator>
    	void insert (iterator position, InputIterator first, InputIterator last , typename ft::enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type *f = 0)
		{
			std::cout << " 3" << std::endl;
			while (first != last)
			{
				this->insert(position, *first);
				++position;
				++first;
			}
		}

		void	clear()
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(_data+i);
			_size = 0;
		}

		void			print(void) const
		{
			for (unsigned int i = 0; i < _size; i++)
				std::cout << _data[i] << std::endl;
		}

allocator_type get_allocator() const;
		
iterator erase (iterator position);
iterator erase (iterator first, iterator last);

	private:
		T *				_data;
		unsigned int	_size;
		unsigned int	_capacity;
		allocator_type	_alloc;
};


// bool oprator <(a, b)
// {
// 	lexicographical_compare(a.begin(), a.end(), b.begin(), b.end())
// }
// bool oprator >()
// {
// 	return !(a < b)
}




#endif
