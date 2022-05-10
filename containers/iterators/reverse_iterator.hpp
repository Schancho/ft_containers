#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{
    template<typename Iterator>
    class reverse_iterator
    {
        public:
            typedef Iterator iterator_type;
            typedef typename iterator_traits<iterator_type>::value_type value_type;
            typedef typename iterator_traits<iterator_type>::difference_type difference_type;
            typedef typename iterator_traits<iterator_type>::pointer pointer;
            typedef typename iterator_traits<iterator_type>::reference reference;
            typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;

            reverse_iterator(): current() {}
            explicit reverse_iterator(iterator_type it) : current(it) {}
            template<class Iter>
            reverse_iterator(const reverse_iterator<Iter>& it) : current(it.base()) {}

            operator  reverse_iterator<const Iterator> ()
            {
                return reverse_iterator<const Iterator>(current);
            }
            iterator_type base() const 
            {
                return current;
            }

            reference operator*() const
            {
                iterator_type tmp = current;
                std::cout << "check" << std::endl;
                return *--tmp;
            }

            pointer operator->() const
            {
                iterator_type tmp(current);
                --tmp;
                std::cout << "heeeeeeere" << std::endl;
                return tmp.operator->();
            }

            reverse_iterator& operator++()
            {
                std::cout << "increment1" << std::endl;
                --current;
                return *this;
            }

            reverse_iterator operator++(int)
            {
                 std::cout << "increment2" << std::endl;
                reverse_iterator tmp = *this;
                --current;
                return tmp;
            }

            reverse_iterator& operator--()
            {
                ++current;
                return *this;
            }

            reverse_iterator operator--(int)
            {
                reverse_iterator tmp = *this;
                ++current;
                return tmp;
            }

            reverse_iterator operator+(difference_type n) const
            {
                return reverse_iterator(current - n);
            }

            reverse_iterator& operator+=(difference_type n)
            {
                current -= n;
                return *this;
            }

            reverse_iterator operator-(difference_type n) const
            {
                return reverse_iterator(current + n);
            }

            reverse_iterator& operator-=(difference_type n)
            {
                current += n;
                return *this;
            }

            reference operator[](difference_type n) const
            {
                return *(*this + n);
            }

            bool operator==(const reverse_iterator& it) const
            {
                return current == it.current;
            }


            bool operator!=(const reverse_iterator& it) const
            {
                return current != it.current;
            }

            bool operator<(const reverse_iterator& it) const
            {
                return current > it.current;
            }

            bool operator>(const reverse_iterator& it) const
            {
                return current < it.current;
            }

            bool operator<=(const reverse_iterator& it) const
            {
                return current >= it.current;
            }

            bool operator>=(const reverse_iterator& it) const
            {
                return current <= it.current;
            }

        private:
            iterator_type current;
};

template <class Iterator>
reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& it)
{
    return it + n;
}

template<class Iterator>
typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return rhs.base() - lhs.base();
}

template<class Iterator>
bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return lhs.base() == rhs.base();
}

template<class Iterator>
bool operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return lhs.base() != rhs.base();
}

template<class Iterator>
bool operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return lhs.base() > rhs.base();
}

template<class Iterator>
bool operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return lhs.base() < rhs.base();
}

template<class Iterator>
bool operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return lhs.base() >= rhs.base();
}

template<class Iterator>
bool operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return lhs.base() <= rhs.base();
}



}
#endif