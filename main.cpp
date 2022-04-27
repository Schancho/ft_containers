// inserting into a Vector

#include <iostream>
#include "containers/utils/binarySearchTree.hpp"
int main() {
  Tree Tree;
  t_node *root = NULL;
  root = Tree.insert(root, 33);
  root = Tree.insert(root, 13);
  root = Tree.insert(root, 53);
  root = Tree.insert(root, 9);
  root = Tree.insert(root, 21);
  root = Tree.insert(root, 61);
  root = Tree.insert(root, 8);
  root = Tree.insert(root, 11);
  root = Tree.insert(root, 10);
  Tree.printTree(root, "", true);
  root = Tree.remove(root, 13);
  std::cout << "After deleting " << std::endl;
  Tree.printTree(root, "", true);
}