#pragma once

#include <iterator>
#include "../iterators/bidirectional_iterator.hpp"
#include "avl.hpp"
#include "../utils/lexigraphical_compare.hpp"


namespace ft
{
    template <
        class key,
        class Mapped_Type,
        class Compare = std::less<key>,
        class Alloc = std::allocator<pair<const key, Mapped_Type> >
        >
    class map
    {
        public:
            typedef key key_type;
            typedef Mapped_Type mapped_type;
            typedef typename ft::pair<const key, mapped_type> value_type;
            typedef Compare key_compare;
            typedef Alloc allocator_type;
            typedef typename allocator_type::reference reference;
            typedef typename allocator_type::const_reference const_reference;
            typedef typename allocator_type::pointer pointer;
            typedef typename allocator_type::const_pointer const_pointer;
            typedef typename allocator_type::size_type size_type;
            typedef typename ft::Avl<key, mapped_type, Compare, Alloc> tree;
            typedef ft::Node<value_type> node_type;
            typedef ft::bidirectional_iterator<node_type, value_type> iterator;
            typedef ft::bidirectional_iterator<node_type, value_type> const_iterator;
            typedef std::reverse_iterator<iterator> reverse_iterator;
            typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
            typedef ptrdiff_t difference_type;
            typedef class value_compare : public std::binary_function<value_type, value_type, bool>
            {
                protected:
                    key_compare _compare;

                public:
                    typedef bool result_type;
                    typedef value_type first_argument_type;
                    typedef value_type second_argument_type;
                    bool operator()(const value_type &lhs, const value_type &rhs) const
                    {
                        return _compare(lhs.first, rhs.first);
                    }
                    value_compare(key_compare comp) : _compare(comp) {}
            } value_compare;

            private:
                tree _tree;
                key_compare _compare;
                allocator_type _allocator;

            public:
                explicit map(const key_compare &comp = key_compare(), 
                            const allocator_type &alloc = allocator_type()) : _tree(comp), _compare(comp), _allocator(alloc) 
                {}

                template <class InputIterator>
                map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(),
                    const allocator_type &alloc = allocator_type()) : _tree(), _compare(comp), _allocator(alloc)
                {
                }

                //insert single element
                pair<iterator, bool> insert(const value_type &val)
                {
                    ft::pair<key_type, mapped_type> p = ft::make_pair(val.first, val.second);
                    node_type *tmp = _tree.search(_tree.root, val.first);
                    if (tmp == nullptr)
                    {
                        _tree.insert(p);
                        


}