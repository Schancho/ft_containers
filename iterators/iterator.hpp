#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iostream>
#include <string>
#include "iterator_traits.hpp"
namespace ft
{
    template <typename T>
    class iterator_op : public ft::iterator<std::random_access_iterator_tag, T>
    {
        public:
            typedef typename iterator<std::random_access_iterator_tag, T>::difference_type		difference_type;
			typedef typename iterator<std::random_access_iterator_tag, T>::value_type			value_type;
			typedef typename iterator<std::random_access_iterator_tag, T>::pointer				pointer;
			typedef typename iterator<std::random_access_iterator_tag, T>::reference			reference;
			typedef typename iterator<std::random_access_iterator_tag, T>::iterator_category	iterator_category;
            typedef size_t	size_type;
            iterator_op(){}
            iterator_op(T *ptr) : _ptr(ptr) {}
            iterator_op(const iterator_op &it) : _ptr(it._ptr) {}
            operator  iterator_op< const value_type>() const 
            { 
                return iterator_op< const value_type>(_ptr); 
            }
            //  operator  iterator_op< const T> ()  const
            // {
            //     std::cout << "Allo" << std::endl;
            //     return iterator_op<const T>(_ptr);
            // }
            iterator_op &operator=(const iterator_op &it) 
            {
                _ptr = it._ptr;
                return *this;
            }

            pointer base() const 
            { 
                return _ptr; 
            }
            iterator_op &operator++()
            {
                ++_ptr;
                return *this;
            }


            T *operator&()
            {
                return  _ptr;
            }


            iterator_op operator++(int)
            {
                iterator_op tmp(*this);
                ++_ptr;
                return tmp;
            }

            iterator_op &operator--()
            {
                --_ptr;
                return *this;
            }
            iterator_op operator--(int)
            {
                iterator_op tmp(*this);
                --_ptr;
                return tmp;
            }

            iterator_op &operator+=(difference_type n)
            {
                _ptr += n;
                return *this;
            }

            iterator_op &operator-=(difference_type n)
            {
                _ptr -= n;
                return *this;
            }

            iterator_op operator+(difference_type n)
            {
                iterator_op tmp(*this);
                tmp += n;
                return tmp;
            }

            iterator_op operator+(difference_type n) const 
            {
                iterator_op tmp(*this);
                tmp += n;
                return tmp;
            }

            iterator_op operator-(difference_type n)
            {
                iterator_op tmp(*this);
                tmp -= n;
                return tmp;
            }

            iterator_op operator-(difference_type n) const 
            {
                iterator_op tmp(*this);
                tmp -= n;
                return tmp;
            }

            difference_type operator-(const iterator_op &it)
            {
                return _ptr - it._ptr;
            }

            reference operator*()
            {
                return *_ptr;
            }

            pointer operator->()
            {
                return _ptr;
            }

            reference       operator[](size_type n)
            {
                return _ptr[n];
            }

            template <class U>
            bool operator==(const iterator_op<U> &it) const 
            {
                return _ptr == it.base();
            }

            template <class U>
            bool operator!=(const iterator_op<U> &it) const
            {
                return _ptr != it.base();
            }   

            template <class U>
            bool operator<(const iterator_op<U> &it) const
            {
                return _ptr < it.base();
            }

            template <class U>
            bool operator>(const iterator_op<U> &it) const
            {
                return _ptr > it.base();
            }

            template <class U>
            bool operator<=(const iterator_op<U> &it) const
            {
                return _ptr <= it.base();
            }
   
            template <class U>
            bool operator>=(const iterator_op<U> &it) const
            {
                return _ptr >= it.base();
            }

            pointer get_pointer(){
				return _ptr;
			}
           
        private:
            T *_ptr;
    };
    template  <typename T>
    iterator_op<T> operator+(typename iterator_op<T>::difference_type n, iterator_op<T> it)
    {
        return it + n;
    }

    template  <typename T>
    iterator_op<T> operator-(typename iterator_op<T>::difference_type n, iterator_op<T> it)
    {
        return it - n;
    }
    
}

#endif