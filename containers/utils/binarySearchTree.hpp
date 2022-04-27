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

    template<typename T>
    class Node
    {
        public:
            T *data;
            Node<T> *left;
            Node<T> *right;
            Node<T> *parent;
            int height;
            int balance_factor;
            Node() : data(NULL), left(NULL), right(NULL), parent(NULL), height(0), balance_factor(0)
            {
            }

            ~Node() {}
    };

    template<class key, class T, class Compare = std::less<key>, class Alloc = std::allocator<ft::pair<const key, T> > >
    class  Avl
    {
        private:
            size_type _size;
            value_compare _comp;
            allocator_type _pair_allocator;
            node_allocator _node_allocator;

        public:
            typedef T value_type;
            typedef key key_type;
            typedef ft::pair<const key, value_type> value_pair;
            typedef Alloc allocator_type;
            typedef Node<value_type> node_type;
            typedef ptrdiff_t difference_type;
            typedef size_t size_type;
            typedef Compare value_compare;
            node_type *root;

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
                    return -1;
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



                // Avl()
                // {
                //     root = NULL;
                // }

                // int height(t_node *node)
                // {
                //     if (node == NULL)
                //         return 0;
                //     return (node->height);
                // }

                // int max(int a, int b)
                // {
                //     return (a > b) ? a : b;
                // }

                // int getBalance(t_node *node)
                // {
                //     if (node == NULL)
                //         return 0;
                //     return (height(node->left) - height(node->right));
                // }

                // t_node *rightRotate(t_node *y)
                // {
                //     t_node *x = y->left;
                //     t_node *T2 = x->right;

                //     x->right = y;
                //     y->left = T2;

                //     if (T2 != NULL)
                //         T2->parent = y;

                //     y->parent = x;

                //     y->height = max(height(y->left), height(y->right)) + 1;
                //     x->height = max(height(x->left), height(x->right)) + 1;

                //     return x;
                // }

                // t_node *leftRotate(t_node *x)
                // {
                //     t_node *y = x->right;
                //     t_node *T2 = y->left;

                //     y->left = x;
                //     x->right = T2;

                //     if (T2 != NULL)
                //         T2->parent = x;

                //     x->parent = y;

                //     x->height = max(height(x->left), height(x->right)) + 1;
                //     y->height = max(height(y->left), height(y->right)) + 1;

                //     return y;
                // }

                // t_node *leftRightRotate(t_node *node)
                // {
                //     node->left = leftRotate(node->left);
                //     return rightRotate(node);
                // }

                // t_node *rightLeftRotate(t_node *node)
                // {
                //     node->right = rightRotate(node->right);
                //     return leftRotate(node);
                // }

                // t_node *insert(t_node *node, int value)
                // {
                //     if (node == NULL)
                //     {
                //         t_node *new_node = new t_node;
                //         new_node->data = value;
                //         new_node->height = 1;
                //         new_node->left = NULL;
                //         new_node->right = NULL;
                //         new_node->parent = NULL;
                //         return new_node;
                //     }

                //     if (value < node->data)
                //     {
                //         node->left = insert(node->left, value);
                //         node->left->parent = node;
                //     }
                //     else if (value > node->data)
                //     {
                //         node->right = insert(node->right, value);
                //         node->right->parent = node;
                //     }

                //     node->height = 1 + max(height(node->left), height(node->right));

                //     int balance = getBalance(node);

                //     if (balance > 1 && value < node->left->data)
                //         return rightRotate(node);

                //     if (balance < -1 && value > node->right->data)
                //         return leftRotate(node);

                //     if (balance > 1 && value > node->left->data)
                //     {
                //         node->left = leftRotate(node->left);
                //         return rightRotate(node);
                //     }

                //     if (balance < -1 && value < node->right->data)
                //     {
                //         node->right = rightRotate(node->right);
                //         return leftRotate(node);
                //     }

                //     return node;
                // }

                // t_node *nodeWitheMinValue(t_node *node)
                // {
                //     t_node *current = node;
                //     while (current->left != NULL)
                //         current = current->left;
                //     return current;
                // }

                // t_node  *nodeWithMaxValue(t_node *node)
                // {
                //     t_node *current = node;
                //     while (current->right != NULL)
                //         current = current->right;
                //     return current;
                // }

                // t_node *deleteNode(t_node *node, int value)
                // {
                //     if (node == NULL)
                //         return node;

                //     if (value < node->data)
                //         node->left = remove(node->left, value);
                //     else if (value > node->data)
                //         node->right = remove(node->right, value);
                //     else
                //     {
                //         if (node->left == NULL)
                //         {
                //             t_node *temp = node->right;
                //             free(node);
                //             return temp;
                //         }
                //         else if (node->right == NULL)
                //         {
                //             t_node *temp = node->left;
                //             free(node);
                //             return temp;
                //         }

                //         t_node *temp = nodeWitheMinValue(node->right);
                //         node->data = temp->data;
                //         node->right = remove(node->right, temp->data);
                //     }

                //     if (node == NULL)
                //         return node;

                //     node->height = 1 + max(height(node->left), height(node->right));

                //     int balance = getBalance(node);

                //     if (balance > 1 && getBalance(node->left) >= 0)
                //         return rightRotate(node);

                //     if (balance > 1 && getBalance(node->left) < 0)
                //         node->left = leftRotate(node->left);

                //     if (balance < -1 && getBalance(node->right) <= 0)
                //         return leftRotate(node);

                //     if (balance < -1 && getBalance(node->right) > 0)
                //         node->right = rightRotate(node->right);

                //     return node;
                // }

                // void    printTree(t_node *root, std::string indent, bool last)
                // {
                //     if (root != NULL)
                //     {
                //         std::cout << indent;
                //         if (last)
                //         {
                //             std::cout << "R----";
                //             indent += "     ";
                //         }
                //         else
                //         {
                //             std::cout << "L----";
                //             indent += "|    ";
                //         }

                //         std::cout << root->data << std::endl;
                //         printTree(root->left, indent, false);
                //         printTree(root->right, indent, true);
                //     }
                // }

        
            // t_node *node;
            // t_node *root;

            
    };
}