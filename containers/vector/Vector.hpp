#pragma once

# include <iostream>
# include <string>
#include <memory>
#include "../../iterators/iterator.hpp"
#include "../../iterators/reverse_iterator.hpp"
#include "../../utils/lexicographical_compare.hpp"
#include <algorithm>
#include <iterator>
#include "../../utils/enable_if.hpp"
#include "../../utils/is_integral.hpp"

namespace ft {

template < class T, class Alloc = std::allocator<T> > 
class vector
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
			//typedef std::allocator<value_type> allocator_type;


		explicit vector (const allocator_type& alloc = allocator_type())
			: _alloc(alloc)
		{
			_capacity = 0;
			_size = 0;
			_data = _alloc.allocate(_capacity);
			// std::cout << _data << std::endl;
		}

		vector (size_type n, const value_type& value = value_type(), const allocator_type& alloc = allocator_type())
			: _alloc(alloc)
		{
			_capacity = n;
			_size = n;
			if(n)
				_data = _alloc.allocate(_capacity);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(&_data[i], value);
		}

		vector (const vector& other)
			: _alloc(other._alloc)
		{
			_capacity = other._capacity;
			_size = other._size;
			_data = _alloc.allocate(_capacity);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(&_data[i], other._data[i]);
		}

		vector	&operator= (const vector& other)
		{
			if (this != &other)
			{
				_alloc.deallocate(_data, _capacity);
				_capacity = other._capacity;
				_size = other._size;
				_data = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&_data[i], other._data[i]);
			}
			return *this;
		}

		template <class InputIterator>
		vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), 
			typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type *f = NULL)
			: _alloc(alloc)
		{
		// 	_capacity = std::distance(first, last);
		// 	_size = _capacity;
		// 	_data = _alloc.allocate(_capacity);
		// 	for (size_type i = 0; i < _size; i++)
		// 		_alloc.construct(&_data[i], *(first + i));
		// }
			(void)f;
			difference_type n;
			n = std::distance(first, last);
			if (n < 0)
				n = n * (-1);
			_capacity = n;
			_size = n;
			if(n)
				_data = _alloc.allocate(n);
			for (size_type i = 0; i < _size && first != last ; i++, first++)
				_alloc.construct(&_data[i], *first);
		}
		
		~vector ()
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(&_data[i]);
			if (_data)
				_alloc.deallocate(_data, _capacity);
		}


		// template <class T, class Alloc>
	  	friend	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
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
	  	friend	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return !(lhs == rhs);
		}

		// template <class T, class Alloc>
		friend bool operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}

				// template <class T, class Alloc>
		friend bool operator >(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return  rhs < lhs;
		}

		// template <class T, class Alloc>
		friend bool operator <=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return  !(rhs < lhs);
		}

				// template <class T, class Alloc>
		friend bool operator >=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
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
			if (n < _size)
            {
                for (size_type i = n; i < _size; ++i)
                    _alloc.destroy(_data + i);
                _size = n;
            }
            else if (n > _capacity)
            {
                if (n > (_capacity * 2))
                    reserve(n);
                else
                    reserve(_capacity * 2);
                for (size_type i = _size; i < n; ++i)
                    push_back(val);
            }
            else if (n > _size)
                for (size_type i = _size; i < n; ++i)
                    push_back(val);
		}


		void	reserve(size_type cap)
		{
			if (cap > max_size())
                throw std::length_error("length error");
			if (cap > _capacity)
			{
				pointer tmp = _alloc.allocate(cap);
				for (size_type i = 0; i < _size; i++)
				{
					_alloc.construct(tmp + i, _data[i]);
					_alloc.destroy(_data + i);
				}
				//_alloc.destroy()
				_alloc.deallocate(_data, _capacity);
				_data = tmp;
				_capacity = cap;
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
                reserve(_capacity == 0 ? 1 : _capacity * 2);
            _alloc.construct(_data + _size, val);
			_size++;
		}
		
		void pop_back()
		{
			_alloc.destroy(_data+_size-1);
			_size--;
		}


		void swap(vector& other)
		{
			std::swap(_data, other._data);
			std::swap(_size, other._size);
			std::swap(_capacity, other._capacity);
		}

		template <class InputIterator>
		void assign(InputIterator first, InputIterator last,
					typename std::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
		{
			size_type n = last - first;
			if (n > _capacity)
			{
				_capacity = n;
				size_type cap = _capacity;
				pointer tmp = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(tmp+i, _data[i]);
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_data+i);
				_alloc.deallocate(_data, cap);
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
				size_type cap = _capacity;
				pointer tmp = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(tmp+i, _data[i]);
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_data+i);
				_alloc.deallocate(_data, cap);
				_data = tmp;
			}
			for (size_type i = 0; i < n; i++)
				_alloc.construct(_data+i, val);
			_size = n;
		}

		iterator		insert(iterator pos, const value_type& val)
		{
			difference_type n = pos - _data;
			if (_size == _capacity)
				reserve(_capacity == 0 ? 1 : _capacity * 2);
			for (difference_type i = _size; i > n; i--)
				_alloc.construct(_data+i, _data[i-1]);
			_alloc.construct(_data+n, val);
			++_size;
			return iterator(_data+n);
		}

		void 	insert(iterator pos, size_type n, const value_type& val)
		{
			difference_type p = pos - _data;
			if (_capacity < _size + n && n <= _size)
                reserve(_capacity * 2);
            else if (_size + n > _capacity)
                reserve(_capacity + n);
			if (_size)
			{
				
				for (difference_type i = _size - 1; i >= p ; i--)
				{
					_alloc.construct(_data +i + n, _data[i]); 
					if (i == p)
						break;
				}
					
			}  
            for (size_type i = 0; i < n; ++i)
				_alloc.construct(_data + p + i, val);
            _size += n;
		}
		template <class InputIterator>
    	void insert (iterator position, InputIterator first, InputIterator last , typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type *f = NULL)
		{

			(void)f;
			// difference_type pos = position - _data;
			// size_type n = last - first;
			// if (_capacity < _size + n && n <= _size)
			// 	reserve(_capacity * 2);
			// else if (_size + n > _capacity)
			// 	reserve(_capacity + n);
			// if (_size)
			// {
			// 	for (difference_type i = _size - 1; i >= pos ; i--)
			// 	{
			// 		_alloc.construct(_data +i + n, _data[i]); 
			// 		if (i == pos)
			// 			break;
			// 	}
			// }
			// for (size_type i = 0; i < n; ++i)
			// 	_alloc.construct(_data + pos + i, *(first+i));
			// _size += n;
			difference_type pos = position - _data;
            size_type n = last - first;
            if (_capacity < _size + n && n <= _size)
                reserve(_capacity * 2);
            else if (_size + n > _capacity)
                reserve(_capacity + n);
			pointer tmp = _data;
			size_type size = _size;
            for (size_type i = pos; i < _size; ++i)
                _alloc.construct(_data + i + n,  _data[i]);
            for (size_type i = 0; i < n; ++i)
                _alloc.construct(_data + pos + i, *(first + i));
			for (size_type i = 0; i < size; i++)
				_alloc.destroy(tmp + i);
            //_alloc.deallocate(tmp, _capacity);
			_size += n;
		}

		allocator_type get_allocator()
        {
            return _alloc;
        }
		
		void	clear()
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(_data+i);
			_size = 0;
		}

		// void			print(void) const
		// {
		// 	for (unsigned int i = 0; i < _size; i++)
		// 		std::cout << _data[i] << std::endl;
		// }
		
		iterator erase (iterator position)
		{
			size_t p = &position - _data;
			for (size_t i = p; i < _size - 1; i++)
				_alloc.construct(_data + i, _data[i + 1]);
			_alloc.destroy(_data + _size - 1);
			_size--;
			return iterator(_data + p);
		}
		iterator erase (iterator first, iterator last)
		{
			size_type n = last - first;
            for (size_type i = first - _data; i < _size - n; ++i)
                _data[i] = _data[i + n];
            _size -= n;
            return first;
		}

	private:
		pointer				_data;
		size_type			_size;
		size_type			_capacity;
		allocator_type		_alloc;
};

template <class T, class Alloc>
void	swap(vector<T, Alloc>& a, vector<T, Alloc>& b)
{
	a.swap(b);
}

}

