#pragma once

#include <stdlib.h>
#include "pair.hpp"

// typedef struct s_node
// {
//     int data;
//     s_node *left;
//     s_node *right;
//     s_node *parent;
//     int height;
    
// }t_node;

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
        Node<pair> *current = root;
        while (current->left != NULL)
            current = current->left;
        return current;
    }

    template<typename pair>
    Node<pair> *most_right(Node<pair> *root)
    {
        Node<pair> *current = root;
        while (current->right != NULL)
            current = current->right;
        return current;
    }

    template<typename pair>
    Node<pair> *inOrderSuccessor(Node<pair> *node, Node<pair> *root)
    {
        if (node != NULL)
        {
            return most_left(root);
        }
        else
        {
            Node<pair> *current = node->parent;
            while (current != NULL && node == current->right)
            {
                node = current;
                current = current->parent;
            }
        }
        return current;
    }

    template<typename pair>
    Node<pair> *inOrderPredecessor(Node<pair> *node, Node<pair> *root)
    {
        if (node != NULL)
        {
            return most_right(root);
        }
        else
        {
            Node<pair> *current = node->parent;
            while (current != NULL && node == current->left)
            {
                node = current;
                current = current->parent;
            }
        }
        return current;
    }
    template<class key, class Mapped_Type, class Compare = std::less<key>, class Alloc = std::allocator<ft::pair<const key, T> > >
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
            private:
                size_type _size;
                value_compare _comp;
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
                tmp->height = 0;
                tmp->balance_factor = 0;
                return tmp;
            }
            
            int height(node_type *node)
            {
                if (node == NULL)
                    return 0;
                return node->height;
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

            node_type *insert(node_type *node, value_type value)
            {
                if (node == NULL)
                    return newNode(value);
                if (_comp(value, node->data->first))
                    node->left = insert(node->left, value);
                else if (_comp(node->data->first, value))
                    node->right = insert(node->right, value);
                else
                    return node;
                node->height = max(height(node->left), height(node->right)) + 1;
                node->balance_factor = getBalanceFactor(node);
                if (node->balance_factor == 2)
                {
                    if (height(node->left->left) >= height(node->left->right))
                        return rotateRight(node);
                    else
                        return rotateLeftRight(node);
                }
                if (node->balance_factor == -2)
                {
                    if (height(node->right->right) >= height(node->right->left))
                        return rotateLeft(node);
                    else
                        return rotateRightLeft(node);
                }
                return node;
            }

            Avl() : _size(0), _comp(), _pair_allocator(), _node_allocator(), root(NULL)
            {
            }

            Avl(const Avl &other) : _size(other._size), _comp(other._comp), _pair_allocator(other._pair_allocator), _node_allocator(other._node_allocator), root(NULL)
            {
                if (other.root == NULL)
                    return;
                root = newNode(other.root->data->first);
                root->data = other.root->data;
                root->left = insert(root->left, other.root->left->data->first);
                root->right = insert(root->right, other.root->right->data->first);
            }

            Avl &operator=(const Avl &other)
            {
                if (this != &other)
                {
                    _size = other._size;
                    _comp = other._comp;
                    _pair_allocator = other._pair_allocator;
                    _node_allocator = other._node_allocator;
                    if (other.root == NULL)
                        root = NULL;
                    else
                    {
                        root = newNode(other.root->data->first);
                        root->data = other.root->data;
                        root->left = insert(root->left, other.root->left->data->first);
                        root->right = insert(root->right, other.root->right->data->first);
                    }
                }
                return *this;
            }

    };
}