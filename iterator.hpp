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
            iterator_op(T *ptr) : _ptr(ptr) {}
            iterator_op(const iterator_op &it) : _ptr(it._ptr) {}
             operator  iterator_op<const T> ()
            {
                std::cout << "Hey" << std::endl;
                return iterator_op<const T>(_ptr);
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

            iterator_op &operator++()
            {
                ++_ptr;
                return *this;
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

            iterator_op operator-(difference_type n)
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

            bool operator==(const iterator_op &it)
            {
                return _ptr == it._ptr;
            }

            bool operator!=(const iterator_op &it)
            {
                return _ptr != it._ptr;
            }   

            bool operator<(const iterator_op &it)
            {
                return _ptr < it._ptr;
            }

            bool operator>(const iterator_op &it)
            {
                return _ptr > it._ptr;
            }

            bool operator<=(const iterator_op &it)
            {
                return _ptr <= it._ptr;
            }

            bool operator>=(const iterator_op &it)
            {
                return _ptr >= it._ptr;
            }

        private:
            T *_ptr;
    };
}

#endif