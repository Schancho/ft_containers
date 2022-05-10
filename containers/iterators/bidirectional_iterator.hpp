#pragma once

namespace ft
{
    template<typename Node, typename pair>
    class bidirectional_iterator
    {
        public:
            typedef Node *node_pointer;
            typedef pair *pair_pointer;
            typedef pair *pointer;
            typedef pair &reference;
            typedef pair value_type;
            typedef pair &pair_reference;
            typedef std::bidirectional_iterator_tag iterator_category;
            typedef std::ptrdiff_t difference_type;

            bidirectional_iterator()  : _node(NULL), _root(NULL) {}
            bidirectional_iterator(node_pointer node, node_pointer *root) : _node(node), _root(root) {}
            bidirectional_iterator(const bidirectional_iterator &other)
            {
                *this = other;
            }
            bidirectional_iterator &operator=(const bidirectional_iterator &other)
            {
                _node = other._node;
                _root = other._root;
                return *this;
            }
            ~bidirectional_iterator() {}

            pair_reference operator*() const
            {
                return (*(_node->data));
            }

            pair_pointer operator->() const
            {
                return _node->data;
            }

            bidirectional_iterator &operator++()
            {
                _node = inOrderSuccessor(_node, *_root);
                return *this;
            }

            bidirectional_iterator operator++(int)
            {
                bidirectional_iterator tmp(*this);
                _node = inOrderSuccessor(_node, *_root);
                return tmp;;
                
            }

            bidirectional_iterator &operator--()
            {
                _node = inOrderPredecessor(_node, *_root);
                return *this;
            }

            bidirectional_iterator operator--(int)
            {
                bidirectional_iterator tmp(*this);
                _node = inOrderPredecessor(_node, *_root);
                return tmp;
            }

            bool operator==(const bidirectional_iterator &other) const
            {
                return (_node == other._node);
            }

            bool operator!=(const bidirectional_iterator &other) const
            {
                return (_node != other._node);
            }

            operator    ft::bidirectional_iterator<Node,pair>() const
            {
                return ft::bidirectional_iterator<Node,pair>(_node, _root);
            }
        private:
            node_pointer _node;
            node_pointer *_root;
    };
    template< typename Node, typename pair>
    class const_bidirectional_iterator
    {
        public:
            typedef Node *node_pointer;
            typedef pair *pair_pointer;
            typedef pair *pointer;
            typedef pair &reference;
            typedef pair value_type;
            typedef pair &pair_reference;
            typedef std::bidirectional_iterator_tag iterator_category;
            typedef std::ptrdiff_t difference_type;
            typedef ft::bidirectional_iterator<Node, pair> bidirectional_iterator;

            const_bidirectional_iterator()  : _node(NULL), _root(NULL) {}
            const_bidirectional_iterator(node_pointer node, node_pointer *root) : _node(node), _root(root) {}
            const_bidirectional_iterator(const bidirectional_iterator &other)
            {
                //maybe it will give a segmentation fault
                _node = other._node;
                _root = other._root;
            }

            const_bidirectional_iterator(const const_bidirectional_iterator &other)
            {
                _node = other._node;
                _root = other._root;
            }

            const_bidirectional_iterator &operator=(const const_bidirectional_iterator &other)
            {
                _node = other._node;
                _root = other._root;
                return *this;
            }

            ~const_bidirectional_iterator() {}

            pair_reference operator*() const
            {
                return (*(_node->data));
            }

            pointer operator->() const
            {
                return _node->data;
            }

            const_bidirectional_iterator &operator++()
            {
                _node = inOrderSuccessor(_node, _root);
                return *this;
            }

            const_bidirectional_iterator operator++(int)
            {
                const_bidirectional_iterator tmp(*this);

                // _node = inOrderSuccessor(_node, _root);
                ++(*this);
                return tmp;
            }

            const_bidirectional_iterator &operator--()
            {
                _node = inOrderPredecessor(_node, _root);
                return *this;
            }

            const_bidirectional_iterator operator--(int)
            {
                const_bidirectional_iterator tmp(*this);
                _node = inOrderPredecessor(_node, _root);
                return tmp;
            }

            bool operator==(const const_bidirectional_iterator &other) const
            {
                return (_node == other._node);
            }

            bool operator!=(const const_bidirectional_iterator &other) const
            {
                return (_node != other._node);
            }

            // operator    ft::const_bidirectional_iterator<pair>() const
            // {
            //     return ft::const_bidirectional_iterator<pair>(_node, _root);
            // }



        private:
            node_pointer _node;
            node_pointer *_root;
    };

}



