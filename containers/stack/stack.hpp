#pragma once

#include "../vector/Vector.hpp"

namespace ft
{
    template <class T, class Container = Vector<T> >
    class stack
    {
        public:
            typedef T value_type;
            typedef Container container_type;
            typedef typename Container::size_type size_type;

            explicit stack (const container_type& ctnr = container_type()) : _container(ctnr) {}

            bool empty() const
            {
                return _container.empty();
            }

            void pop()
            {
                _container.pop_back();
            }

            void push (const value_type& val)
            {
                _container.push_back(val);
            }

            size_type size() const
            {
                return _container.size();
            }

            value_type& top()
            {
                return _container.back();
            }

            const value_type& top() const
            {
                return _container.back();
            }

            friend bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
            {
                return lhs._container == rhs._container;
            }

            friend bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
            {
                return !(lhs == rhs);
            }

            friend bool operator< (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
            {
                return lhs._container < rhs._container;
            }

            friend bool operator> (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
            {
                return rhs < lhs;
            }

            friend bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
            {
                return !(rhs < lhs);
            }

            friend bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
            {
                return !(lhs < rhs);
            }

        protected:
            container_type _container;
    };

    

}