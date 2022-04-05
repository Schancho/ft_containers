#ifndef random_access_iterator_H
#define random_access_iterator_H

#include <iostream>
#include <string>

namespace ft
{
    template <typename T>
    class random_access_iterator
    {
        public:
            random_access_iterator( T* ptr)
            {
                _ptr = ptr;
            }

          operator  random_access_iterator<const T> ()
            {
                std::cout << "Hey" << std::endl;
                return random_access_iterator<const T>(_ptr);
            }
             operator  random_access_iterator< const T> ()  const
            {
                std::cout << "Hey" << std::endl;
                return random_access_iterator<const T>(_ptr);
            }


            random_access_iterator(const random_access_iterator& src)
            {
                std::cout<< "Copy" << std::endl;
                _ptr = src._ptr;
            }
            // template <typename T>
            // random_access_iterator(const random_access_iterator<const T>& src)
            // {
            //     _ptr = src._ptr;
            // }
            
            random_access_iterator & operator++(void)
            {
                _ptr++;
                return *this;
            }
            random_access_iterator & operator++(int)
            {
                random_access_iterator tmp = *this;
                _ptr++;
                return tmp;
            }
            random_access_iterator & operator--(void)
            {
                _ptr--;
                return *this;
            }
            random_access_iterator & operator--(int)
            {
                random_access_iterator tmp = *this;
                _ptr--;
                return tmp;
            }
            T & operator*(void)
            {
                return *_ptr;
            }
            T * operator->(void)
            {
                return _ptr;
            }
            bool operator==(const random_access_iterator& rhs)
            {
                return (_ptr == rhs._ptr);
            }
            bool operator!=(const random_access_iterator& rhs)
            {
                return (_ptr != rhs._ptr);
            }
            //asigeration operator
            random_access_iterator & operator=( random_access_iterator< T>& rhs)
            {
                std::cout << "assignation" << std::endl;
                _ptr = rhs._ptr;
                return *this;
            }
            // template <typename const T>
            // random_access_iterator & operator=( random_access_iterator< T>& rhs)
            // {
            //     _ptr = rhs._ptr;
            //     return *this;
            // }





            T *_ptr;

    };
}

#endif