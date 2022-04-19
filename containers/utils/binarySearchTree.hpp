#pragma once

#include <stdlib.h>

typedef struct s_node
{
    int data;
    s_node *left;
    s_node *right;
    s_node *parent;
}t_node;

class  tree
{
    public:
        void insert(int value)
        {
            t_node *new_node = new t_node;
            new_node->data = value;
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
                        {
                            current = current->left;
                        }
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
                        {
                            current = current->right;
                        }
                    }
                }
            }
        }
    private:
        t_node *node;
        t_node *root;
        
};