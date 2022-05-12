#pragma once

#include <iterator>
#include "../iterators/bidirectional_iterator.hpp"
#include "../iterators/reverse_iterator.hpp"
#include "avl.hpp"
#include "../utils/lexicographical_compare.hpp"
#include "../utils/equal.hpp"
#include "../vector/Vector.hpp"
#include "../utils/enable_if.hpp"
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
                    const allocator_type &alloc = allocator_type(), typename ft::enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type *f = 0 ) : _tree(), _compare(comp), _allocator(alloc)
                {
                    int i= 0;
                    while (first != last)
                    {
                        
                       // std::cout << "debug1: "<< first->first << std::endl;
                        
                        insert(*first);
                        //std::cout << "debug2: "<< first->second << std::endl;
                        ++first;
                        //std::cout << "debug3: "<< first->second << std::endl;
                        // i++;
                        // if (i == 6)
                        //     break;
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
                    // std::cout << "debug: " << tmp->data->first << std::endl;
                    // std::cout << "debug: " << tmp->data->second << std::endl;
                    return (iterator(tmp, const_cast<node_type **>(&_tree.root))); //casting
                }

                const_iterator begin() const
                {
                    node_type *tmp = most_left(_tree.root);
                    return (const_iterator(tmp, const_cast<node_type **>(&_tree.root))); //casting
                }

                // iterator end
                iterator end()
                {
                    return iterator(NULL, const_cast<node_type **>(&_tree.root));
                }

                const_iterator end() const
                {
                    return const_iterator(NULL, const_cast<node_type **>(&_tree.root));
                }

                // reverse iterator rbegin
                reverse_iterator rbegin()
                {
                    return reverse_iterator(end());
                }

                const_reverse_iterator rbegin() const
                {
                    return const_reverse_iterator(end());
                }

                // reverse iterator rend
                reverse_iterator rend()
                {
                    return reverse_iterator(begin());//segfauuuuuuult
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
                   std::vector<key_type> keys;
                    while (first != last)
                    {
                        keys.push_back(first->first);
                        ++first;
                    }
                    typename std::vector<key_type>::iterator it = keys.begin();
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

                size_t call_count()
                {
                    return _tree.call_count;
                }


                //insert single element
                pair<iterator, bool> insert(const value_type &val)
                {
                    _tree.clock_start(0);
                    ft::pair<key_type, mapped_type> p = ft::make_pair(val.first, val.second);
                    node_type *tmp = _tree.search(_tree.root, val.first);
                    _tree.clock_stop(0);

                    if (tmp == NULL)
                    {
                        _tree.clock_start(1);
                        _tree.insert(p);
                        tmp = _tree.search(_tree.root, val.first);
                         _tree.clock_stop(1);
                        return (pair<iterator, bool>(iterator(tmp, const_cast<node_type **>(&_tree.root)), true)); //casting
                    }
                    else
                    {
                        return (pair<iterator, bool>(iterator(tmp, const_cast<node_type **>(&_tree.root)), false)); //casting
                    }
                }

                //insert range
                template <class InputIterator>
                void    insert(InputIterator first, InputIterator last)
                {
                    for (; first != last; ++first)
                    {
                        insert(*first);
                    }
                }

                //insert with hint
                iterator insert(iterator position, const value_type &val)
                {
                    (void)position;
                    return (this->insert(val).first);
                }

                iterator    lower_bound(const key_type &key1)
                {
                    if (_tree.exists(key1))
                    {
                        node_type *tmp = _tree.lower_bound(_tree.root, key1);
                        if (tmp == NULL)
                            return end();
                        return (iterator(tmp, &_tree.root));
                    }
                    return iterator(NULL, &_tree.root);
                }

                const_iterator lower_bound(const key_type &key1) const
                {
                    node_type *tmp = _tree.lower_bound(_tree.root, key1);
                    if (tmp == NULL)
                        return end();
                    return (const_iterator(tmp, const_cast<node_type **>(&_tree.root)));
                }

                iterator    upper_bound(const key_type &key1)
                {
                    node_type *tmp = _tree.upper_bound(_tree.root, key1);
                    if (tmp == NULL)
                        return end();
                    return (iterator(tmp, &_tree.root));
                }

                const_iterator upper_bound(const key_type &key1) const
                {
                    node_type *tmp = _tree.upper_bound(_tree.root, key1);
                    if (tmp == NULL)
                        return end();
                    return (const_iterator(tmp,const_cast<node_type **>(&_tree.root)));
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

                int depth() const
                {
                    return _tree.depth();
                }
                void    clock_print_all()
                {
                    _tree.clock_print_all();
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