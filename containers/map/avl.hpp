#pragma once

#include <stdlib.h>
#include <time.h>
#include "pair.hpp"
#include "make_pair.hpp"
#include "../../iterators/bidirectional_iterator.hpp"
#include <iostream>

namespace ft
{

    template<typename pair>
    class Node
    {
        public:
            pair *data;
            Node<pair> *left;
            Node<pair> *right;
            Node<pair> *parent;
            int height;
            int balance_factor;
            Node() : data(NULL), left(NULL), right(NULL), parent(NULL), height(0), balance_factor(0)
            {
            }

            ~Node() {}
    };

    template<typename pair>
    Node<pair> *most_left(Node<pair> *root)
    {
        if (!root)
            return root;
        while (root->left != NULL)
            root = root->left;
        return root;
    }

    template<typename pair>
    Node<pair> *most_right(Node<pair> *root)
    {
        if (!root)
            return root;
        while (root->right)
            root = root->right;
        return root;
    }

    template<typename pair>
    Node<pair> *inOrderSuccessor(Node<pair> *node, Node<pair> *root)
    {
         Node<pair> *current = NULL;
        if (node == NULL)
        {
            return most_left(root);
        }
        else
        {
            if (node->right != NULL)
                return most_left(node->right);
            else
            {
                Node<pair> *parent = node->parent;
                while (parent != NULL && node == parent->right)
                {
                    node = parent;
                    parent = parent->parent;
                }
                return parent;
            }
        }
        return current;
    }

    template<typename pair>
    Node<pair> *inOrderPredecessor(Node<pair> *node, Node<pair> *root)
    {
        Node<pair> *current = NULL;
        if (node == NULL)
        {
            return most_right(root);
        }
        else
        {
            if (node->left != NULL)
                return most_right(node->left);
           current = node->parent;
            while (current != NULL && node == current->left)
            {
                node = current;
                current = current->parent;
            }
        }
        return current;
    }
    template<class key, class Mapped_Type, class Compare = std::less<key>, class Alloc = std::allocator<ft::pair<const key, Mapped_Type> > >
    class  Avl
    {
        public:
            typedef Mapped_Type mapped_type;
            typedef key key_type;
            typedef ft::pair<const key_type, mapped_type> value_type;
            typedef Alloc allocator_type;
            typedef Node<value_type> node_type;
            typedef ptrdiff_t difference_type;
            typedef typename allocator_type::template rebind<node_type>::other node_allocator;
            typedef size_t size_type;
            //typedef Compare value_compare;
            node_type *root;
            typedef bidirectional_iterator<node_type, value_type> iterator;
            typedef const_bidirectional_iterator<node_type, value_type> const_iterator;

            private:
                size_type _size;
                Compare _comp;
                allocator_type _pair_allocator;
                node_allocator _node_allocator;
                node_type *newNode(value_type value)
                {
                    node_type *tmp = _node_allocator.allocate(1);
                    tmp->data = _pair_allocator.allocate(1);
                    _pair_allocator.construct(tmp->data, value);
                    tmp->left = NULL;
                    tmp->right = NULL;
                    tmp->parent = NULL;
                    tmp->height = 1;
                    tmp->balance_factor = 0;
                    return tmp;
                }
                
                int height(node_type *node)
                {
                    if (node == NULL)
                        return 0;
                    return node->height;
                }

                bool __equal(const key_type &key1, const key_type &key2) const 
                {
                    return !_comp(key1, key2) && !_comp(key2, key1);
                }

                bool __exist(node_type *node, const key_type &key1) const
                {
                    if (node == NULL)
                        return false;
                    if (__equal(node->data->first, key1))
                        return true;
                    if (_comp(key1, node->data->first))
                        return __exist(node->left, key1);
                    else
                        return __exist(node->right, key1);
                }

                node_type *__find(node_type *node, const key_type &key1) const
                {
                    if (node == NULL)
                        return NULL;
                    if (__equal(node->data->first, key1))
                        return node;
                    if (_comp(key1, node->data->first))
                        return __find(node->left, key1);
                    else
                        return __find(node->right, key1);
                }
                

                int max(int a, int b)
                {
                    return (a > b) ? a : b;
                }

                int getBalanceFactor(node_type *node)
                {
                    if (node == NULL)
                        return 0;
                    return height(node->left) - height(node->right);
                }

                node_type *rotateRight(node_type *node)
                {
                    node_type *tmp = node->left;
                    if (tmp == NULL)
                        return node;
                    node->left = tmp->right;
                    if (tmp->right != NULL)
                        tmp->right->parent = node;
                    tmp->parent = node->parent;
                    if (node->parent == NULL)
                        root = tmp;
                    else if (node == node->parent->left)
                        node->parent->left = tmp;
                    else
                        node->parent->right = tmp;
                    tmp->right = node;
                    node->parent = tmp;
                    node->height = max(height(node->left), height(node->right)) + 1;
                    node->balance_factor = getBalanceFactor(node);
                    tmp->height = max(height(tmp->left), height(tmp->right)) + 1;
                    tmp->balance_factor = getBalanceFactor(tmp);
                    return tmp;
                }

                node_type *rotateLeft(node_type *node)
                {

                    node_type *tmp = node->right;

                    if (tmp == NULL)
                        return node;
                    node->right = tmp->left;
                    if (tmp->left != NULL)
                        tmp->left->parent = node;
                    tmp->parent = node->parent;
                    if (node->parent == NULL)
                        root = tmp;
                    else if (node == node->parent->left)
                        node->parent->left = tmp;
                    else
                        node->parent->right = tmp;
                    tmp->left = node;
                    node->parent = tmp;
                    node->height = max(height(node->left), height(node->right)) + 1;
                    node->balance_factor = getBalanceFactor(node);
                    tmp->height = max(height(tmp->left), height(tmp->right)) + 1;
                    tmp->balance_factor = getBalanceFactor(tmp);
                    
                    return tmp;
                }

                node_type *rotateLeftRight(node_type *node)
                {

                    node->left = rotateLeft(node->left);
                    return rotateRight(node);
                }

                node_type *rotateRightLeft(node_type *node)
                {
                    node->right = rotateRight(node->right);
                    return rotateLeft(node);
                }
               
               node_type  *update(node_type *node)
               {
                    node->height = max(height(node->left), height(node->right)) + 1;
                    node->balance_factor = getBalanceFactor(node);
                    if (node->balance_factor > 1)
                    {
                        if (getBalanceFactor(node->left) >= 0)
                            node= rotateRight(node);
                        else
                            node= rotateLeftRight(node); // rotateRightLeft
                    }
                    else if (node->balance_factor < -1)
                    {
                        if (getBalanceFactor(node->right) < 0)
                            node=  rotateLeft(node);
                        else
                            node = rotateRightLeft(node); // rotateRightLeft
                    }
                    return node;
               }

                node_type *insert_helper(node_type *node, value_type value)
                {
                    if (root == NULL)
                    {
                        return newNode(value);
                    }
                    if (node == NULL)
                        return  newNode(value);
                    if (_comp(value.first, node->data->first))
                    {
                        node->left = insert_helper(node->left, value);
                        node->left->parent = node;
                    }
                    else if (_comp(node->data->first, value.first))
                    {
                        node->right = insert_helper(node->right, value);
                        node->right->parent = node;
                    }
                    else
                        return node;
                    node_type*ret =  update(node);
                    return ret;
                }

                node_type   *deleteNode_helper(node_type *node, const key_type &key1)
                {
                    if (node == NULL)
                        return NULL;
                    if (_comp(key1, node->data->first))
                        node->left = deleteNode_helper(node->left, key1);
                    else if (_comp(node->data->first, key1))
                        node->right = deleteNode_helper(node->right, key1);
                    else
                    {
                        if (node->left == NULL && node->right)
                        {
                            node->right->parent = node->parent;
                            _pair_allocator.destroy(node->data);
                            _pair_allocator.construct(node->data, *(node->right->data));
                            _pair_allocator.destroy(node->right->data);
                            _pair_allocator.deallocate(node->right->data, 1);
                            _node_allocator.deallocate(node->right, 1);
                            node->right = NULL;
                        }
                        else if (node->right == NULL && node->left)
                        {
                            node->left->parent = node->parent;
                            _pair_allocator.destroy(node->data);
                            _pair_allocator.construct(node->data, *(node->left->data));
                            _pair_allocator.destroy(node->left->data);
                            _pair_allocator.deallocate(node->left->data, 1);
                            _node_allocator.deallocate(node->left, 1);
                            node->left = NULL;
                        }
                        else if (!node->right && !node->left)
                        {
                            _pair_allocator.destroy(node->data);
                            _pair_allocator.deallocate(node->data, 1);
                            _node_allocator.deallocate(node, 1);
                            node = NULL;
                            return NULL;
                        }
                        else
                        {
                            node_type *tmp = most_left(node->right);
                            _pair_allocator.destroy(node->data);
                            _pair_allocator.construct(node->data, *(tmp->data));
                            node->right = deleteNode_helper(node->right, tmp->data->first);
                        }
                    }
                    if (node == NULL)
                        return node;
                    node->height = max(height(node->left), height(node->right)) + 1;
                    node->balance_factor = getBalanceFactor(node);
                    if (node->balance_factor > 1)
                    {
                        if (getBalanceFactor(node->left) >= 0)
                            node =  rotateRight(node);
                        else
                            node =  rotateLeftRight(node); 
                    }
                    else if (node->balance_factor < -1)
                    {
                        if (getBalanceFactor(node->right) < 0)
                            node =  rotateLeft(node);
                        else
                            node =  rotateRightLeft(node); 
                    }
                    return node;
                }

            public:    

                Avl() : root(NULL), _size(0), _comp(), _pair_allocator(), _node_allocator()
                {
                }

                Avl(const Avl &other) : _size(other._size), root(NULL)
                {
                    *this = other;
                }

                Avl &operator=(const Avl &other)
                {
                    clear();
                    node_type *tmp = other.root;
                    copy(tmp);
                    return *this;
                }
                
                void    freee(node_type *node)
                {
                    if (node == NULL)
                        return;
                    freee(node->left);
                    freee(node->right);
                    _pair_allocator.destroy(node->data);
                    _pair_allocator.deallocate(node->data, 1);
                    _node_allocator.deallocate(node, 1);
                }

                void    clear()
                {
                    freee(root);
                    root = NULL;
                    _size = 0;

                }

                void    copy(node_type *node)
                {
                    if (node != NULL)
                    {
                        insert(*(node->data));
                        copy(node->left);
                        copy(node->right);
                    }
                }
                bool    empty() const
                {
                    return _size == 0;
                }

                bool    exists(const key_type &key1) 
                {
                    return (__exist(root, key1));
                }

                node_type   *search(node_type *node, const key_type &key1) const
                {
                    if (node == NULL)
                        return NULL;
                    if (key1 == node->data->first)
                        return node;
                    else
                    {
                        if (_comp(key1, node->data->first))
                            return search(node->left, key1);
                        else
                            return search(node->right, key1);
                    }
                }

                bool   insert(const value_type &value)
                {
                    if (exists(value.first))
                        return false;
                    root = insert_helper(root, value);
                    _size++;
                    return true;
                }

            int    height() const
            {
                if (root == NULL)
                    return 0;
                return root->height;
            }


           bool   remove(key_type key1)
           {
               if (!exists(key1))
                   return false;
               root =  deleteNode_helper(root, key1);
                _size--;
                return true;
           }

           node_type    *_max(node_type *node)
           {
               if (node == NULL)
                   return node;
               while (node->right != NULL)
                   node = node->right;
                return node;
           }

              node_type    *_min(node_type *node) const
              {
                  if (!node)
                    return node;
                while (node->left != NULL)
                    node = node->left;
                return node;
              }

              void  swap(Avl &other)
              {
                  std::swap(root, other.root);
                    std::swap(_size, other._size);
                    std::swap(_comp, other._comp);
              }

           

                size_t size() const
                {
                    return _size;
                }
            
            node_type *successor(node_type *node) const
            {
                if (node->right != NULL)
                    return most_left(node->right);
                node_type *tmp = node->parent;
                while (tmp != NULL && node == tmp->right)
                {
                    node = tmp;
                    tmp = tmp->parent;
                }
                return tmp;
            }

            node_type *lower_bound(node_type *node, key_type key1)
            {
                node_type *tmp = most_left(node);
                while (tmp)
                {
                    if (tmp->data->first >= key1)
                        return tmp;
                    tmp = successor(tmp);
                }
                return NULL;
            }

            node_type *lower_bound(node_type *node, key_type key1) const
            {
                node_type *tmp = most_left(node);
                while (tmp)
                {
                    if (tmp->data->first >= key1)
                        return tmp;
                    tmp = successor(tmp);
                }
                return NULL;
            }

            node_type *upper_bound(node_type *node, key_type key1)
            {
                node_type *tmp = most_left(node);
                while (tmp)
                {
                    if (tmp->data->first > key1)
                        return tmp;
                    tmp = successor(tmp);
                }
                return NULL;
            }

            node_type *upper_bound(node_type *node, key_type key1) const
            {
                node_type *tmp = most_left(node);
                while (tmp)
                {
                    if (tmp->data->first > key1)
                        return tmp;
                    tmp = successor(tmp);
                }
                return NULL;
            }

            pair<iterator, iterator> equal_range(const key_type &key1)
            {
                ft::pair<iterator, iterator> ret = ft::make_pair(lower_bound(key1), upper_bound(key1));
                return ret;
            }

            pair<const_iterator, const_iterator> equal_range(const key_type &key1) const
            {
                ft::pair<const_iterator, const_iterator> ret = ft::make_pair(lower_bound(key1), upper_bound(key1));
                return ret;
            }



                

        void printBT(const std::string& prefix, const node_type* node, bool isLeft)
        {
            if( node != nullptr )
            {
                std::cout << prefix;

                std::cout << (isLeft ? "L├──" : "R└──" );

                // print the value of the node
                std::cout << node->data->first << std::endl;

                // enter the next tree level - left and right branch
                if (node)
                printBT( prefix + (isLeft ? "│   " : "    "), node->left, true);
                printBT( prefix + (isLeft ? "│   " : "    "), node->right, false);
            }
        }

        int depth() const
        {
            return depth(root);
        }
        int depth(node_type *node) const
        {
            if (node == NULL)
                return 0;
            return 1 + std::max(depth(node->left), depth(node->right));
        }

void print()
{
    // ptint value or root in stout
    printBT("", root, true);    
    std::cout<< std::endl;
}

    };
}