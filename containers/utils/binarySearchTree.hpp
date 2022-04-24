#pragma once

#include <stdlib.h>

typedef struct s_node
{
    int data;
    s_node *left;
    s_node *right;
    s_node *parent;
    int height;
    
}t_node;

class  tree
{
    public:
        void insert(int value)
        {
            t_node *new_node = new t_node;
            new_node->data = value;
            new_node->height = 1;
            new_node->left = NULL;
            new_node->right = NULL;
            new_node->parent = NULL;
            if(root == NULL)
            {
                root = new_node;
            }
            else
            {
                t_node *current = root;
                while(current != NULL)
                {
                    if(value < current->data)
                    {
                        if(current->left == NULL)
                        {
                            current->left = new_node;
                            new_node->parent = current;
                            break;
                        }
                        else
                            current = current->left;
                    }
                    else
                    {
                        if(current->right == NULL)
                        {
                            current->right = new_node;
                            new_node->parent = current;
                            break;
                        }
                        else
                            current = current->right;
                    }
                }
            }
        }

        int height(t_node *node)
        {
            if (node == NULL)
                return 0;
            return (node->height);
        }

        int max(int a, int b)
        {
            return (a > b) ? a : b;
        }

        int getBalance(t_node *node)
        {
            if (node == NULL)
                return 0;
            return (height(node->left) - height(node->right));
        }

        t_node *rightRotate(t_node *y)
        {
            t_node *x = y->left;
            t_node *T2 = x->right;

            x->right = y;
            y->left = T2;

            if (T2 != NULL)
                T2->parent = y;

            y->parent = x;

            y->height = max(height(y->left), height(y->right)) + 1;
            x->height = max(height(x->left), height(x->right)) + 1;

            return x;
        }

        t_node *leftRotate(t_node *x)
        {
            t_node *y = x->right;
            t_node *T2 = y->left;

            y->left = x;
            x->right = T2;

            if (T2 != NULL)
                T2->parent = x;

            x->parent = y;

            x->height = max(height(x->left), height(x->right)) + 1;
            y->height = max(height(y->left), height(y->right)) + 1;

            return y;
        }
    private:
        t_node *node;
        t_node *root;

        
};