#pragma once

#include <iterator>
#include "../../iterators/bidirectional_iterator.hpp"
#include "../../iterators/reverse_iterator.hpp"
#include "avl.hpp"
#include "../../utils/lexicographical_compare.hpp"
#include "../../utils/equal.hpp"
#include "../vector/vector.hpp"
#include "../../utils/enable_if.hpp"
#include <vector>
#include <iostream>
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
            typedef ft::reverse_iterator<iterator> reverse_iterator;
            typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
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
                            const allocator_type &alloc = allocator_type()) : _tree(), _compare(comp), _allocator(alloc) 
                {}

                template <class InputIterator>
                map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(),
                    const allocator_type &alloc = allocator_type()) : _tree(), _compare(comp), _allocator(alloc)
                {
                    //(void)f;
                    while (first != last)
                    {
                        insert(*first);
                        ++first;
                    }
                }

                map(const map &other)
                {
                   _tree = other._tree;
                    _compare = other._compare;
                    _allocator = other._allocator;
                }

                map  &operator=(const map &other)
                {
                    if (this != &other)
                    {
                        _tree = other._tree;
                        _compare = other._compare;
                        _allocator = other._allocator;
                    }
                    return *this;
                }

                ~map()
                {
                    clear();
                }

                iterator begin()
                {
                    node_type *tmp = most_left(_tree.root);
                    return (iterator(tmp, const_cast<node_type **>(&_tree.root))); 
                }

                const_iterator begin() const
                {
                    node_type *tmp = most_left(_tree.root);
                    return (const_iterator(tmp, const_cast<node_type **>(&_tree.root)));
                }

                iterator end()
                {
                    return iterator(NULL, const_cast<node_type **>(&_tree.root));
                }

                const_iterator end() const
                {
                    return const_iterator(NULL, const_cast<node_type **>(&_tree.root));
                }

                reverse_iterator rbegin()
                {
                    return reverse_iterator(end());
                }

                const_reverse_iterator rbegin() const
                {
                    return const_reverse_iterator(end());
                }

                reverse_iterator rend()
                {
                    return reverse_iterator(begin());
                }
                
                const_reverse_iterator rend() const
                {
                    return const_reverse_iterator(begin());
                }

                bool empty() const
                {
                    return _tree.empty();
                }

                size_type size() const
                {
                    return _tree.size();
                }

                size_type max_size() const
                {
                    return _allocator.max_size();
                }

                mapped_type &operator[](const key_type &key1)
                {
                    ft::pair<key_type, mapped_type> p = ft::make_pair(key1, mapped_type());
                    _tree.insert(p);
                    node_type *tmp = _tree.search(_tree.root, key1);
                    return tmp->data->second;
                }

                void    erase(iterator pos)
                {
                    value_type tmp = *pos;
                    _tree.remove(tmp.first);
                }

                size_type erase(const key_type &key1)
                {
                    return _tree.remove(key1);
                }

                void erase(iterator first, iterator last)
                {
                   ft::vector<key_type> keys;
                    while (first != last)
                    {
                        keys.push_back(first->first);
                        ++first;
                    }
                    typename ft::vector<key_type>::iterator it = keys.begin();
                    while (it != keys.end())
                    {
                        erase(*it);                       
                        ++it;
                    }
                }

                void swap(map &other)
                {
                    _tree.swap(other._tree);
                    std::swap(_compare, other._compare);
                    std::swap(_allocator, other._allocator);
                }

                void clear()
                {
                    this->erase(begin(), end());
                }

                key_compare key_comp() const
                {
                    return _compare;
                }

                value_compare   value_comp() const
                {
                    return value_compare(_compare);
                }

                iterator    find(const key_type &key1)
                {
                    node_type *tmp = _tree.search(_tree.root, key1);
                    if (tmp == NULL)
                        return end();
                    return (iterator(tmp, const_cast<node_type **>(&_tree.root)));
                }

                const_iterator find(const key_type &key1) const
                {
                    node_type *tmp = _tree.search(_tree.root, key1);
                    if (tmp == NULL)
                        return end();
                    return (const_iterator(tmp, const_cast<node_type **>(&_tree.root)));
                }

                size_type count(const key_type &key1) const
                {
                    node_type *tmp = _tree.search(_tree.root, key1);
                    if (tmp == NULL)
                        return 0;
                    return 1;
                }

                allocator_type get_allocator() const
                {
                    return _allocator;
                }

                pair<iterator, bool> insert(const value_type &val)
                {
                    ft::pair<key_type, mapped_type> p = ft::make_pair(val.first, val.second);
                    node_type *tmp = _tree.search(_tree.root, val.first);
                    if (tmp == NULL)
                    {
                        _tree.insert(p);
                        tmp = _tree.search(_tree.root, val.first);
                        return (pair<iterator, bool>(iterator(tmp, const_cast<node_type **>(&_tree.root)), true));
                    }
                    else
                    {
                        return (pair<iterator, bool>(iterator(tmp, const_cast<node_type **>(&_tree.root)), false));
                    }
                }

                template <class InputIterator>
                void    insert(InputIterator first, InputIterator last)
                {
                    for (; first != last; ++first)
                    {
                        insert(*first);
                    }
                }

                iterator insert(iterator position, const value_type &val)
                {
                    (void)position;
                    return (this->insert(val).first);
                }

                iterator    lower_bound(const key_type &key1)
                {
                    iterator it = begin();
                    iterator bg = end();
                    while (it != bg)
                    {
                        if (_compare(it->first, key1) == false)
                            break ;
                        ++it;
                    }
                    return (it);
                    // node_type *tmp = _tree.lower_bound(_tree.root, key1);
                    // if (tmp == NULL)
                    //     return end();
                    // return (iterator(tmp, const_cast<node_type **>(&_tree.root)));
                }

                const_iterator lower_bound(const key_type &key1) const
                {
                    const_iterator it = begin();
                    const_iterator bg = end();
                    while (it != bg)
                    {
                        if (_compare(it->first, key1) == false)
                            break ;
                        ++it;
                    }
                    return (it);
                }

                iterator    upper_bound(const key_type &key1)
                {
                    iterator it = begin();
                    iterator bg = end();
                    while (it != bg)
                    {
                        if (_compare(key1, it->first) == true)
                            break ;
                        ++it;
                    }
                    return (it);
                }

                const_iterator upper_bound(const key_type &key1) const
                {
                    const_iterator it = begin();
                    const_iterator bg = end();
                    while (it != bg)
                    {
                        if (_compare(key1, it->first) == true)
                            break ;
                        ++it;
                    }
                    return (it);
                }
                void   print()
                {
                    _tree.print();
                }

                pair<iterator, iterator> equal_range(const key_type &key1)
                {
                    ft::pair<iterator, iterator> p = ft::make_pair(lower_bound(key1), upper_bound(key1));
                    return p;
                }

                pair<const_iterator, const_iterator> equal_range(const key_type &key1) const
                {
                    ft::pair<const_iterator, const_iterator> p = ft::make_pair(lower_bound(key1), upper_bound(key1));
                    return p;
                }
    };
    template <class k, class T, class Comp, class Allocat>
    bool operator==(const ft::map<k, T, Comp, Allocat> &lhs,
                    const ft::map<k, T, Comp, Allocat> &rhs)
    {
        return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template <class k, class T, class Comp, class Allocat>
    bool operator!=(const ft::map<k, T, Comp, Allocat> &lhs,
                    const ft::map<k, T, Comp, Allocat> &rhs)
    {
        return !(lhs == rhs);
    }

    template <class k, class T, class Comp, class Allocat>
    bool operator<(const ft::map<k, T, Comp, Allocat> &lhs,
                    const ft::map<k, T, Comp, Allocat> &rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class k, class T, class Comp, class Allocat>
    bool operator>(const ft::map<k, T, Comp, Allocat> &lhs,
                    const ft::map<k, T, Comp, Allocat> &rhs)
    {
        return rhs < lhs;
    }
    template <class k, class T, class Comp, class Allocat>
    bool operator<=(const ft::map<k, T, Comp, Allocat> &lhs,
                    const ft::map<k, T, Comp, Allocat> &rhs)
    {
        return !(rhs < lhs);
    }

    template <class k, class T, class Comp, class Allocat>
    bool operator>=(const ft::map<k, T, Comp, Allocat> &lhs,
                    const ft::map<k, T, Comp, Allocat> &rhs)
    {
        return !(lhs < rhs);
    }
}